#[cxx::bridge]
pub mod ffi {
    unsafe extern "C++" {
        include!("perlinTerrainGenerator.h");
        include!("memory");

        type PerlinTerrainGenerator;
        type Heightmap;
        type Vec2i;

        fn new_perlin_generator(seed: u32) -> UniquePtr<PerlinTerrainGenerator>;
        fn setParameters(self: Pin<&mut PerlinTerrainGenerator>, params: &PerlinParameters);

        // call the new wrapper method returning a UniquePtr
        fn generate_as_unique_ptr(self: Pin<&mut PerlinTerrainGenerator>, x: &u32, y: &u32) -> UniquePtr<Heightmap>;

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