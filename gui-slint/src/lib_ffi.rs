#[cxx::bridge]
pub mod ffi {

    #[derive(Debug)]
    #[namespace = "tg::combine"]
    struct HeightmapHandle {
        ptr: *const Heightmap,
    }

    #[namespace = "tg::imgexport"]
    enum ExportType{
        PNG_8,
        PNG_16
    }

    unsafe extern "C++" {
        include!("data_types.h");

        type Heightmap;
        fn flattenHeightmap(hm: &Heightmap) -> UniquePtr<CxxVector<f32>>;
    }

    #[namespace = "tg::combine"]
    unsafe extern "C++" {
        include!("terrainCombination.h");
        
        fn combine(hms: &CxxVector<HeightmapHandle>, weights: &CxxVector<f32>) -> UniquePtr<Heightmap>;
    }

    #[namespace = "tg::imgexport"]
    unsafe extern "C++" {
        include!("imageExport.h");

        type ExportType;

        fn saveToFile(hm: &UniquePtr<Heightmap>, path: &CxxString, expType: &ExportType);
    }

    unsafe extern "C++" {
        include!("generatorParameters.h");

        type DiamondSquareParameters;
        type PerlinParameters;

        fn buildDiamondSquareParameters(cols: u32, rows: u32, seed: i32, roughness: f32) -> UniquePtr<DiamondSquareParameters>;
        fn buildPerlinParameters(cols: u32, rows: u32, seed: i32, scale: f32, cell_size: i32) -> UniquePtr<PerlinParameters>;
    }

    #[namespace = "tg::generate"]
    unsafe extern "C++" {
        include!("diamondSquare.h");

        fn generate_ds_unique(params: &DiamondSquareParameters) -> UniquePtr<Heightmap>;
    }

    #[namespace = "tg::generate"]
    unsafe extern "C++" {
        include!("perlin.h");

        fn generate_perlin_unique(params: &PerlinParameters) -> UniquePtr<Heightmap>;
    }

}
