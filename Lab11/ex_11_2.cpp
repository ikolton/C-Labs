/*
 *Exercise 2. Filesystem
Implement functions

 * Prints content of directory given by path
 * Format
 * [X] file_name file_size
 * where X equals D for directories, F for regular files, L for symlinks and space otherwise.
 * @param path directory path

void printDirectory (std::string_view path);

 * Makes copies of all files matching fileNames regular expression in directory given by path
 * to files in the same directory but with changes extension to newExtension
 * @param path directory path
 * @param fileNames regular expression
 * @param newExtension new extension

void changeExtension(fs::path path, std::string fileNames, std::string_view newExtension );
 */

#include <filesystem>
#include <regex>
#include <iostream>

void printDirectory(std::string_view path) {
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        char type = ' ';
        if (std::filesystem::is_directory(entry.status())) {
            type = 'D';
        } else if (std::filesystem::is_regular_file(entry.status())) {
            type = 'F';
        } else if (std::filesystem::is_symlink(entry.symlink_status())) {
            type = 'L';
        }

        std::cout << "[" << type << "] " << entry.path().filename();
        if (type == 'F') {
            std::cout << " " << std::filesystem::file_size(entry);
        }
        std::cout << '\n';
    }
}

void changeExtension(std::filesystem::path path, std::string fileNames, std::string_view newExtension) {
    std::regex fileNamesRegex(fileNames);
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        if (std::filesystem::is_regular_file(entry.status()) && std::regex_match(entry.path().filename().string(), fileNamesRegex)) {
            std::filesystem::path newPath = entry.path();
            newPath.replace_extension(newExtension);
            std::filesystem::copy(entry, newPath);
        }
    }
}

int main() {
    // Test printDirectory function
    std::cout << "Testing printDirectory function with path './':\n";
    printDirectory("./");

    // Test changeExtension function
    std::cout << "\nTesting changeExtension function with path './', fileNames '.txt$', and newExtension '.bak':\n";
    changeExtension("./", ".bak$", ".txt");

    // Print directory content again to see the changes
    std::cout << "\nDirectory content after changeExtension function:\n";
    printDirectory("./");

    return 0;
}