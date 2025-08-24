// use slint::SharedString;
slint::include_modules!();

fn main() {
    let app = AppWindow::new().expect("Failed to create AppWindow");

    // app.invoke_generate(|algorithm| {
    //     println!("Generating terrain using: {}", algorithm);
    // });

    let _ = app.run();
}
