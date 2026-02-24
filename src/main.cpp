#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main() {
    std::cout << "Smart File Organizer - Day 2\n";
    std::cout << "Listing only files with extensions:\n\n";

    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.is_regular_file()) {
            std::cout 
                << entry.path().filename()
                << " -> "
                << entry.path().extension()
                << std::endl;
        }
    }

    return 0;
}