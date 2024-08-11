#pragma once
#include "cell.h"
#include "voxParser.h"
#include <string>
#include <cstdint>
#include <queue>
#include <chrono>

//propagation depth should probably be about double of the largest grid size
const int WAVE_PROPAGATION_DEPTH = 10000;

const int WAVE_GRID_SIZE_X = 30;
const int WAVE_GRID_SIZE_Y = 30;
const int WAVE_GRID_SIZE_Z = 30;


//capture intermediate models
const bool LOGGING = false; 


class Wave {
    public:
        Wave(int gridWidth, int gridDepth, int gridHeight, std::vector<Tile*> tiles); 
        ~Wave();

        void printEntropy();        
        Vector3D<uint8_t> run();

    private:
        Vector3D<Cell*> grid;  

        bool observe(std::string baseFilePath, int& count);
        void propagate(Cell* cell, int depth);
        void breadthPropagate(Cell* cell);
        Vector3D<uint8_t> assemble() const;

        Cell* pickRandomCellWithLowestEntropy();
        Cell* pickRandomCell();
        Cell* getAdjacentCell(Cell* cell, Direction dir);
};