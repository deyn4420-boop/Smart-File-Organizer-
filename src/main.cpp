#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

std::string getCategory(const std::string& ext) {
    if (ext == ".jpg" || ext == ".png" || ext == ".jpeg")
        return "Images";
    else if (ext == ".pdf" || ext == ".docx" || ext == ".txt" || ext == ".md")
        return "Documents";
    else if (ext == ".mp4" || ext == ".mkv")
        return "Videos";
    else if (ext == ".exe")
        return "Executables";
    else
        return "Others";
}

int main() {
    std::cout << "Smart File Organizer - Day 4\n\n";

    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.is_regular_file()) {
            std::string ext = entry.path().extension().string();
            std::string category = getCategory(ext);

            if (!fs::exists(category)) {
                fs::create_directory(category);
                std::cout << "Created folder: " << category << std::endl;
            }
        }
    }

    return 0;
}