#pragma once
#include "cell.h"


class Wave {
    public:
        Wave(int gridWidth, int gridDepth, int gridHeight, std::vector<Tile*> tiles); 
        bool observe();
        Vector3D<uint8_t> assemble();
        ~Wave();
        void printEntropy();

    private:
        //void collapse();

        Cell* pickRandomCellWithLowestEntropy();

        Cell* pickRandomCell();

        Vector3D<Cell*> grid;
        void propagateCollapse(Cell* cell, int depth);
        //void propagateConstraintsToAdjacent(Cell* cell, Direction dir, const std::unordered_set<const Tile*>& allowedTiles, int depth);
        Cell* getAdjacentCell(Cell* cell, Direction dir);


};