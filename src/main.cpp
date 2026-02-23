#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::cout << "Smart File Organizer - Day 1\n";
    std::cout << "Listing all items in current directory:\n\n";

    for (const auto& entry : fs::directory_iterator(".")) {
        std::cout << entry.path() << std::endl;
    }

    return 0;
}