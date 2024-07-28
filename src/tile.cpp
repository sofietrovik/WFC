#include "tile.h"


Tile::Tile (std::string name, const Vector3D<uint8_t>& voxelData)
    :  name(name), voxelData(voxelData) {
    if (voxelData.dimX() != TILE_SIZE_X || voxelData.dimY() != TILE_SIZE_Y || voxelData.dimZ() != TILE_SIZE_Z) {
        throw std::runtime_error(std::string("Wrong tile dimensions"));
    }
    
    extractFaces();
    tileSet.push_back(this);;
}

void Tile::addRotations(int numRotations) const{
    Vector3D<uint8_t> newData = voxelData;

    for(int i = 0; i < numRotations; i++) {
        newData.rotateClockwise(1);
        new Tile{name + "_r" + static_cast<char>(i), newData};
    }
}


void Tile::printData() const{
    voxelData.print();
}

void Tile::printFace (Direction dir) const{
    auto face = faces[dir];
    int dimX = face.size();
    int dimY = face[0].size();


    for (int y = dimY - 1; y >= 0; y--) {
        for (int x = 0; x < dimX; x++) {
            std::cout << std::setw(3) << std::left << static_cast<int>(face[x][y]) << " ";
        }
        std::cout << std::endl;
    }
}

void printFace(std::vector<std::vector<uint8_t>> face) {
    int dimX = face.size();
    int dimY = face[0].size();

    for (int y = dimY - 1; y >= 0; y--) {
        for (int x = 0; x < dimX; x++) {
            std::cout << std::setw(3) << std::left << static_cast<int>(face[x][y]) << " ";
        }
        std::cout << std::endl;
    }   
}

void Tile::printAllFaces() const {
    for (int dir = FRONT; dir < NUM_DIRECTIONS; dir++) {
        std::cout << "\nface dir: " << dir << std::endl;
        printFace(static_cast<Direction>(dir));
    }
}


void Tile::extractFaces() {
    faces[FRONT] = std::vector<std::vector<uint8_t>>(TILE_SIZE_X, std::vector<uint8_t>(TILE_SIZE_Z));
    faces[BACK] = std::vector<std::vector<uint8_t>>(TILE_SIZE_X, std::vector<uint8_t>(TILE_SIZE_Z));
    faces[LEFT] = std::vector<std::vector<uint8_t>>(TILE_SIZE_Y, std::vector<uint8_t>(TILE_SIZE_Z));
    faces[RIGHT] = std::vector<std::vector<uint8_t>>(TILE_SIZE_Y, std::vector<uint8_t>(TILE_SIZE_Z));
    faces[TOP] = std::vector<std::vector<uint8_t>>(TILE_SIZE_X, std::vector<uint8_t>(TILE_SIZE_Y));
    faces[BOTTOM] = std::vector<std::vector<uint8_t>>(TILE_SIZE_X, std::vector<uint8_t>(TILE_SIZE_Y));

    for (int x = 0; x < TILE_SIZE_X; x++) {
        for (int z = 0; z < TILE_SIZE_Z; z++) {
            faces[FRONT][x][z] = voxelData[x][0][z];
            faces[BACK][x][z] = voxelData[x][TILE_SIZE_Y - 1][z];     
        }
    }
    
    for (int y = 0; y < TILE_SIZE_Y; y++) {
        for (int z = 0; z < TILE_SIZE_Z; z++) {
            faces[LEFT][y][z] = voxelData[0][TILE_SIZE_Y - 1 - y][z];
            faces[RIGHT][y][z] = voxelData[TILE_SIZE_X - 1][TILE_SIZE_Y - 1 - y][z];
        }
    }

    for (int x = 0; x < TILE_SIZE_X; x++) {
        for (int y = 0; y < TILE_SIZE_Y; y++) {
            faces[TOP][x][y] = voxelData[x][y][TILE_SIZE_Z - 1]; 
            faces[BOTTOM][x][y] = voxelData[x][y][0]; 
        }
    }
}

