#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

namespace fs = std::filesystem;

// Category detection
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

// Skip project files
bool shouldSkip(const fs::path& file) {
    std::string name = file.filename().string();

    if (name == "organizer.exe" ||
        name == ".gitignore" ||
        name == "README.md" ||
        name == "organizer.log")
        return true;

    return false;
}

// Prevent overwrite
fs::path getUniquePath(const fs::path& dest) {
    if (!fs::exists(dest))
        return dest;

    int counter = 1;
    fs::path parent = dest.parent_path();
    std::string stem = dest.stem().string();
    std::string ext = dest.extension().string();

    while (true) {
        fs::path newPath =
            parent / (stem + "(" + std::to_string(counter) + ")" + ext);
        if (!fs::exists(newPath))
            return newPath;
        counter++;
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Smart File Organizer - Day 8\n\n";

    fs::path targetDir = ".";
    bool dryRun = false;

    // Read command-line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--dry-run")
            dryRun = true;
        else
            targetDir = arg;
    }

    if (!fs::exists(targetDir) || !fs::is_directory(targetDir)) {
        std::cout << "Invalid directory!\n";
        return 1;
    }

    std::ofstream logFile("organizer.log", std::ios::app);

    for (const auto& entry : fs::directory_iterator(targetDir)) {
        if (entry.is_regular_file()) {

            if (shouldSkip(entry.path()))
                continue;

            std::string ext = entry.path().extension().string();
            std::string category = getCategory(ext);

            fs::path categoryPath = targetDir / category;

            if (!dryRun && !fs::exists(categoryPath))
                fs::create_directory(categoryPath);

            fs::path destination = categoryPath / entry.path().filename();
            destination = getUniquePath(destination);

            std::string message =
                entry.path().filename().string() + " -> " + category;

            if (dryRun) {
                std::cout << "[DRY RUN] " << message << std::endl;
            } else {
                fs::rename(entry.path(), destination);
                std::cout << "Moved: " << message << std::endl;
                logFile << "Moved: " << message << std::endl;
            }
        }
    }

    std::cout << "\nDone.\n";
    logFile.close();
    return 0;
}