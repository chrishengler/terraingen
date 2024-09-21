#pragma once

#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

inline fs::path get_temp_filepath(const std::string &extension)
{
        std::stringstream filename("");
        filename << "terraingen-test-export-" << std::rand() << "." << extension;
        auto filepath = fs::path(fs::temp_directory_path() / filename.str());

        return filepath;
}

