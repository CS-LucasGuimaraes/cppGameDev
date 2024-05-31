#ifndef imageHandle_hpp
#define imageHandle_hpp

#include "../engine.hpp"

extern std::string BASE_PATH;

/**
 * Create a texture from an image file using the class surface as base.
 *
 * \param path a path on the filesystem to load an image from.
 * \returns the created texture or NULL on failure; call SDL_GetError() for
 *          more information.
 *
 */
__SDL_Texture  load_image(const char* path);

/**
 * Create a list of textures from a folder path.
 *
 * \param path a path on the filesystem to the folder you want to load the images from.
 * \returns a vector with the created textures or NULL on failure;
 *
 */
const std::vector<__SDL_Texture > load_images(const char* path);

#endif