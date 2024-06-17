# Changelog

All notable changes to this project will be documented in this file.

## [v0.0.3] Foundation Update

**Date:** June 17, 2024

This update brings significant improvements to code organization, build
infrastructure, asset management, and core functionalities.

**Enhancements:**

- **Project Structure:**
  - **Refined Folder Hierarchy:** The `src` and `include` folders have been
    reorganized into categories like `classes`, `core`, and `main` for enhanced
    clarity and maintainability.
  - **Header Inclusion:** All header files (`.hpp`) have been relocated to the
    `include` folder, establishing a clear separation between source code
    (`.cpp`) and header definitions.
- **Build System:**
  - **Enhanced GitIgnore:** The `.gitignore` file has been optimized to exclude
    unnecessary files and folders from version control, streamlining the
    development workflow.
  - **Cross-Platform Build Scripts:** New build scripts (`build_scripts`) have
    been implemented to support building and linking the project for Windows
    (mingw-w64) and Linux (GNU g++). This facilitates development on various
    platforms.
  - **Dependency Management:** A dedicated `README` file within the project now
    outlines the required dependencies, including libraries and frameworks,
    ensuring a smooth setup process for users.
  - **Old Development configurations:** The previously included .vscode folder
    containing development configurations has been removed.
- **Codebase Modernization:**
  - **Improved Error Handling:** Enhanced error messages now include a
    `[WARNING!]` flag for better visibility and debugging.
  - **Type Safety:** The `Position` and `Size` data types have been transitioned
    from `int[2]` to a custom `cord` type within the `engine` module for
    improved type safety and potential performance gains.
  - **Color Support:** A new `RGB` type has been introduced to efficiently store
    red, green, and blue values as `Uint8` integers, making color management
    more efficient.
  - **Namespace Encapsulation:** All code residing within the `cppGameDev`
    namespace for enhanced collision safety and overall organization.
- **Gameplay and Functionality:**
  - **Player Control:** Player movement, gravity, and other fundamental entity
    management elements have been implemented, laying the foundation for dynamic
    character interaction.
  - **Tilemap System:** A versatile tilemap system has been added, enabling the
    control and manipulation of individual tiles within the game environment.
  - **Map Editor:** A basic map editor has been integrated to allow users to
    create and save game maps using a simple JSON format, increasing the
    flexibility of level design.
  - **Image Loading Optimization:** The `load_image()` function has been
    streamlined for both readability and efficiency, ensuring efficient image
    handling for graphical assets.
  - **Animation Support:** A new `img_list()` function within the `update`
    function was implemented to efficiently retrieve all images associated with
    an animation, streamlining animation management.
  - **Enhanced Physics:** The physics entity has been augmented with a
    `color_mod` variable, enabling dynamic and programmatic color changes for
    visual customization.

**Additional Notes:**

- The project license has been changed from MIT to GPL-3.0. Please review and
  accept the revised license terms before contributing or using the code.
- A GPL-3.0 boilerplate has been added to each file to ensure compliance with
  the license terms.

## [v0.0.2] Engine & Asset Management

**Date:** May 31, 2024

This release focuses on setting the stage for future development. While gameplay
functionality might be limited at this point, it provides a solid base for
building upon.

**Enhancements:**

- **New Modules:**

  - **Engine Core (engine.cpp & engine.hpp):** This new module manages
    general-purpose includes (e.g., core libraries, game engine specifics,
    global renderer and window).
  - **Asset Management (assets.cpp & assets.hpp):** This module handles asset
    importing and conversion (e.g., image formats, sound files).
  - **Image Handling (ImageHandle.cpp & ImageHandle.hpp):** This module
    facilitates image loading and conversion to SDL textures.
  - **Animation (scripts/animation.cpp & scripts/animation.hpp):** This module
    manages animations within the game. It handles animation sequences, stores
    frames (textures), controls playback (looping, frame advancement), and
    provides access to the current frame's texture.
  - **Game Entities: (scripts/entities.cpp & scripts/entities.hpp)**: This
    module Introduced entities as fundamental game objects (e.g., characters).

- **Assets:**
  - Added an assets directory containing some textures and images for use in the
    game (e.g., character sprites).

**Additional Notes:**

## [v0.0.1] Initial Commit

**Date:** May 19, 2024

This is the very first public release of the project! It lays the groundwork for
future development, with essential files and basic project structure in place.

**Project Setup:**

- Established a `LICENSE` file to specify permissions for code usage.
- Created a `.gitignore` file to streamline version control by excluding
  unnecessary files.

**Core Functionalities:**

- Implemented the main game loop functionalities within `game.cpp` and
  `game.hpp`.

**Modular Structure:**

- Organized code into a dedicated `src` folder containing `.cpp` and `.hpp`
  files for specific functionalities.
- Created `main.cpp` as the entry point, initiating the game and calling
  scripts.

**Development Environment:**

- Added a `.vscode` folder with essential build commands for compiling the code.
