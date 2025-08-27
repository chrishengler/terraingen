#[cxx::bridge]
pub mod ffi {

    unsafe extern "C++" {
        include!("generatorParameters.h");

        type DiamondSquareParameters;
        type PerlinParameters;

        fn buildDiamondSquareParameters(roughness: f32) -> UniquePtr<DiamondSquareParameters>;
        fn buildPerlinParameters(scale: f32, cell_size: i32) -> UniquePtr<PerlinParameters>;
    }

    unsafe extern "C++" {
        include!("diamondSquareGenerator.h");

        type DiamondSquareGenerator;

        fn new_diamond_square_generator() -> UniquePtr<DiamondSquareGenerator>;
        fn setParameters(self: Pin<&mut DiamondSquareGenerator>, params: &DiamondSquareParameters);
        fn generate_flat(self: &DiamondSquareGenerator, x: &u32, y: &u32, seed: &u32) -> UniquePtr<CxxVector<f32>>;
    }

    unsafe extern "C++" {
        include!("perlinTerrainGenerator.h");

        type PerlinTerrainGenerator;

        fn new_perlin_generator() -> UniquePtr<PerlinTerrainGenerator>;
        fn setParameters(self: Pin<&mut PerlinTerrainGenerator>, params: &PerlinParameters);
        fn generate_flat(self: &PerlinTerrainGenerator, x: &u32, y: &u32, seed: &u32) -> UniquePtr<CxxVector<f32>>;
    }

}
