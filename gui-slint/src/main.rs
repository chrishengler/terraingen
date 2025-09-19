use std::borrow::BorrowMut;
use std::cell::RefCell;
use std::rc::Rc;
use cxx::let_cxx_string;
use cxx::CxxVector;
use cxx::UniquePtr;
use slint::Image;
use slint::Model;
use slint::ModelRc;
use slint::VecModel;

use crate::lib_ffi::ffi::applyHydraulicErosion;
use crate::lib_ffi::ffi::build_hydraulic_erosion_parameters;
use crate::lib_ffi::ffi::combine;
use crate::lib_ffi::ffi::flattenHeightmap;
use crate::lib_ffi::ffi::generate_ds_unique;
use crate::lib_ffi::ffi::generate_perlin_unique;
use crate::lib_ffi::ffi::saveToFile;
use crate::lib_ffi::ffi::ExportType;
use crate::lib_ffi::ffi::Heightmap;
use crate::lib_ffi::ffi::HeightmapHandle;
use crate::lib_ffi::ffi::HydraulicErosionParameters;
use crate::lib_ffi::ffi::{buildDiamondSquareParameters, buildPerlinParameters};

mod convert_image; 
use crate::convert_image::vec_to_image;

slint::include_modules!();
mod lib_ffi;

pub struct LayerData {
    pub heightmap: Option<UniquePtr<Heightmap>>,
    pub image: Option<slint::Image>,
    pub initialised: bool
}

pub struct GeneratedData {
    pub combined_heightmap: Option<UniquePtr<Heightmap>>,
    pub image: Option<slint::Image>,
    pub modified_heightmap: Option<UniquePtr<Heightmap>>,
}

fn default_layer_data() -> LayerData {
    LayerData {
        heightmap: None,
        image: None,
        initialised: false
    }
}

#[allow(non_snake_case)]
fn exportAs_to_exportType(exportAs: ExportAs) -> ExportType {
    if exportAs == ExportAs::PNG8 {
        print!("8 bit");
        ExportType::PNG_8
    }
    else {
        print!("16 bit");
        ExportType::PNG_16
    }
}

fn convert_he_params(he_params: HEParams) -> UniquePtr<HydraulicErosionParameters> {
    return build_hydraulic_erosion_parameters(
        he_params.num_particles as u32, 
        he_params.inertia, 
        he_params.gravity, 
        he_params.sediment_capacity, 
        he_params.deposition_rate, 
        he_params.erosion_rate, 
        he_params.num_steps as u32);
}

fn default_layer_info() -> GeneratorLayerInfo {
    GeneratorLayerInfo {
        selected_algorithm: GeneratorType::Perlin,
        ds_params: DiamondSquareParams { seed: 0, roughness: 1.0 },
        perlin_params: PerlinParams { seed: 0, scale: 1.0, cell_size: 16 },
        weight: 1.0,
    }
}

pub fn set_layer_data(layer_data_vec: Rc::<RefCell::<Vec::<LayerData>>>, index: i32, heightmap: Option<UniquePtr<Heightmap>>, image: Option<Image>) {
    let mut layer_data_access = layer_data_vec.as_ref().borrow_mut();
    if let Some(layer_data) = layer_data_access.get_mut(index as usize) {
        layer_data.heightmap = heightmap;
        layer_data.image = image;
    }
}

