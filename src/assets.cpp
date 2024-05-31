#include "assets.hpp"

// template class std::map<char const*, Animation*>;
std::map<std::string, Animation*> animationAssets;

bool assets_init() {
    animationAssets = {
        {"player/idle", new Animation(load_images("entities/player/idle"), 16)},
    };

    return true;
}
