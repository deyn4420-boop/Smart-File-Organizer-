#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

// Decide category based on extension
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

// Skip important project files
bool shouldSkip(const fs::path& file) {
    std::string name = file.filename().string();

    if (name == "organizer.exe" ||
        name == ".gitignore" ||
        name == "README.md")
        return true;

    return false;
}

// If file already exists, rename: file(1).txt
fs::path getUniquePath(const fs::path& dest) {
    if (!fs::exists(dest))
        return dest;

    int counter = 1;
    fs::path parent = dest.parent_path();
    std::string stem = dest.stem().string();
    std::string ext = dest.extension().string();

    while (true) {
        fs::path newPath = parent / (stem + "(" + std::to_string(counter) + ")" + ext);
        if (!fs::exists(newPath))
            return newPath;
        counter++;
    }
}

int main() {
    std::cout << "Smart File Organizer - Day 6\n\n";

    // Ask user for directory
    std::string folderPath;
    std::cout << "Enter folder path to organize (or press Enter for current folder): ";
    std::getline(std::cin, folderPath);

    fs::path targetDir;

    if (folderPath.empty())
        targetDir = ".";
    else
        targetDir = folderPath;

    if (!fs::exists(targetDir) || !fs::is_directory(targetDir)) {
        std::cout << "Invalid directory!\n";
        return 1;
    }

    for (const auto& entry : fs::directory_iterator(targetDir)) {
        if (entry.is_regular_file()) {

            if (shouldSkip(entry.path()))
                continue;

            std::string ext = entry.path().extension().string();
            std::string category = getCategory(ext);

            fs::path categoryPath = targetDir / category;

            // Create category folder if needed
            if (!fs::exists(categoryPath))
                fs::create_directory(categoryPath);

            fs::path destination = categoryPath / entry.path().filename();

            // Prevent overwrite
            destination = getUniquePath(destination);

            fs::rename(entry.path(), destination);

            std::cout << "Moved: "
                      << entry.path().filename()
                      << " -> "
                      << category << std::endl;
        }
    }

    std::cout << "\nOrganization Complete.\n";
    return 0;
}