std::vector<std::vector<uint8_t>> findCenterElements(const std::vector<std::vector<uint8_t>>& array) {
    std::vector<std::vector<uint8_t>> centers;

    size_t numRows = array.size();
    if (numRows == 0) return centers;  // Return empty if the array is empty

    size_t numCols = array[0].size();
    if (numCols == 0) return centers;  // Return empty if any row is empty

    size_t centerRow = numRows / 2;
    size_t centerCol = numCols / 2;

    if (numRows % 2 == 1 && numCols % 2 == 1) {
        centers.push_back({array[centerRow][centerCol]});
    } else if (numRows % 2 == 1 && numCols % 2 == 0) {
        centers.push_back({array[centerRow][centerCol - 1], array[centerRow][centerCol]});
    } else if (numRows % 2 == 0 && numCols % 2 == 1) {
        centers.push_back({array[centerRow - 1][centerCol]});
        centers.push_back({array[centerRow][centerCol]});
    } else {
        // Both dimensions are even
        centers.push_back({array[centerRow - 1][centerCol - 1], array[centerRow - 1][centerCol]});
        centers.push_back({array[centerRow][centerCol - 1], array[centerRow][centerCol]});
    }
    return centers;
}






/**
 * Check if the @param other tile can be placed next to the this tile in @param dir direction. 
 * 
 * Contains logic for extracting the right faces according to @param dir,
 * and will match based on a matching function called in the return statement.  
 * 
 * @return true if the faces are matching, false if not
*/
bool Tile::matchFaces(const Tile& other, Direction dir) {

    std::vector<std::vector<uint8_t>> face = this->faces[dir];
    std::vector<std::vector<uint8_t>> otherFace;


    switch (dir)
    {
    case FRONT:
        otherFace = other.faces[BACK];
        break;
    case BACK:
        otherFace = other.faces[FRONT];
        break;
    case LEFT:
        otherFace = other.faces[RIGHT];
        break;
    case RIGHT:
        otherFace = other.faces[LEFT];
        break;
    case TOP:
        otherFace = other.faces[BOTTOM];
        break;
    case BOTTOM:
        otherFace = other.faces[TOP];
        break;
    
    default:
        break;
    }
    
    if (face.size() != otherFace.size()) {
        return false;
    }
    if (face[0].size() != otherFace[0].size()) {
        return false;
    }

    return matchAllElements(face, otherFace);
}

bool Tile::matchCenterElements(std::vector<std::vector<uint8_t>> face, std::vector<std::vector<uint8_t>> otherFace) {
    std::vector<std::vector<uint8_t>> center = findCenterElements(face); 
    std::vector<std::vector<uint8_t>> otherCenter = findCenterElements(otherFace);
    
    size_t numRows = center.size();
    size_t numCols = center[0].size();

    for (size_t x = 0; x < numRows; x++) {
        for (size_t y = 0; y < numCols; y++) {
            if (center[x][y] != otherCenter[x][y]) {
                return false;
            }
        }
    }
    return true;
}

bool Tile::matchAllElements(std::vector<std::vector<uint8_t>> face, std::vector<std::vector<uint8_t>> otherFace) {
    size_t numRows = face.size();
    size_t numCols = face[0].size();
    int errorCount = 0;

    int numElements = numRows*numCols;
    int allowedErrorCount = numElements*ERROR_PERCENTAGE_THRESHOLD/100;

    for (size_t x = 0; x < numRows; x++) {
        for (size_t y = 0; y < numCols; y++) {
            if (face[x][y] != otherFace[x][y]) {
                errorCount++;
                if (errorCount > allowedErrorCount) {
                    return false;
                }      
            }
        }
    }
    return true;
}


void Tile::setAdjacencyConstraints() {
    for (int dir = FRONT; dir < NUM_DIRECTIONS; dir++) {
        adjacencyConstraints[static_cast<Direction>(dir)] = std::unordered_set<const Tile*>();
    }

    for (const Tile* tile : tileSet) {
        for (int dir = FRONT; dir < NUM_DIRECTIONS; dir++) {
            if(this->matchFaces(*tile, static_cast<Direction>(dir)) == false) {
                continue;
            }
            adjacencyConstraints[static_cast<Direction>(dir)].insert(tile);
        }
    }
}

std::vector<Tile*> Tile::tileSet;

//kinda... hacky
Tile::~Tile() {
    for (auto tile : tileSet) {
        if (tile->name == (this->name + "_r1")||
            tile->name == (this->name + "_r2")||
            tile->name == (this->name + "_r3")||
            tile->name == (this->name + "_r4")) {
            delete tile;
        }
    } 
}
