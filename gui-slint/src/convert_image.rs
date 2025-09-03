fn cxx_vec_to_f64_vec(cxx_vec: &cxx::CxxVector<f32>) -> Vec<f64> {
    cxx_vec.iter().map(|&x| x as f64).collect()
}

pub fn vec_to_image(cxx_vec: &cxx::CxxVector<f32>, width: usize, height: usize) -> slint::Image {
    use slint::{Image, SharedPixelBuffer, Rgba8Pixel};
    println!("cxx vec length = {}" , cxx_vec.len());
    assert!(cxx_vec.len() == width * height);
    let data = cxx_vec_to_f64_vec(cxx_vec);

    let mut buffer = SharedPixelBuffer::<Rgba8Pixel>::new(width as u32, height as u32);
    let pixels = buffer.make_mut_bytes();
    assert!(cxx_vec.len() == width * height);

    for (i, &value) in data.iter().enumerate() {
        let v = (value.clamp(0.0, 1.0) * 255.0) as u8;
        let offset = i * 4;
        pixels[offset] = v;     // R
        pixels[offset + 1] = v; // G
        pixels[offset + 2] = v; // B
        pixels[offset + 3] = 255; // A
    }

    Image::from_rgba8(buffer)
}