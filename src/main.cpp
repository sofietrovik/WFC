
#include <iostream>

#include "voxParser.h"
#include "wave.h"

//TODO
void initTileSetFromFolder(const char* filepath, std::vector<Tile*>& tileSet, bool rotate = false) {
    //for each vox file in 'filepath' folder, create tile with the voxel data
    //if 'rotate' = true, also create rotations of the tile
    //all tiles must be placed in the 'tileset' vector
}




void initStairsTileSet(std::vector<Tile*>& tileSet) {
    Vector3D<uint8_t> big_stair = readVoxFile("vox_tiles/stairs/big_stair.vox");
    Tile* big_stairTile = new Tile{"big_stair", big_stair, tileSet};
    big_stairTile->addRotations(3, tileSet);

    Vector3D<uint8_t> empty = readVoxFile("vox_tiles/stairs/empty.vox");
    Tile* emptyTile = new Tile{"empty", empty, tileSet};

    Vector3D<uint8_t> small_stair = readVoxFile("vox_tiles/stairs/small_stair.vox");
    Tile* small_stairTile = new Tile{"small_stair", small_stair, tileSet};
    small_stairTile->addRotations(3, tileSet);
}

void initSimpleShapesTileSet(std::vector<Tile*>& tileSet) {
    // Vector3D<uint8_t> wallInnerCornerGround = readVoxFile("vox_tiles/simple_shapes/wall_inner_corner_ground.vox"); 
    // Tile* wallInnerCornerGroundTile = new Tile{"wallInnerCornerGround", wallInnerCornerGround, tileSet};
    // wallInnerCornerGroundTile->addRotations(3, tileSet);

    // Vector3D<uint8_t> wallOuterCornerGround = readVoxFile("vox_tiles/simple_shapes/wall_outer_corner_ground.vox");
    // Tile* wallOuterCornerGroundTile = new Tile{"wallOuterCornerGround", wallOuterCornerGround, tileSet};
    // wallOuterCornerGroundTile->addRotations(3, tileSet);

    // Vector3D<uint8_t> empty = readVoxFile("vox_tiles/simple_shapes/sky.vox");
    // Tile* emptyTile = new Tile{"empty", empty, tileSet};

    // Vector3D<uint8_t> ground = readVoxFile("vox_tiles/simple_shapes/ground.vox");
    // Tile* groundTile = new Tile{"ground", ground, tileSet};

    // Vector3D<uint8_t> halfWallGround = readVoxFile("vox_tiles/simple_shapes/half_wall_ground.vox");
    // Tile* halfWallGroundTile = new Tile{"halfWallGround", halfWallGround, tileSet};
    // halfWallGroundTile->addRotations(3, tileSet);

    // Vector3D<uint8_t> halfWallTop = readVoxFile("vox_tiles/simple_shapes/half_wall_top.vox");
    // Tile* halfWallTopTile = new Tile{"halfWallTop", halfWallTop, tileSet};
    // halfWallTopTile->addRotations(3, tileSet);

    // Vector3D<uint8_t> skyGround = readVoxFile("vox_tiles/simple_shapes/sky_ground.vox");
    // Tile* skyGroundTile = new Tile{"skyGround", skyGround, tileSet};

    // Vector3D<uint8_t> wallInnerCornerTop = readVoxFile("vox_tiles/simple_shapes/wall_inner_corner_top.vox");
    // Tile* wallInnerCornerTopTile = new Tile{"wallInnerCornerTop", wallInnerCornerTop, tileSet};
    // wallInnerCornerTopTile->addRotations(3, tileSet);

    // Vector3D<uint8_t> wallOuterCornerTop = readVoxFile("vox_tiles/simple_shapes/wall_outer_corner_top.vox");
    // Tile* wallOuterCornerTopTile = new Tile{"wallOuterCornerTop", wallOuterCornerTop, tileSet};
    // wallOuterCornerTopTile->addRotations(3, tileSet); 

    Vector3D<uint8_t> wallOuterCorner = readVoxFile("vox_tiles/simple_shapes/wall_outer_corner.vox");
    Tile* wallOuterCornerTile = new Tile{"wallOuterCorner", wallOuterCorner, tileSet};
    wallOuterCornerTile->addRotations(3, tileSet);

    Vector3D<uint8_t> wallInnerCorner = readVoxFile("vox_tiles/simple_shapes/wall_inner_corner.vox");
    Tile* wallInnerCornerTile = new Tile{"wallInnerCorner", wallInnerCorner, tileSet};
    wallInnerCornerTile->addRotations(3, tileSet);

    // Vector3D<uint8_t> wall = readVoxFile("vox_tiles/simple_shapes/wall.vox");
    // Tile* wallTile = new Tile{"wall", wall, tileSet};    
    // wallTile->addRotations(3, tileSet);
}


int main() {

    std::string magicaPath = "C:/Program Files/MagicaVoxel-0.99.7.1-win64/MagicaVoxel.exe";

    std::vector<Tile*> tileSet;
    initSimpleShapesTileSet(tileSet);

    Wave wave{WAVE_GRID_SIZE_X, WAVE_GRID_SIZE_Y, WAVE_GRID_SIZE_Z, tileSet};

    Vector3D<uint8_t> model = wave.run();

    writeVoxFile(model, "vox_tiles/output.vox");
    openInMagicaVoxel("vox_tiles/output.vox", magicaPath);

    return 0;
}


