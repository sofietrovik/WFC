#pragma once
#include "cell.h"
#include "voxParser.h"
#include <string>
#include <cstdint>

//propagation depth should probably be about double of the largest grid size
const int WAVE_PROPAGATION_DEPTH = 24;

const int WAVE_GRID_SIZE_X = 12;
const int WAVE_GRID_SIZE_Y = 12;
const int WAVE_GRID_SIZE_Z = 12;


//Capture intermediate models
const bool LOGGING = false; 


class Wave {
    public:
        Wave(int gridWidth, int gridDepth, int gridHeight, std::vector<Tile*> tiles); 
        ~Wave();

        void printEntropy();        
        Vector3D<uint8_t> run();

    private:
        Vector3D<Cell*> grid;  

        bool observe(std::string baseFilePath, int& coun);
        void propagate(Cell* cell, int depth);
        Vector3D<uint8_t> assemble() const;

        Cell* pickRandomCellWithLowestEntropy();
        Cell* pickRandomCell();
        Cell* getAdjacentCell(Cell* cell, Direction dir);
};