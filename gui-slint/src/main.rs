slint::include_modules!();
mod lib_ffi;

fn main() {
    let app = AppWindow::new().unwrap();
    let app_weak = app.as_weak();

    let mut perlin = lib_ffi::ffi::new_perlin_generator();
    let mut diamond = lib_ffi::ffi::new_diamond_square_generator();

    app.on_invoke_generate(move |algorithm| {
        if let Some(app) = app_weak.upgrade() {
            match algorithm.as_str() {
                "Perlin Noise" => {
                    let slint_params = app.get_perlin_params();
                    let params = lib_ffi::ffi::PerlinParameters {
                        scale: slint_params.scale,
                        cellSize: slint_params.cell_size,
                    };
                    perlin.pin_mut().setParameters(&params);
                    let _hm = perlin.pin_mut().generate(&64, &64, &4);
                }
                "Diamond-Square" => {
                    let slint_params = app.get_ds_params();
                    let params = lib_ffi::ffi::DiamondSquareParameters {
                        roughness: slint_params.roughness,
                    };
                    diamond.pin_mut().setParameters(&params);
                    let _hm = diamond.pin_mut().generate(&64, &64, &4);
                }
                _ => {}
            }
        }
    });

    let _ = app.run();
}
