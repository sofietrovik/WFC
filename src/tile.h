#pragma once


#include <iostream>
#include <cstdint>
#include <iomanip> 
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <algorithm>
#include "voxParser.h"



const int TILE_SIZE_X = 8;
const int TILE_SIZE_Y = 8;  
const int TILE_SIZE_Z = 8;

const int NUM_DIRECTIONS = 6;
enum Direction {FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM};

const double ERROR_PERCENTAGE_THRESHOLD = 0;



class Tile {
    public:

        Tile (std::string name, const Vector3D<uint8_t>& voxelData, std::vector<Tile*>& tileSet);
        ~Tile();
        
        void addRotations(int numRotations, std::vector<Tile*>& tileSet) const;
        void setAdjacencyConstraints(std::vector<Tile*> tileSet);
        const std::unordered_set<const Tile*>& getAdjacencyConstraints(Direction dir) const {
            return adjacencyConstraints.at(dir);
        }       
        uint8_t getVoxelData(int x, int y, int z) const {
            return voxelData[x][y][z];
        }

        void printData() const;
        void printFace(Direction dir) const;
        void printAllFaces() const;
        void printAdjacencyConstraints() const;


    private:
        std::string name;
        Vector3D<uint8_t> voxelData;
        std::vector<std::vector<uint8_t>> faces[NUM_DIRECTIONS]; 
        std::unordered_map<Direction, std::unordered_set<const Tile*>> adjacencyConstraints;

        void extractFaces();
        bool matchFaces(const Tile& other, Direction dir);
        bool matchCenterElements(std::vector<std::vector<uint8_t>> face, std::vector<std::vector<uint8_t>> otherFace);
        bool matchAllElements(std::vector<std::vector<uint8_t>> face, std::vector<std::vector<uint8_t>> otherFace);
        
};

