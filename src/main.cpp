
#include <iostream>

#include "voxParser.h"
#include "wave.h"




int main() {

    std::string magicaPath = "C:/Program Files/MagicaVoxel-0.99.7.1-win64/MagicaVoxel.exe";




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

}