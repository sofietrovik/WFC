#include "wave.h"
#include <filesystem>


Wave::Wave(int gridWidth,  int gridDepth, int gridHeight, std::vector<Tile*> tileSet) {
    
    for (auto tile:tileSet) {
        tile->setAdjacencyConstraints(tileSet);
        //tile->printAdjacencyConstraints();
    }
    //exit(1);

    grid.resize(gridWidth, gridDepth, gridHeight);

    //initialize 3d grid of cells
    for (int x = 0; x < gridWidth; x++) {
        for (int y = 0; y < gridDepth; y++) {
            for (int z = 0; z < gridHeight; z++) {
                Cell *cellPtr = new Cell{tileSet, x, y, z};
                grid[x][y][z] = cellPtr;
            }
        }
    }
}



/**
 * Pick and collapse a cell in the wave grid
 * 
 * @return true if a cell was collapsed, false if not (all cells are collapsed)
*/
bool Wave::observe(std::string baseFilepath, int& count) {
   
    Cell* randomCell = pickRandomCellWithLowestEntropy();

    if(randomCell == nullptr) {
        //all cells are collapsed
        return false;
    }

    randomCell->collapse();

    if (LOGGING) {
        count++;
        std::string filepath = baseFilepath + std::to_string(count) + "_observe" + ".vox";             
        writeVoxFile(assemble(), filepath.c_str());
        }  

    //depthPropagate(randomCell, 100000);
    breadthPropagate(randomCell);


    return true;
}
 


/**
 * The function will go through all the six adjacent cells of the cell input and 
 * remove invalid tile options based on the tile options of the calling cell
 * 
 * It will be recursivly called for the adjacent cells if their tileOptions were
 * updated, and quit if the recursiveness reaches a certain depth
 * 
 * @param cell cell object that has had its tileOptions updated.
 * @param depth maximum depth of the propagation in terms of number of cells traversed from the input cell
*/
void Wave::depthPropagate(Cell* cell, int depth) {
    depth = depth - 1;
    if (depth < 0) {
        return;
    }
    
    for (Direction dir : {FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM}) {
        Cell* adjacentCell = getAdjacentCell(cell, dir);

        if (adjacentCell == nullptr || adjacentCell->isCollapsed()) {
            continue;
        }
        if (adjacentCell == nullptr) {
            continue;
        }

        std::unordered_set<const Tile*> uniqueConstraints;
        for (auto tile : cell->tileOptions) {            
            std::unordered_set<const Tile*> constraints = tile->getAdjacencyConstraints(dir);
            uniqueConstraints.insert(constraints.begin(), constraints.end());
        }

        std::vector<Tile*> allowedTileOptions;
        for (const Tile* tile : uniqueConstraints) {
            allowedTileOptions.push_back(const_cast<Tile*>(tile));
        }

        bool updated = adjacentCell->updateTileOptions(allowedTileOptions);
        if (updated) {
            depthPropagate(adjacentCell, depth);
        }        
    }
}



void Wave::breadthPropagate(Cell* startCell) {
    std::queue<Cell*> queue;
    queue.push(startCell);

    while (!queue.empty()) {
        auto cell = queue.front();
        queue.pop();

        for (Direction dir : {FRONT, BACK, LEFT, RIGHT, TOP, BOTTOM}) {
            Cell* adjacentCell = getAdjacentCell(cell, dir);

            if (adjacentCell == nullptr || adjacentCell->isCollapsed()) {
                continue;
            }

            std::unordered_set<const Tile*> uniqueConstraints;
            for (auto tile : cell->tileOptions) {            
                std::unordered_set<const Tile*> constraints = tile->getAdjacencyConstraints(dir);
                uniqueConstraints.insert(constraints.begin(), constraints.end());
            }

            std::vector<Tile*> allowedTileOptions;
            for (const Tile* tile : uniqueConstraints) {
                allowedTileOptions.push_back(const_cast<Tile*>(tile));
            }

            bool updated = adjacentCell->updateTileOptions(allowedTileOptions);
            if (updated) {
                queue.push(adjacentCell);
            }
        }
    }
}



Cell* Wave::getAdjacentCell(Cell* cell, Direction dir) {
    switch (dir) {
        case TOP:
            if (cell->getZ() + 1 < grid.dimZ())
                return grid[cell->getX()][cell->getY()][cell->getZ() + 1];
            break;
        case BOTTOM:
            if (cell->getZ() - 1 >= 0)
                return grid[cell->getX()][cell->getY()][cell->getZ() - 1];
            break;
        case LEFT:
            if (cell->getX() - 1 >= 0) 
                return grid[cell->getX() - 1][cell->getY()][cell->getZ()];
            break;
        case RIGHT:
            if (cell->getX() + 1 < grid.dimX())
                return grid[cell->getX() + 1][cell->getY()][cell->getZ()];
            break;
        case BACK:
            if (cell->getY() + 1 < grid.dimY())
                return grid[cell->getX()][cell->getY() + 1][cell->getZ()];
            break;
        case FRONT:
            if (cell->getY() - 1 >= 0) 
                return grid[cell->getX()][cell->getY() - 1][cell->getZ()];
            break;
        default:
            return nullptr;
    }
    return nullptr; 
}


