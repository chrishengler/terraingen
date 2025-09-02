use std::borrow::BorrowMut;
use std::rc::Rc;
use slint::ModelRc;
use slint::VecModel;

use crate::lib_ffi::ffi::{buildDiamondSquareParameters, buildPerlinParameters, new_diamond_square_generator, new_perlin_generator};

mod convert_image; 
use crate::convert_image::vec_to_image;

slint::include_modules!();
mod lib_ffi;

fn main() {
    let app = AppWindow::new().unwrap();
    let app_weak = app.as_weak();


    let mut layers = Rc::new(VecModel::default());
    const DEFAULT_LAYER : GeneratorLayerInfo = GeneratorLayerInfo {
        selected_algorithm: GeneratorType::Perlin,
        ds_params: DiamondSquareParams { seed: 0, roughness: 1.0 },
        perlin_params: PerlinParams { seed: 0, scale: 1.0, cell_size: 16 },
        weight: 1.0
    };
    layers.push(DEFAULT_LAYER);

    app.set_layers(ModelRc::from(layers.clone()));

    app.on_add_layer({
        // let mut layers = layers.clone();
        move || {
            layers.borrow_mut().push(DEFAULT_LAYER.clone());
        }
    });

    // TODO: won't have to be mutable after static refactoring of generators
    let mut perlin = new_perlin_generator();
    let mut ds = new_diamond_square_generator();

    app.on_invoke_generate(move |algorithm| {
        if let Some(app) = app_weak.upgrade() {
            match algorithm {
                val if val == GeneratorType::Perlin => {
                    let cols = app.get_cols();
                    let rows = app.get_rows();

                    let slint_params = app.get_perlin_params();
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

                    let slint_params = app.get_ds_params();
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
