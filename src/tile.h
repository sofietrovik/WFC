#pragma once


//#include "Vector3D.h"
#include <iostream>
#include <cstdint>
#include "voxParser.h"
#include <iomanip> 
#include <unordered_map>
#include <unordered_set>


const int TILE_SIZE_X = 16;
const int TILE_SIZE_Y = 16;  
const int TILE_SIZE_Z = 16;

const int NUM_DIRECTIONS = 6;
enum Direction {FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM};

const double ERROR_PERCENTAGE_THRESHOLD = 0;



class Tile {
    public:

        Tile (std::string name, const Vector3D<uint8_t>& voxelData);

        void printData() const;
        void printFace(Direction dir) const;
        void printAllFaces() const;

        
        void addRotations(int numRotations) const;
        void setAdjacencyConstraints();

        

        inline const std::unordered_set<const Tile*>& getAdjacencyConstraints(Direction dir) const {
            return adjacencyConstraints.at(dir);
        }

        inline std::vector<Tile*> getTileSet() const {
            return tileSet;
        }        
        
        inline uint8_t getVoxelData(int x, int y, int z) const {
            return voxelData[x][y][z];
        }


    private:
        std::string name;
        Vector3D<uint8_t> voxelData;
        std::vector<std::vector<uint8_t>> faces[6]; 

        static std::vector<Tile*> tileSet;
        std::unordered_map<Direction, std::unordered_set<const Tile*>> adjacencyConstraints;


        bool matchFaces(const Tile& other, Direction dir);
        bool matchCenterElements(std::vector<std::vector<uint8_t>> face, std::vector<std::vector<uint8_t>> otherFace);
        bool matchAllElements(std::vector<std::vector<uint8_t>> face, std::vector<std::vector<uint8_t>> otherFace);
        void extractFaces();
};