void Wave::printEntropy() {
    std::cout << "\n-ENTROPY OF GRID-\n";
    for (size_t z = 0; z < grid.dimZ(); z++) {
        for (int y = grid.dimY() - 1; y >= 0; y--) {
            for (size_t x = 0; x < grid.dimX(); x++) {
                int entropy = grid[x][y][z]->getEntropy();
                std::cout << entropy << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }    
}

/** 
 * Picks a random cell from the uncollapsed cells with the lowest entropy in the wave grid.
 * 
 * 
 * @return The chosen cell
*/
Cell* Wave::pickRandomCellWithLowestEntropy() {

    std::vector<Cell*> flattenedGrid = grid.flatten();

    //remove all collapsed cells
    flattenedGrid.erase(
        std::remove_if(
            flattenedGrid.begin(), 
            flattenedGrid.end(),
            [](Cell* cell) { 
                return cell->isCollapsed(); 
            }
        ),
        flattenedGrid.end()
    );


    if (flattenedGrid.empty()) {
        //all cells are collapsed
        return nullptr;
    }

    //find the minimum entropy among the remaining cells
    int minEntropy = std::numeric_limits<int>::max();
    for (const auto& cell : flattenedGrid) {
        int entropy = cell->getEntropy();
        if (entropy < minEntropy) {
            minEntropy = entropy;
        }
    }
    
    //filter cells to include only those with the minimum entropy
    std::vector<Cell*> minEntropyCells; 
    std::copy_if(flattenedGrid.begin(), flattenedGrid.end(), std::back_inserter(minEntropyCells),
                 [minEntropy](Cell* cell) { return cell->getEntropy() == minEntropy; });

    //randomly pick a cell from the cells with the minimum entropy
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, minEntropyCells.size() - 1);
    int randomIndex = dis(gen);

    return minEntropyCells[randomIndex]; 

}


/**
 * Pick a random cell from the grid that is not collapsed
 * 
 * 
 * @return Random cell from grid
*/
Cell* Wave::pickRandomCell() {
    std::vector<Cell*> flattenedGrid = grid.flatten();

    //remove all collapsed cells from flattened grid
    flattenedGrid.erase(
        std::remove_if(
            flattenedGrid.begin(), 
            flattenedGrid.end(),
            [](Cell* cell) { 
                return cell->isCollapsed(); 
            }
        ),
        flattenedGrid.end()
    );


    if (flattenedGrid.empty()) {
        //all cells are collapsed
        return nullptr;
    }
    
    // pick random collapsed cell
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, flattenedGrid.size() - 1);
    int randomIndex = dis(gen);

    return flattenedGrid[randomIndex];    
}

/**
 * Go through all the cells in the grid. Construct a new vector3D and copying 
 * the data from the tiles the cells collapsed into.
 * 
 * 
 * @return 3D vector of the assembled tiles
*/
Vector3D<uint8_t> Wave::assemble() const{
    Vector3D<uint8_t> finalModel;
    
    finalModel.resize(grid.dimX()*TILE_SIZE_X, grid.dimY()*TILE_SIZE_Y, grid.dimZ()*TILE_SIZE_Z);

    //TODO: legg inn sjekk for at modellen ikke blir større enn det magicavoxel kan tåle


    for (size_t i = 0; i < grid.dimX(); i++) {
        for (size_t j = 0; j < grid.dimY(); j++) {
            for (size_t k = 0; k < grid.dimZ(); k++) {
                Tile* tile;

                if (grid[i][j][k]->isCollapsed()) {
                    tile = grid[i][j][k]->tileOptions[0];
                } else {
                    //std::cerr << "found empty slot in grid at x: " << i << ", y: "<< j << "z: "<< k << std::endl;
                    continue;
                }
                
                //copy tile data into final model
                for (int x = 0; x < TILE_SIZE_X; x++) {
                    for (int y = 0; y < TILE_SIZE_Y; y++) {
                        for (int z = 0; z < TILE_SIZE_Z; z++) {
                            finalModel[i*TILE_SIZE_X + x][j*TILE_SIZE_Y + y][k*TILE_SIZE_Z + z] = tile->getVoxelData(x, y, z);
                        }
                    }
                }    
            }
        }
    }
    return finalModel;
}


Vector3D<uint8_t> Wave::run() {

    std::string baseFilepath = "vox_tiles/output_log/";
    std::string filetype = ".vox";
    std::string filepath;
    int count = 0;

    if (LOGGING) {
        using namespace std::filesystem;
        std::error_code ec;
        remove_all("vox_tiles/output_log", ec);
        if (ec) {
            std::cerr << "Error removing directory: " << ec.message() << "\n";
        } else {
            create_directory("vox_tiles/output_log", ec);
            if (ec) {
                std::cerr << "Error creating directory: " << ec.message() << "\n";
            }
        }
    }
    auto start = std::chrono::high_resolution_clock::now();
    while(observe(baseFilepath, count)) {
        if (LOGGING) {
            filepath = baseFilepath + std::to_string(count) + "_propagate" +  filetype;             
            writeVoxFile(assemble(), filepath.c_str());
        }   
        
        //std::cout << "observing ...";
    }
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;

    return assemble();    
}




Wave::~Wave() {
    size_t gridWidth = grid.dimX();
    size_t gridDepth = grid.dimY();
    size_t gridHeight = grid.dimZ();

    for (size_t x = 0; x < gridWidth; x++) {
        for (size_t y = 0; y < gridDepth; y++) {
            for (size_t z = 0; z < gridHeight; z++) {
                delete grid[x][y][z];
            }
        }
    }
}
