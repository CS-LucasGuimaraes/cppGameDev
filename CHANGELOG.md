# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [v0.0.2] Engine & Asset Management

**Date:** May 31, 2024

**Core Functionalities (Expanded):**

* Added `engine.cpp` and `engine.hpp` files for managing general-purpose includes (e.g., core libraries, game engine specifics, global renderer and window).
* Implemented `assets.cpp` and `assets.hpp` to handle asset importing and conversion (e.g., image formats, sound files).
* Included `ImageHandle.cpp` and `ImageHandle.hpp` for image loading and conversion to SDL textures.

**New Modules:**

* **scripts:**
    * Dedicated `scripts` folder containing `.cpp` and `.hpp` files for specific classes.

* **Game Entities:**
    * Introduced entities as fundamental game objects (e.g., characters).
    * Created `PhysicsEntities` class for managing entities within the game.
* **Animation System:**
    * Implemented `Animation` class to handle animations within the game.
    * This class manages animation sequences. It stores frames (textures) and controls playback (looping, frame advancement). It also provides access to the current frame's texture.

**Assets:**

* Added an assets directory containing some textures and images for use in the game (e.g., character sprites).

## [v0.0.1] Initial Commit

**Date:** May 19, 2024

**Project Setup:**

* Established a `LICENSE` file to specify permissions for code usage.
* Created a `.gitignore` file to streamline version control by excluding unnecessary files.

**Core Functionalities:**

* Implemented the main game loop functionalities within `game.cpp` and `game.hpp`.

**Modular Structure:**

* Organized code into a dedicated `src` folder containing `.cpp` and `.hpp` files for specific functionalities.
* Created `main.cpp` as the entry point, initiating the game and calling scripts.

**Development Environment:**

* Added a `.vscode` folder with essential build commands for compiling the code.