use crate::lib_ffi::ffi::{new_diamond_square_generator, new_perlin_generator};

slint::include_modules!();
mod lib_ffi;

fn main() {
    let app = AppWindow::new().unwrap();
    let app_weak = app.as_weak();

    // let mut perlin = lib_ffi::ffi::new_perlin_generator();
    // let mut diamond = lib_ffi::ffi::new_diamond_square_generator();

    app.on_invoke_generate(move |algorithm| {
        if let Some(_app) = app_weak.upgrade() {
            match algorithm.as_str() {
                "Perlin Noise" => {
                    // let slint_params = app.get_perlin_params();
                    
                    // For the C bridge, just pass the width, height, seed
                    // You could extend the adapter to accept scale/cellSize if needed
                    let width: u32 = 64;
                    let height: u32 = 64;
                    let seed: u32 = 4;

                    let perlin = new_perlin_generator();
                    let perlin_ref = perlin.as_ref().expect("failed to get ref to perlin generator");
                    let hm = perlin_ref.generate_flat(&width, &height, &seed);

                    println!("Generated Perlin heightmap of length {}", hm.len());
                }

                "Diamond-Square" => {
                    // let _slint_params = app.get_ds_params();
                    
                    let width: u32 = 32;
                    let height: u32 = 32;
                    let seed: u32 = 4;

                    let ds = new_diamond_square_generator();
                    let ds_ref = ds.as_ref().expect("Failed to get reference to diamond-square generator");
                    let hm = ds_ref.generate_flat(&width, &height, &seed);

                    println!("generated Diamond-Square heightmap of length {}", hm.len());
                }
                _ => {}
            }
        }
    });

    let _ = app.run();
}
