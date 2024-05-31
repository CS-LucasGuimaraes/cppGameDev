#ifndef assets_hpp
#define assets_hpp

#include "engine.hpp"
#include "scripts/imageHandle.hpp"
#include "scripts/animation.hpp"

extern std::map<std::string, Animation*> animationAssets;

/**
 * Initializes the game assets.
 *
 * This function loads and stores animation data for different player states.
 * 
 * @returns (bool): This function returns true on success, or false on failure (e.g., loading errors).
 */
bool assets_init();

#endif