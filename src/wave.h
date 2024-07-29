#pragma once
#include "cell.h"

//propagation depth should be about double of the largest grid size
const int WAVE_PROPAGATION_DEPTH = 30;

const int WAVE_GRID_SIZE_X = 15;
const int WAVE_GRID_SIZE_Y = 15;
const int WAVE_GRID_SIZE_Z = 10;


class Wave {
    public:
        Wave(int gridWidth, int gridDepth, int gridHeight, std::vector<Tile*> tiles); 
        ~Wave();

        void printEntropy();        
        Vector3D<uint8_t> run();

    private:
        Vector3D<Cell*> grid;  

        bool observe();
        void propagate(Cell* cell, int depth);
        Vector3D<uint8_t> assemble();

        Cell* pickRandomCellWithLowestEntropy();
        Cell* pickRandomCell();
        Cell* getAdjacentCell(Cell* cell, Direction dir);
};