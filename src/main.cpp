
#include <iostream>

#include "cell.h"
#include "voxParser.h"
//#include "vector3D.h"
#include "wave.h"



// std::vector<Tile*> initRiverTiles() {
//     Vector3D<uint8_t> data = readVoxFile("vox_tiles/simple_shapes/wall_inner_corner_ground.vox");
//     Tile tile{"", data};
//     data.rotateClockwise(1);
//     Tile tile_r1{"", data};
//     data.rotateClockwise(1);
//     Tile tile_r2{"", data};
//     data.rotateClockwise(1);
//     Tile tile_r3{"", data};


//     Vector3D<uint8_t> otherData = readVoxFile("vox_tiles/simple_shapes/wall_outer_corner_ground.vox");
//     Tile otherTile{"", otherData};
//     otherData.rotateClockwise(1);
//     Tile otherTile_r1{"", otherData};
//     otherData.rotateClockwise(1);
//     Tile otherTile_r2{"", otherData};
//     otherData.rotateClockwise(1);
//     Tile otherTile_r3{"", otherData};  
// }


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




int main() {

    std::string magicaPath = "C:/Program Files/MagicaVoxel-0.99.7.1-win64/MagicaVoxel.exe";







    // Vector3D<uint8_t> data = readVoxFile("vox_tiles/simple_shapes/wall_inner_corner_ground.vox"); 
    // Tile tile{"", data};
    // data.rotateClockwise(1);
    // Tile tile_r1{"", data};
    // data.rotateClockwise(1);
    // Tile tile_r2{"", data};
    // data.rotateClockwise(1);
    // Tile tile_r3{"", data};


    // Vector3D<uint8_t> otherData = readVoxFile("vox_tiles/simple_shapes/wall_outer_corner_ground.vox");
    // Tile otherTile{"wallOuterCornerGround", otherData};
    // otherData.rotateClockwise(1);
    // Tile otherTile_r1{"wallOuterCornerGround_r1", otherData};
    // otherData.rotateClockwise(1);
    // Tile otherTile_r2{"wallOuterCornerGround_r2", otherData};
    // otherData.rotateClockwise(1);
    // Tile otherTile_r3{"wallOuterCornerGround_r3", otherData};

    // Vector3D<uint8_t> sky = readVoxFile("vox_tiles/simple_shapes/sky.vox");
    // Tile skyTile{"sky", sky};

    // Vector3D<uint8_t> ground = readVoxFile("vox_tiles/simple_shapes/ground.vox");
    // Tile groundTile{"ground", ground};


    // Vector3D<uint8_t> halfWallGround = readVoxFile("vox_tiles/simple_shapes/half_wall_ground.vox");
    // Tile halfWallGroundTile{"halfWallGround", halfWallGround};

    // Vector3D<uint8_t> halfWallTop = readVoxFile("vox_tiles/simple_shapes/half_wall_top.vox");
    // Tile halfWallTopTile{"halfWallTop", halfWallTop};
    // halfWallTop.rotateClockwise(1);
    // Tile halfWallTopTile_r1{"halfWallTop_r1", halfWallTop};
    // halfWallTop.rotateClockwise(1);
    // Tile halfWallTopTile_r2{"halfWallTop_r2", halfWallTop};
    // halfWallTop.rotateClockwise(1);
    // Tile halfWallTopTile_r3{"halfWallTop_r3", halfWallTop};

    // Vector3D<uint8_t> skyGround = readVoxFile("vox_tiles/simple_shapes/sky_ground.vox");
    // Tile skyGroundTile{"skyGround", skyGround};

    // Vector3D<uint8_t> wallInnerCornerTop = readVoxFile("vox_tiles/simple_shapes/wall_inner_corner_top.vox");
    // Tile wallInnerCornerTopTile{"wallInnerCornerTop", wallInnerCornerTop};
    // wallInnerCornerTop.rotateClockwise(1);
    // Tile wallInnerCornerTopTile_r1{"wallInnerCornerTop_r1", wallInnerCornerTop};
    // wallInnerCornerTop.rotateClockwise(1);
    // Tile wallInnerCornerTopTile_r2{"wallInnerCornerTop_r2", wallInnerCornerTop};
    // wallInnerCornerTop.rotateClockwise(1);
    // Tile wallInnerCornerTopTile_r3{"wallInnerCornerTop_r3", wallInnerCornerTop}; 

    // Vector3D<uint8_t> wallOuterCornerTop = readVoxFile("vox_tiles/simple_shapes/wall_outer_corner_top.vox");
    // Tile wallOuterCornerTopTile{"wallOuterCornerTop", wallOuterCornerTop};
    // wallOuterCornerTop.rotateClockwise(1);
    // Tile wallOuterCornerTopTile_r1{"wallOuterCornerTop_r1", wallOuterCornerTop};
    // wallOuterCornerTop.rotateClockwise(1);
    // Tile wallOuterCornerTopTile_r2{"wallOuterCornerTop_r2", wallOuterCornerTop};
    // wallOuterCornerTop.rotateClockwise(1);
    // Tile wallOuterCornerTopTile_r3{"wallOuterCornerTop_r3", wallOuterCornerTop}; 

    // Vector3D<uint8_t> wallOuterCorner = readVoxFile("vox_tiles/simple_shapes/wall_outer_corner.vox");
    // Tile wallOuterCornerTile{"wallOuterCorner", wallOuterCorner};
    // wallOuterCorner.rotateClockwise(1);
    // Tile wallOuterCornerTile_r1{"wallOuterCorner_r1", wallOuterCorner};
    // wallOuterCorner.rotateClockwise(1);
    // Tile wallOuterCornerTile_r2{"wallOuterCorner_r2", wallOuterCorner};
    // wallOuterCorner.rotateClockwise(1);
    // Tile wallOuterCornerTile_r3{"wallOuterCorner_r3", wallOuterCorner}; 

    // Vector3D<uint8_t> wallInnerCorner = readVoxFile("vox_tiles/simple_shapes/wall_inner_corner.vox");
    // Tile wallInnerCornerTile{"wallInnerCorner", wallInnerCorner};
    // wallInnerCorner.rotateClockwise(1);
    // Tile wallInnerCornerTile_r1{"wallInnerCorner_r1", wallInnerCorner};
    // wallInnerCorner.rotateClockwise(1);
    // Tile wallInnerCornerTile_r2{"wallInnerCorner_r2", wallInnerCorner};
    // wallInnerCorner.rotateClockwise(1);
    // Tile wallInnerCornerTile_r3{"wallInnerCorner_r3", wallInnerCorner}; 

    // Vector3D<uint8_t> wall = readVoxFile("vox_tiles/simple_shapes/wall.vox");
    // Tile wallTile{"wall", wall};
    // wall.rotateClockwise(1);
    // Tile wallTile_r1{"wall_r1", wall};
    // wall.rotateClockwise(1);
    // Tile wallTile_r2{"wall_r2", wall};
    // wall.rotateClockwise(1); 
    // Tile wallTile_r3{"wall_r3", wall};

    //-------------STAIRS--------------

    Vector3D<uint8_t> stair = readVoxFile("vox_tiles/stairs/big_stair.vox");
    Tile stairTile{"stair", stair};
    stairTile.addRotations(3);


    Vector3D<uint8_t> empty = readVoxFile("vox_tiles/stairs/empty.vox");
    Tile emptyTile{"empty", empty};


    Vector3D<uint8_t> stair_top_corner = readVoxFile("vox_tiles/stairs/stair_top_corner.vox");
    Tile stair_top_cornerTile{"stair_top_corner", stair_top_corner};
    stair_top_cornerTile.addRotations(3);


    std::vector<Tile*> tileSet = emptyTile.getTileSet();
    Wave wave{WAVE_GRID_SIZE_X, WAVE_GRID_SIZE_Y, WAVE_GRID_SIZE_Z, tileSet};

    Vector3D<uint8_t> model = wave.run();

    writeVoxFile(model, "vox_tiles/output.vox");
    openInMagicaVoxel("C:/Users/sofie/OneDrive/Documents/master/WFC/vox_tiles/output.vox", magicaPath);

    return 0;
}