// use slint::SharedString;
// use std::pin::Pin;

// Import the Slint module generated from your .slint file
slint::include_modules!();

// Import your C++ bridge
mod lib_ffi;
// use lib_ffi::ffi::new_perlin_generator;
// use lib_ffi::ffi::PerlinTerrainGenerator;
// use lib_ffi::ffi::Vec2i;

fn main() {
    // Create the GUI
    let app = AppWindow::new().expect("Failed to create AppWindow");

    // We'll hold the currently selected generator
    // You could also instantiate on-demand in the closure
    let mut perlin_gen = lib_ffi::ffi::new_perlin_generator();
    // let mut ds_gen = Pin::new(Box::new(new_diamond_square));

    app.on_invoke_generate(move |algorithm| {
        let x: u32 = 64;
        let y: u32 = 64;
        let seed: u32 = 4;
        println!("Generating terrain using algorithm: {}", algorithm);
        match algorithm.as_str() {
            "Perlin Noise" => {
                let _heightmap = perlin_gen.pin_mut().generate_as_unique_ptr(&x, &y, &seed);
                println!("Generated Perlin heightmap of size");
            }
            // "Diamond-Square" => {
            //     let heightmap = ds_gen.generate_as_unique_ptr(Vec2i { x: 64, y: 64 });
            //     println!("Generated Diamond-Square heightmap of size {}", heightmap.len());
            // }
            "Simplex" => {
                println!("Simplex not implemented yet");
            }
            _ => unreachable!(),
        }
    });

    // Run the GUI
    let _ = app.run();
}
