/*
 * Write function that for a given file name computes the sum of ASCII codes of all characters in that
file and returns it using std::promise.
In the main thread create separate thread for each file name given as command line argument.
Thread should compute the sum of characters in a given file.
Use futures to get those sums and find all pairs of files with the same sums.
 */
#include <iostream>
#include <fstream>
#include <thread>
#include <future>
#include <vector>
#include <map>

void computeSum(std::string filename, std::promise<int> &&p) {
    std::ifstream file(filename);
//    if (!file) {
//        std::cout << "Failed to open file: " << filename << "\n";
//        return;
//    }
//    if(file){
//        std::cout << "File " << filename << " opened successfully" << std::endl;
//    }

    char c;
    int sum = 0;
    while (file.get(c)) {
        sum += static_cast<int>(c);
    }
//    std::cout << "Sum for file " << filename << " is: " << sum << "\n";
    p.set_value(sum);
}

int main(int argc, char* argv[]) {
    std::vector<std::future<int>> futures;
    std::map<int, std::vector<std::string>> sums;

    for (int i = 1; i < argc; ++i) {
        std::promise<int> p;
        futures.push_back(p.get_future());
        std::thread(computeSum, argv[i], std::move(p)).detach();
    }

    for (int i = 1; i < argc; ++i) {
        sums[futures[i-1].get()].push_back(argv[i]);
    }

    for (const auto& pair : sums) {
        if (pair.second.size() > 1) {
            std::cout << "Files with the same sum (" << pair.first << "): ";
            for (const auto& filename : pair.second) {
                std::cout << filename << " ";
            }
            std::cout << "\n";
        }
    }


    return 0;
}