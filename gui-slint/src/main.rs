use crate::lib_ffi::ffi::{buildDiamondSquareParameters, buildPerlinParameters, new_diamond_square_generator, new_perlin_generator};

mod convert_image; 
use crate::convert_image::vec_to_image;

slint::include_modules!();
mod lib_ffi;

fn main() {
    let app = AppWindow::new().unwrap();
    let app_weak = app.as_weak();

    // TODO: won't have to be mutable after static refactoring of generators
    let mut perlin = new_perlin_generator();
    let mut ds = new_diamond_square_generator();

    app.on_invoke_generate(move |algorithm| {
        if let Some(app) = app_weak.upgrade() {
            match algorithm.as_str() {
                "Perlin Noise" => {
                    // let width: u32 = 64;
                    // let height: u32 = 64;
                    // let seed: i32 = 4;

                    let slint_params = app.get_perlin_params();
                    let params = buildPerlinParameters( slint_params.cols as u32, slint_params.rows as u32, slint_params.seed, slint_params.scale, slint_params.cell_size);

                    if let Some(perlin_ref) = perlin.as_mut() {
                        if let Some(params_ref) = params.as_ref() {
                            let hm = perlin_ref.generate_flat(params_ref);
                            println!("Generated Perlin heightmap of length {}", hm.len());
                        
                            let image = vec_to_image(&hm, slint_params.cols as usize, slint_params.rows as usize);
                            app.set_heightmap_image(image);
                        }
                    }
                } 

                "Diamond-Square" => {
                    // let width: u32 = 32;
                    // let height: u32 = 32;
                    // let seed: i32 = 4;

                    let slint_params = app.get_ds_params();
                    let params = buildDiamondSquareParameters(slint_params.cols as u32, slint_params.rows as u32, slint_params.seed, slint_params.roughness);

                    if let Some(ds_ref) = ds.as_mut() {
                        if let Some(params_ref) = params.as_ref() {
                            let hm = ds_ref.generate_flat(params_ref);
                            println!("generated Diamond-Square heightmap of length {}", hm.len());

                            let image = vec_to_image(&hm, slint_params.cols as usize, slint_params.rows as usize);
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
