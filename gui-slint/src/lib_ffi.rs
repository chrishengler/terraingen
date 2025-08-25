#[cxx::bridge]
pub mod ffi {
    #[derive(Debug)]
    struct PerlinParameters {
        scale: f32,
        cellSize: i32,
    }

    // #[derive(Debug)]
    // struct DiamondSquareParameters {
    //     roughness: f32,
    // }

    unsafe extern "C++" {
        include!("perlinTerrainGenerator.h");
        include!("memory");


        type PerlinTerrainGenerator;
        type Heightmap;
        type Vec2i;

        fn new_perlin_generator() -> UniquePtr<PerlinTerrainGenerator>;
        fn setParameters(self: Pin<&mut PerlinTerrainGenerator>, params: &PerlinParameters);

        // call the new wrapper method returning a UniquePtr
        fn generate(self: Pin<&mut PerlinTerrainGenerator>, x: &u32, y: &u32, seed: &u32) -> UniquePtr<Heightmap>;

        type PerlinParameters;
    }

}

// // Free functions wrapping constructors
// pub fn new_perlin() -> UniquePtr<ffi::PerlinTerrainGenerator> {
//     ffi::PerlinTerrainGenerator::new()
// }

// pub fn new_diamond_square() -> UniquePtr<ffi::DiamondSquareGenerator> {
//     ffi::DiamondSquareGenerator::new()
// }