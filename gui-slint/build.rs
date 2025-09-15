fn main() {
        // Tell Cargo where to find headers
    println!("cargo:include=../lib-terraingen/generation/perlin");
    println!("cargo:include=../lib-terraingen/generation/diamondsquare");

    // Tell Cargo where to find your compiled library
    // println!("cargo:rustc-link-search=native=../lib-terraingen/build");

    // // Link the library (adjust name to your actual built target)
    // println!("cargo:rustc-link-lib=static=terraingen"); // or "dylib"

    // Rebuild if these files change

    slint_build::compile("ui/appwindow.slint").unwrap();
    cxx_build::bridge("src/lib_ffi.rs")
        .file("../lib-terraingen/generation/diamondsquare/diamondSquareGenerator.cpp")
        .file("../lib-terraingen/generation/perlin/perlinTerrainGenerator.cpp")
        .file("../lib-terraingen/generation/terrainCombination.cpp")
        .file("../lib-terraingen/export/imageExporter.cpp")
        .file("../lib-terraingen/external/stb/stbi.cpp")
        .file("../lib-terraingen/external/lodepng/lodepng.cpp")
        .include("../lib-terraingen")
        .include("../lib-terraingen/external/lodepng")
        .include("../lib-terraingen/external/stb")
        .include("../lib-terraingen/export")
        .include("../lib-terraingen/generation")
        .include("../lib-terraingen/generation/diamondsquare")
        .include("../lib-terraingen/generation/perlin")
        .include("cpp")
        .include("include")
        .flag_if_supported("/std:c++20") // windows
        .flag_if_supported("-std=c++20") // linux & mac
        .compile("terraingen_cpp");

    println!("cargo:rerun-if-changed=../lib-terraingen");
    println!("cargo:rerun-if-changed=../lib-terraingen/export/imageExporter.h");
    println!("cargo:rerun-if-changed=../lib-terraingen/generation/data_types.h");
    println!("cargo:rerun-if-changed=../lib-terraingen/generation/terrainCombination.h");
    println!("cargo:rerun-if-changed=src/lib_ffi.rs");
}
