#pragma once

#include <filesystem>
#include <sstream>

namespace fs = std::filesystem;

inline fs::path get_temp_filepath(const std::string &extension, const std::string &label = "")
{
        std::stringstream filename("");
        filename << "terraingen-test-export-";
        if(!label.empty())
        {
            filename << label << "-";
        }
        std::srand(static_cast<unsigned int>(std::time({})));
        filename << std::rand() << "." << extension;
        auto filepath = fs::path(fs::temp_directory_path() / filename.str());

        return filepath;
}

