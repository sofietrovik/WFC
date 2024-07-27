#pragma once
#include "cell.h"

const int WAVE_PROPAGATION_DEPTH = 30;


class Wave {
    public:
        Wave(int gridWidth, int gridDepth, int gridHeight, std::vector<Tile*> tiles); 
        ~Wave();

        bool observe();
        Vector3D<uint8_t> assemble();
        void printEntropy();

    private:
        Vector3D<Cell*> grid;

        Cell* pickRandomCellWithLowestEntropy();
        Cell* pickRandomCell();
        void propagateCollapse(Cell* cell, int depth);
        Cell* getAdjacentCell(Cell* cell, Direction dir);


};