fn main() {
    let app = AppWindow::new().unwrap();
    let app_weak = app.as_weak();

    let generated_data: Rc<RefCell<GeneratedData>> = Rc::new(RefCell::new(GeneratedData { combined_heightmap: None, image: None, modified_heightmap: None }));
    let layers = Rc::new(VecModel::default());
    layers.push(default_layer_info());

    let layer_data: Rc<RefCell<Vec<LayerData>>> = Rc::new(RefCell::new(Vec::new()));
    layer_data.as_ref().borrow_mut().push(default_layer_data());

    app.set_layers(ModelRc::from(layers.clone()));

    let mut layers_for_add = layers.clone();
    let layer_data_for_add = layer_data.clone();
    app.on_add_layer({
        move || {
            layer_data_for_add.as_ref().borrow_mut().push(default_layer_data());
            layers_for_add.borrow_mut().push(default_layer_info());
        }
    });

    let app_weak_for_combine = app_weak.clone();
    let layers_for_combine = layers.clone();
    let layer_data_for_combine = layer_data.clone();
    let generated_data_for_combine = generated_data.clone();
    app.on_combine_layers(move || {
        let len = layers_for_combine.as_ref().row_count();

        let mut heightmap_handles: UniquePtr<CxxVector<HeightmapHandle>> = CxxVector::new();
        let mut weights= CxxVector::<f32>::new();

        for idx in 0..len {
            let layer_info_opt = layers_for_combine.row_data(idx);
            if layer_info_opt.is_none() { continue; }
            let layer_info = layer_info_opt.unwrap();

            if let Some(ld) = layer_data_for_combine.borrow().get(idx) {
                if let Some(hm_ptr) = &ld.heightmap {
                    let handle = HeightmapHandle { ptr: hm_ptr.as_ptr() };
                    heightmap_handles.pin_mut().push(handle);
                    weights.pin_mut().push(layer_info.weight as f32);
                }
            }
        }

        let combined_hm: UniquePtr<Heightmap> = combine(&heightmap_handles, &weights);

        if !combined_hm.is_null() {
            if let Some(app) = app_weak_for_combine.upgrade() {
                let cols = app.get_cols();
                let rows = app.get_rows();
                let mut generated_data = generated_data_for_combine.as_ref().borrow_mut();
                let flattened_map = flattenHeightmap(combined_hm.as_ref().expect("failed to unwrap heightmap"));
                let image = vec_to_image(&flattened_map, cols as usize, rows as usize); 
                generated_data.combined_heightmap = Some(combined_hm);
                app.set_heightmap_image(image.clone());
                generated_data.image = Some(image);
                app.set_terrain_ready(true);
            }
        }
    }
    );

    let data_for_save = generated_data.clone();
    app.on_save_terrain(move |export_as| {
        let default_path = std::env::current_dir().unwrap();
        let export_type = exportAs_to_exportType(export_as);

        if let Some(hm) = &data_for_save.as_ref().borrow().combined_heightmap {
            if let Some(res) = rfd::FileDialog::new()
                .set_file_name("heightmap.png")
                .set_directory(&default_path)
                .save_file(){

                if let Some(path_string) = res.as_os_str().to_str(){
                    let_cxx_string!(cxx_path = path_string);
                    saveToFile(&hm, &cxx_path, &export_type);
                }
            }
        }
    }
    );


    let app_weak_for_select = app_weak.clone();
    let layers_for_select = layers.clone();
    let layer_data_for_select = layer_data.clone();
    app.on_select_layer(move |index| {
        if let Some(app) = app_weak_for_select.upgrade(){
            app.set_selected_layer_index(index);
            app.set_heightmap_image(slint::Image::default());
            if index >= 0 {
                if let (Some(app), Some(row)) = (app_weak_for_select.upgrade(), layers_for_select.row_data(index as usize)) {
                    app.set_selected_algorithm(row.selected_algorithm);
                    app.set_current_perlin_params(row.perlin_params);
                    app.set_current_ds_params(row.ds_params);

                    if let Some(layer) = layer_data_for_select.as_ref().borrow_mut().get(index as usize) {
                        if let Some(image) = &layer.image {
                            app.set_heightmap_image(image.clone());
                        } else {
                            app.set_heightmap_image(slint::Image::default());
                        }
                    }
                }
            }
        }
    }); 


    app.on_update_layer({
        let layers = layers.clone();
        let app_weak = app_weak.clone();
        move |layer_info, idx| {
            if let Some(app) = app_weak.upgrade() {
                if idx >= 0 {
                    if let Some(mut row) = layers.row_data(idx as usize) {
                        row = layer_info.clone();
                        app.set_selected_algorithm(row.selected_algorithm);
                        layers.set_row_data(idx as usize, row);
                    }
                }
            }
        }
    });

    app.on_update_perlin_params({
        let layers = layers.clone();
        let app_weak = app_weak.clone();
        move |params| {
            if let Some(app) = app_weak.upgrade() {
                let idx = app.get_selected_layer_index();
                if idx >= 0 {
                    let i = idx as usize;
                    if let Some(mut row) = layers.row_data(i) {
                        row.perlin_params = params.clone();
                        layers.set_row_data(i, row);
                    }
                }
            }
        }
    });

    app.on_apply_hydraulic_erosion({
        let generated_for_erosion = generated_data.clone();
        let app_weak_for_erosion = app_weak.clone();
        move |params| {
            if let Some(app) = app_weak_for_erosion.upgrade(){
                let he_params = convert_he_params(params);
                let mut generated_data = generated_for_erosion.as_ref().borrow_mut();
                if let Some(combined_hm) = &generated_data.combined_heightmap{
                    let modified_hm = applyHydraulicErosion(&combined_hm, he_params.as_ref().expect("failed to unwrap he params"));
                    let flattened_map = flattenHeightmap(modified_hm.as_ref().expect("failed to unwrap heightmap"));
                    generated_data.modified_heightmap = Some(modified_hm);
                    let cols = app.get_cols();
                    let rows = app.get_rows();
                    let image = vec_to_image(&flattened_map, cols as usize, rows as usize); 
                    app.set_heightmap_image(image.clone());
                    generated_data.image = Some(image);
                }
            }
        }
    });

    let app_weak_for_generate = app_weak.clone();
    let layer_data_for_invoke = layer_data.clone();
    app.on_invoke_generate(move |algorithm| {
        if let Some(app) = app_weak_for_generate.upgrade() {
            let selected_layer_index = app.get_selected_layer_index();
            match algorithm {
                val if val == GeneratorType::Perlin => {
                    let cols = app.get_cols();
                    let rows = app.get_rows();

                    let slint_params = app.get_current_perlin_params();
                    let params = buildPerlinParameters( cols as u32, rows as u32, slint_params.seed, slint_params.scale, slint_params.cell_size);

                    if let Some(params_ref) = params.as_ref() {
                        let hm = generate_perlin_unique(params_ref);
                        let image = flattenHeightmap(hm.as_ref().expect("failed to unwrap heightmap"));
                    
                        let image = vec_to_image(&image, cols as usize, rows as usize);
                        set_layer_data(layer_data_for_invoke.clone(), selected_layer_index, Some(hm), Some(image.clone()));
                        app.set_heightmap_image(image);
                    }
                } 

                val if val == GeneratorType::Diamondsquare => {
                    let cols = app.get_cols();
                    let rows = app.get_rows();

                    let slint_params = app.get_current_ds_params();
                    let params = buildDiamondSquareParameters(cols as u32, rows as u32, slint_params.seed, slint_params.roughness);

                    if let Some(params_ref) = params.as_ref() {
                        let hm = generate_ds_unique(params_ref);
                        let image = flattenHeightmap(hm.as_ref().expect("failed to unwrap heightmap"));

                        let image = vec_to_image(&image, cols as usize, rows as usize);
                        set_layer_data(layer_data_for_invoke.clone(), selected_layer_index, Some(hm), Some(image.clone()));
                        app.set_heightmap_image(image);
                    }
                }
                _ => {}
            }
        }
    });

    let _ = app.run();
}
