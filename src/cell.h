#pragma once

#include "tile.h"

#include <random>
#include <algorithm>

//forward declaration of Wave to make it a friend class
class Wave;

class Cell {
    public:
        bool isCollapsed() const;
        int getEntropy() const;
        int getX() const;
        int getY() const;
        int getZ() const;

        //enforce composition relationship with Wave class
        Cell() = delete;

    private:
        Cell(std::vector<Tile*> tileOptions, int x, int y, int z);

        //coordinates in wave grid
        int x;
        int y;
        int z;   

        bool collapsed;
        int entropy;
        std::vector<Tile*> tileOptions;

        void collapse();  
        void updateEntropy();
        bool updateTileOptions(std::vector<Tile*> allowedTileOptions);

        friend class Wave;
};



