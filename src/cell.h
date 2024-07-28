#pragma once

#include "tile.h"

#include <random>
#include <algorithm>

class Cell {
    public:
        Cell(std::vector<Tile*> tileOptions, int x, int y, int z);
        bool collapse(); 
        bool isCollapsed() const;
        std::vector<Tile*> tileOptions;
        bool updateTileOptions(std::vector<Tile*> allowedTileOptions);

        int getEntropy() const;
        int getX() const;
        int getY() const;
        int getZ() const;

    private:
        
        bool collapsed;
        int entropy;

        //coordinates in wave grid
        int x;
        int y;
        int z;

        void updateEntropy();
        void print();
};



