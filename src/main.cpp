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

bool shouldSkip(const fs::path& file) {
    std::string name = file.filename().string();

    // Skip program itself and important project files
    if (name == "organizer.exe" ||
        name == ".gitignore" ||
        name == "README.md")
        return true;

    return false;
}

int main() {
    std::cout << "Smart File Organizer - Day 5\n\n";

    for (const auto& entry : fs::directory_iterator(".")) {
        if (entry.is_regular_file()) {

            if (shouldSkip(entry.path()))
                continue;

            std::string ext = entry.path().extension().string();
            std::string category = getCategory(ext);

            // Create folder if not exists
            if (!fs::exists(category)) {
                fs::create_directory(category);
            }

            fs::path destination = category / entry.path().filename();

            // Move only if file not already there
            if (!fs::exists(destination)) {
                fs::rename(entry.path(), destination);
                std::cout << "Moved: "
                          << entry.path().filename()
                          << " -> "
                          << category << std::endl;
            }
        }
    }

    std::cout << "\nOrganization Complete.\n";
    return 0;
}