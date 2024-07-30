
#include <iostream>

#include "voxParser.h"
#include "wave.h"




int main() {

    std::string magicaPath = "C:/Program Files/MagicaVoxel-0.99.7.1-win64/MagicaVoxel.exe";




    //-------------STAIRS--------------

    Vector3D<uint8_t> big_stair = readVoxFile("vox_tiles/stairs/big_stair.vox");
    Tile big_stairTile{"stair", big_stair};
    big_stairTile.addRotations(3);

    Vector3D<uint8_t> empty = readVoxFile("vox_tiles/stairs/empty.vox");
    Tile emptyTile{"empty", empty};   

    Vector3D<uint8_t> small_stair = readVoxFile("vox_tiles/stairs/small_stair.vox");
    Tile small_stairTile{"small_stair", small_stair};
    small_stairTile.addRotations(3);
    

    std::vector<Tile*> tileSet = small_stairTile.getTileSet();
    //-------------------------------


    Wave wave{WAVE_GRID_SIZE_X, WAVE_GRID_SIZE_Y, WAVE_GRID_SIZE_Z, tileSet};

    Vector3D<uint8_t> model = wave.run();

    writeVoxFile(model, "vox_tiles/output.vox");
    openInMagicaVoxel("vox_tiles/output.vox", magicaPath);

    return 0;
}


//TODO: finish
std::vector<Tile*> initStairsTileSet() {
    Vector3D<uint8_t> stair = readVoxFile("vox_tiles/stairs/big_stair.vox");
    Tile stairTile{"stair", stair};
    stairTile.addRotations(3);


    Vector3D<uint8_t> empty = readVoxFile("vox_tiles/stairs/empty.vox");
    Tile emptyTile{"empty", empty};


    Vector3D<uint8_t> stair_top_corner = readVoxFile("vox_tiles/stairs/stair_top_corner.vox");
    Tile stair_top_cornerTile{"stair_top_corner", stair_top_corner};
    stair_top_cornerTile.addRotations(3);

    return stairTile.getTileSet();
}

std::vector<Tile*> initSimpleShapesTileSet() {
    Vector3D<uint8_t> wallInnerCornerGround = readVoxFile("vox_tiles/simple_shapes/wall_inner_corner_ground.vox"); 
    Tile wallInnerCornerGroundTile{"wallInnerCornerGround", wallInnerCornerGround};
    wallInnerCornerGroundTile.addRotations(3);

    Vector3D<uint8_t> wallOuterCornerGround = readVoxFile("vox_tiles/simple_shapes/wall_outer_corner_ground.vox");
    Tile wallOuterCornerGroundTile{"wallOuterCornerGround", wallOuterCornerGround};
    wallOuterCornerGroundTile.addRotations(3);

    Vector3D<uint8_t> empty = readVoxFile("vox_tiles/simple_shapes/sky.vox");
    Tile emptyTile{"empty", empty};

    Vector3D<uint8_t> ground = readVoxFile("vox_tiles/simple_shapes/ground.vox");
    Tile groundTile{"ground", ground};

    Vector3D<uint8_t> halfWallGround = readVoxFile("vox_tiles/simple_shapes/half_wall_ground.vox");
    Tile halfWallGroundTile{"halfWallGround", halfWallGround};

    Vector3D<uint8_t> halfWallTop = readVoxFile("vox_tiles/simple_shapes/half_wall_top.vox");
    Tile halfWallTopTile{"halfWallTop", halfWallTop};
    halfWallTopTile.addRotations(3);

    Vector3D<uint8_t> skyGround = readVoxFile("vox_tiles/simple_shapes/sky_ground.vox");
    Tile skyGroundTile{"skyGround", skyGround};

    Vector3D<uint8_t> wallInnerCornerTop = readVoxFile("vox_tiles/simple_shapes/wall_inner_corner_top.vox");
    Tile wallInnerCornerTopTile{"wallInnerCornerTop", wallInnerCornerTop};
    wallInnerCornerTopTile.addRotations(3);

    Vector3D<uint8_t> wallOuterCornerTop = readVoxFile("vox_tiles/simple_shapes/wall_outer_corner_top.vox");
    Tile wallOuterCornerTopTile{"wallOuterCornerTop", wallOuterCornerTop};
    wallOuterCornerTopTile.addRotations(3); 

    Vector3D<uint8_t> wallOuterCorner = readVoxFile("vox_tiles/simple_shapes/wall_outer_corner.vox");
    Tile wallOuterCornerTile{"wallOuterCorner", wallOuterCorner};
    wallOuterCornerTile.addRotations(3);

    Vector3D<uint8_t> wallInnerCorner = readVoxFile("vox_tiles/simple_shapes/wall_inner_corner.vox");
    Tile wallInnerCornerTile{"wallInnerCorner", wallInnerCorner};
    wallInnerCornerTile.addRotations(3);

    Vector3D<uint8_t> wall = readVoxFile("vox_tiles/simple_shapes/wall.vox");
    Tile wallTile{"wall", wall};
}