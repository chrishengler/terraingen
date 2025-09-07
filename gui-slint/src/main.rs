use std::borrow::BorrowMut;
use std::cell::RefCell;
use std::rc::Rc;
use cxx::UniquePtr;
use slint::Image;
use slint::Model;
use slint::ModelRc;
use slint::VecModel;

use crate::lib_ffi::ffi::flattenHeightmap;
use crate::lib_ffi::ffi::Heightmap;
use crate::lib_ffi::ffi::{buildDiamondSquareParameters, buildPerlinParameters, new_diamond_square_generator, new_perlin_generator};

mod convert_image; 
use crate::convert_image::vec_to_image;

slint::include_modules!();
mod lib_ffi;

pub struct LayerData {
    pub heightmap: Option<UniquePtr<Heightmap>>,
    pub image: Option<slint::Image>,
    pub initialised: bool
}

fn default_layer_data() -> LayerData {
    LayerData {
        heightmap: None,
        image: None,
        initialised: false
    }
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

    let app_weak_for_select = app_weak.clone();
    let layers_for_select = layers.clone();
    let layer_data_for_select = layer_data.clone();
    app.on_select_layer(move |index| {
        if let Some(app) = app_weak_for_select.upgrade(){
            app.set_selected_layer_index(index);
            app.set_heightmap_image(slint::Image::default());
            if index >= 0 {
                if let (Some(app), Some(row)) = (app_weak_for_select.upgrade(), layers_for_select.row_data(index as usize)) {
                    println!("{}: {}", index, (if row.selected_algorithm == GeneratorType::Perlin { "Perlin" } else { "DS" }));
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

    // TODO: won't have to be mutable after static refactoring of generators
    let mut perlin = new_perlin_generator();
    let mut ds = new_diamond_square_generator();

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

                    if let Some(perlin_ref) = perlin.as_mut() {
                        if let Some(params_ref) = params.as_ref() {
                            let hm = perlin_ref.generate_unique(params_ref);
                            let image = flattenHeightmap(hm.as_ref().expect("failed to unwrap heightmap"));
                            println!("Generated Perlin heightmap of length {}", image.len());
                        
                            let image = vec_to_image(&image, cols as usize, rows as usize);
                            set_layer_data(layer_data_for_invoke.clone(), selected_layer_index, Some(hm), Some(image.clone()));
                            app.set_heightmap_image(image);
                        }
                    }
                } 

                val if val == GeneratorType::Diamondsquare => {
                    let cols = app.get_cols();
                    let rows = app.get_rows();

                    let slint_params = app.get_current_ds_params();
                    let params = buildDiamondSquareParameters(cols as u32, rows as u32, slint_params.seed, slint_params.roughness);

                    if let Some(ds_ref) = ds.as_mut() {
                        if let Some(params_ref) = params.as_ref() {
                            let hm = ds_ref.generate_unique(params_ref);
                            let image = flattenHeightmap(hm.as_ref().expect("failed to unwrap heightmap"));
                            println!("generated Diamond-Square heightmap of length {}", image.len());

                            let image = vec_to_image(&image, cols as usize, rows as usize);
                            set_layer_data(layer_data_for_invoke.clone(), selected_layer_index, Some(hm), Some(image.clone()));
                            app.set_heightmap_image(image);
                        }
                    }
                }
                _ => {}
            }
        }
    });

    let _ = app.run();
}
