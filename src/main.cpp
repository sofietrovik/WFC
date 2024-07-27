
#include <iostream>

#include "cell.h"
#include "voxParser.h"
//#include "vector3D.h"
#include "wave.h"



std::vector<Tile*> initRiverTiles() {
    Vector3D<uint8_t> data = readVoxFile("vox_tiles/simple_shapes/wall_inner_corner_ground.vox");
    Tile tile{"", data};
    data.rotateClockwise(1);
    Tile tile_r1{"", data};
    data.rotateClockwise(1);
    Tile tile_r2{"", data};
    data.rotateClockwise(1);
    Tile tile_r3{"", data};


    Vector3D<uint8_t> otherData = readVoxFile("vox_tiles/simple_shapes/wall_outer_corner_ground.vox");
    Tile otherTile{"", otherData};
    otherData.rotateClockwise(1);
    Tile otherTile_r1{"", otherData};
    otherData.rotateClockwise(1);
    Tile otherTile_r2{"", otherData};
    otherData.rotateClockwise(1);
    Tile otherTile_r3{"", otherData};  
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
    stair.rotateClockwise(1);
    Tile stairTile_r1{"stair_r1", stair};
    stair.rotateClockwise(1);
    Tile stairTile_r2{"stair_r2", stair};
    stair.rotateClockwise(1); 
    Tile stairTile_r3{"stair_r3", stair};


    Vector3D<uint8_t> empty = readVoxFile("vox_tiles/stairs/empty.vox");
    Tile emptyTile{"empty", empty};

    // Vector3D<uint8_t> stair_bottom_corner = readVoxFile("vox_tiles/stairs/stair_bottom_corner.vox");
    // Tile stair_bottom_cornerTile{"stair_bottom_corner", stair_bottom_corner};
    // stair_bottom_corner.rotateClockwise(1);
    // Tile stair_bottom_cornerTile_r1{"stair_bottom_corner_r1", stair_bottom_corner};
    // stair_bottom_corner.rotateClockwise(1);
    // Tile stair_bottom_cornerTile_r2{"stair_bottom_corner_r2", stair_bottom_corner};
    // stair_bottom_corner.rotateClockwise(1); 
    // Tile stair_bottom_cornerTile_r3{"stair_bottom_corner_r3", stair_bottom_corner};


    Vector3D<uint8_t> stair_top_corner = readVoxFile("vox_tiles/stairs/stair_top_corner.vox");
    Tile stair_top_cornerTile{"stair_top_corner", stair_top_corner};
    stair_top_corner.rotateClockwise(1);
    Tile stair_top_cornerTile_r1{"stair_top_corner_r1", stair_top_corner};
    stair_top_corner.rotateClockwise(1);
    Tile stair_top_cornerTile_r2{"stair_top_corner_r2", stair_top_corner};
    stair_top_corner.rotateClockwise(1); 
    Tile stair_top_cornerTile_r3{"stair_top_corner_r3", stair_top_corner};


    // Vector3D<uint8_t> straight_path = readVoxFile("vox_tiles/stairs/straight_path.vox");
    // Tile straight_pathTile{"straight_path", straight_path};
    // straight_path.rotateClockwise(1);
    // Tile straight_pathTile_r1{"straight_path_r1", straight_path};
    // straight_path.rotateClockwise(1);
    // Tile straight_pathTile_r2{"straight_path_r2", straight_path};
    // straight_path.rotateClockwise(1); 
    // Tile straight_pathTile_r3{"straight_path_r3", straight_path};

    // Vector3D<uint8_t> bendy_path = readVoxFile("vox_tiles/stairs/bendy_path.vox");
    // Tile bendy_pathTile{"bendy_path", bendy_path};
    // bendy_path.rotateClockwise(1);
    // Tile bendy_pathTile_r1{"bendy_path_r1", bendy_path};
    // bendy_path.rotateClockwise(1);
    // Tile bendy_pathTile_r2{"bendy_path_r2", bendy_path};
    // bendy_path.rotateClockwise(1); 
    // Tile bendy_pathTile_r3{"bendy_path_r3", bendy_path};
    
 


    std::vector<Tile*> tileOptions = emptyTile.getListOfTiles();
    Wave wave{15,15, 15, emptyTile.getListOfTiles()};



    while(wave.observe()) {        
        std::cout << "\nobserving ... \n";
        
    }

    Vector3D<uint8_t> model = wave.assemble();

    writeVoxFile(model, "vox_tiles/output.vox");
    



    openInMagicaVoxel("C:/Users/sofie/OneDrive/Documents/master/WFC/vox_tiles/output.vox", magicaPath);

    return 0;
}