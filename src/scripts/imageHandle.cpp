#include "imageHandle.hpp"

std::string BASE_PATH = "assets/images/";

__SDL_Texture load_image(const char *path) {
    return SDL_CreateTextureFromSurface(display, IMG_Load(path));
}

const std::vector<__SDL_Texture> load_images(const char* path) {
    std::vector<__SDL_Texture > tmp;
    for (auto const& file : std::filesystem::directory_iterator((BASE_PATH+path).c_str())) {
        tmp.push_back(load_image((BASE_PATH + std::string(path) + "/"  + file.path().filename().string()).c_str()));
        
        std::clog << "    " << std::string(path) << "/"  << file.path().filename().string() << " loaded.\n";
    }
    
    return tmp;
}