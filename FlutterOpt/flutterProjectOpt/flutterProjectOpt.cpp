#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
#define log(x) std::cout<<x<<std::endl;

auto init_filesystem() {
    if (!fs::exists("pubspec.yaml")) {
        log("Not flutter project!");
        return false;
    }
    std::string directoryPath = "./assets/images";

    if (fs::exists(directoryPath)) {
        std::cout << "Directory already exists: " << directoryPath << std::endl;
        return true;
    }
    if (fs::create_directories(directoryPath)) {
        std::cout << "Directory created successfully: " << directoryPath << std::endl;
        return true;
    }
    std::cerr << "Failed to create directory: " << directoryPath << std::endl;
    return false;

}

int main(int argc, char **argv) {
    init_filesystem();
    std::cin.get();
}
