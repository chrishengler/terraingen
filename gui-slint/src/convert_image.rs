fn vec_to_image(data: &[f64], width: usize, height: usize) -> slint::Image {
    use slint::{Image, SharedPixelBuffer, Rgba8Pixel};

    let mut buffer = SharedPixelBuffer::<Rgba8Pixel>::new(width as u32, height as u32);
    let pixels = buffer.make_mut_bytes();

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