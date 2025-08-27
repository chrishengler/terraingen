#[cxx::bridge]
pub mod ffi {
    unsafe extern "C++" {
        include!("perlinTerrainGenerator.h");

        type PerlinTerrainGenerator;

        fn new_perlin_generator() -> UniquePtr<PerlinTerrainGenerator>;
        fn generate_flat(self: &PerlinTerrainGenerator, x: &u32, y: &u32, seed: &u32) -> UniquePtr<CxxVector<f32>>;
    }

    unsafe extern "C++" {
        include!("diamondSquareGenerator.h");

        type DiamondSquareGenerator;

        fn new_diamond_square_generator() -> UniquePtr<DiamondSquareGenerator>;
        fn generate_flat(self: &DiamondSquareGenerator, x: &u32, y: &u32, seed: &u32) -> UniquePtr<CxxVector<f32>>;
    }
}
