use std::borrow::BorrowMut;
use std::rc::Rc;
use slint::Model;
use slint::ModelRc;
use slint::VecModel;

use crate::lib_ffi::ffi::{buildDiamondSquareParameters, buildPerlinParameters, new_diamond_square_generator, new_perlin_generator};

mod convert_image; 
use crate::convert_image::vec_to_image;

slint::include_modules!();
mod lib_ffi;

fn default_layer() -> GeneratorLayerInfo {
    GeneratorLayerInfo {
        selected_algorithm: GeneratorType::Perlin,
        ds_params: DiamondSquareParams { seed: 0, roughness: 1.0 },
        perlin_params: PerlinParams { seed: 0, scale: 1.0, cell_size: 16 },
        weight: 1.0,
    }
}

fn main() {
    let app = AppWindow::new().unwrap();
    let app_weak = app.as_weak();


    
    let layers = Rc::new(VecModel::default());
    layers.push(default_layer());

    app.set_layers(ModelRc::from(layers.clone()));

    let mut layers_for_add = layers.clone();
    app.on_add_layer({
        // let mut layers = layers.clone();
        move || {
            layers_for_add.borrow_mut().push(default_layer());
        }
    });

    let app_weak_for_select = app_weak.clone();
    let layers_for_select = layers.clone();
    app.on_select_layer(move |index| {
        if let (Some(app), Some(row)) = (app_weak_for_select.upgrade(), layers_for_select.row_data(index as usize)) {
            app.set_selected_layer_index(index);
            app.set_selected_algorithm(row.selected_algorithm);
            app.set_current_perlin_params(row.perlin_params);
        }
    }); 

    app.on_update_layer({
        let layers = layers.clone();
        let app_weak = app_weak.clone();
        move |layer_info| {
            if let Some(app) = app_weak.upgrade() {
                let idx = app.get_selected_layer_index();
                if idx >= 0 {
                    let i = idx as usize;
                    if let Some(mut row) = layers.row_data(i) {
                        row = layer_info.clone();
                        app.set_selected_algorithm(row.selected_algorithm);
                        layers.set_row_data(i, row);
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
    app.on_invoke_generate(move |algorithm| {
        if let Some(app) = app_weak_for_generate.upgrade() {
            match algorithm {
                val if val == GeneratorType::Perlin => {
                    let cols = app.get_cols();
                    let rows = app.get_rows();

                    let slint_params = app.get_current_perlin_params();
                    let params = buildPerlinParameters( cols as u32, rows as u32, slint_params.seed, slint_params.scale, slint_params.cell_size);

                    if let Some(perlin_ref) = perlin.as_mut() {
                        if let Some(params_ref) = params.as_ref() {
                            let hm = perlin_ref.generate_flat(params_ref);
                            println!("Generated Perlin heightmap of length {}", hm.len());
                        
                            let image = vec_to_image(&hm, cols as usize, rows as usize);
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
                            let hm = ds_ref.generate_flat(params_ref);
                            println!("generated Diamond-Square heightmap of length {}", hm.len());

                            let image = vec_to_image(&hm, cols as usize, rows as usize);
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
