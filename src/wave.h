#pragma once
#include "cell.h"
#include "voxParser.h"
#include <string>
#include <cstdint>
#include <queue>
#include <chrono>


const int WAVE_GRID_SIZE_X = 10;
const int WAVE_GRID_SIZE_Y = 10;
const int WAVE_GRID_SIZE_Z = 10;


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
        void depthPropagate(Cell* cell, int depth);
        void breadthPropagate(Cell* cell);
        Vector3D<uint8_t> assemble() const;

        Cell* pickRandomCellWithLowestEntropy();
        Cell* pickRandomCell();
        Cell* getAdjacentCell(Cell* cell, Direction dir);
};