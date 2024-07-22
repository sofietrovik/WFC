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


// void printDirection(Direction dir) {s
//     switch (dir)
//     {
//     case FRONT:
//         std::cout << "Front";
//         break;
//     case BACK:
//         std::cout << "Back";
//         break;
//     case LEFT:
//         std::cout << "Left";
//         break;
//     case RIGHT:
//         std::cout << "Right";
//         break;
//     case TOP:
//         std::cout << "Top";
//         break;
//     case BOTTOM:
//         std::cout << "Bottom";
//         break;
//     default:
//         std::cout << "Unknown Direction";
//         break;
//     }
// }


class Tile {
    public:
        std::string name;
        Vector3D<uint8_t> voxelData;
        std::vector<std::vector<uint8_t>> faces[6]; //this is unneccessary data after the adjacency constraints are populated... should remove it

        Tile (std::string name, const Vector3D<uint8_t>& voxelData);

        void printData();
        void printFace(Direction dir) const;
        void printAllFaces() const;

        void extractFaces();

        void addRotations(); //not sure how to implement this one and keeping scopes
    
        //should be unordered sets


        bool matchFaces(const Tile& other, Direction dir);
        bool matchCenterElements(std::vector<std::vector<uint8_t>> face, std::vector<std::vector<uint8_t>> otherFace);
        bool matchAllElements(std::vector<std::vector<uint8_t>> face, std::vector<std::vector<uint8_t>> otherFace);
        void setAdjacencyConstraints();
        

        inline const std::unordered_set<const Tile*>& getAdjacencyConstraints(Direction dir) const {
            return adjacencyConstraints.at(dir);
        }

        inline std::vector<Tile*> getListOfTiles() const {
            return listOfTiles;
        }


    private:
        static std::vector<Tile*> listOfTiles;
        std::unordered_map<Direction, std::unordered_set<const Tile*>> adjacencyConstraints;
        //void extractFaces();
        

};

