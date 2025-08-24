fn main() {
    slint_build::compile("ui/appwindow.slint").unwrap();
    cxx_build::bridge("src/lib_ffi.rs")
        .file("../lib-terraingen/generation/generator.cpp")
        .file("../lib-terraingen/generation/diamondsquare/diamondSquareGenerator.cpp")
        .file("../lib-terraingen/generation/flat/flatTerrainGenerator.cpp")
        .file("../lib-terraingen/generation/perlin/perlinTerrainGenerator.cpp")
        .file("../lib-terraingen/generation/terrainCombination.cpp")
        .include("../lib-terraingen")
        .include("../lib-terraingen/generation")
        .include("../lib-terraingen/generation/diamondSquare")
        .include("../lib-terraingen/generation/flat")
        .include("../lib-terraingen/generation/perlin")
        .flag_if_supported("-std=c++20")
        .compile("terraingen_cpp");

    println!("cargo:rerun-if-changed=../lib-terraingen");
    println!("cargo:rerun-if-changed=src/lib_ffi.rs");
}
