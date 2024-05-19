#include <iostream>
#include <filesystem>
#include <regex>
#include <string_view>

namespace fs = std::filesystem;

void printDirectory(std::string_view path) {
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            const auto& file_path = entry.path();
            char type = ' ';

            if (fs::is_directory(entry.status())) {
                type = 'D';
            } else if (fs::is_regular_file(entry.status())) {
                type = 'F';
            } else if (fs::is_symlink(entry.status())) {
                type = 'L';
            }

            auto file_size = fs::is_regular_file(entry.status()) ? fs::file_size(file_path) : 0;
            std::cout << "[" << type << "] " << file_path.filename().string() << " " << file_size << "\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

void changeExtension(fs::path path, std::string fileNames, std::string_view newExtension) {
    try {
        std::regex file_pattern(fileNames);
        for (const auto& entry : fs::directory_iterator(path)) {
            if (fs::is_regular_file(entry.status())) {
                const auto& file_path = entry.path();
                std::string filename = file_path.filename().string();

                if (std::regex_match(filename, file_pattern)) {
                    fs::path new_file_path = file_path;
                    new_file_path.replace_extension(newExtension);
                    fs::copy_file(file_path, new_file_path, fs::copy_options::overwrite_existing);
                    std::cout << "Copied: " << file_path << " to " << new_file_path << "\n";
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}

int main() {
    std::string path = "./test_directory"; // Replace with the path to your test directory

    std::cout << "Directory contents before changing extensions:\n";
    printDirectory(path);

    std::string file_pattern = ".*\\.bak"; // Regex to match .bak files
    std::string new_extension = ".txt";

    changeExtension(path, file_pattern, new_extension);

    std::cout << "\nDirectory contents after changing extensions:\n";
    printDirectory(path);

    return 0;
}
