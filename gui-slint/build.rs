fn main() {
    println!("cargo:include=../lib-terraingen/generation/perlin");
    println!("cargo:include=../lib-terraingen/generation/diamondsquare");

    slint_build::compile("ui/appwindow.slint").unwrap();
    cxx_build::bridge("src/lib_ffi.rs")
        .file("../lib-terraingen/external/stb/stbi.cpp")
        .file("../lib-terraingen/external/lodepng/lodepng.cpp")
        .file("../lib-terraingen/generation/diamondsquare/diamondSquare.cpp")
        .file("../lib-terraingen/generation/perlin/perlin.cpp")
        .file("../lib-terraingen/generation/terrainCombination.cpp")
        .file("../lib-terraingen/export/imageExport.cpp")
        .file("../lib-terraingen/modifiers/hydraulic/hydraulicErosionModifier.cpp")
        .include("../lib-terraingen")
        .include("../lib-terraingen/external/lodepng")
        .include("../lib-terraingen/external/stb")
        .include("../lib-terraingen/export")
        .include("../lib-terraingen/generation")
        .include("../lib-terraingen/generation/diamondsquare")
        .include("../lib-terraingen/generation/perlin")
        .include("../lib-terraingen/modifiers/hydraulic")
        .include("cpp")
        .include("include")
        .flag_if_supported("/std:c++20") // windows
        .flag_if_supported("-std=c++20") // linux & mac
        .compile("terraingen_cpp");

    println!("cargo:rerun-if-changed=../lib-terraingen");
    println!("cargo:rerun-if-changed=../lib-terraingen/export/imageExport.h");
    println!("cargo:rerun-if-changed=../lib-terraingen/generation/data_types.h");
    println!("cargo:rerun-if-changed=../lib-terraingen/generation/terrainCombination.h");
    println!("cargo:rerun-if-changed=src/lib_ffi.rs");
}
