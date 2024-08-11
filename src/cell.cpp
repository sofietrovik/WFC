#include "cell.h"

Cell::Cell(std::vector<Tile*> tileOptions, int x, int y, int z)
    : tileOptions(tileOptions), x(x), y(y), z(z), collapsed(false) {
        entropy = tileOptions.size();
    }

void Cell::collapse() {
    if (tileOptions.empty()) {
        throw std::runtime_error("Error: Attempting to collapse a cell with no tile options available. The algorithm has failed");
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, tileOptions.size() - 1);
    int randomIndex = dis(gen);

    tileOptions = {tileOptions[randomIndex]};
    updateEntropy();
}

bool Cell::isCollapsed() const{
    return collapsed;
}

void Cell::updateEntropy() {
    entropy = tileOptions.size();

    if (entropy == 1) {
        collapsed = true;
    }
}

int Cell::getEntropy() const {
    return entropy;
}

int Cell::getX() const {
    return x; 
}

int Cell::getY() const {
    return y;
}

int Cell::getZ() const {
    return z;
}

/**
 * Remove all tiles from tileOptions that are not in allowedTileOptions
 * 
 * 
 * @param allowedTileOptions list of the allowed tiles 
 * @return 'true' if the number of tiles in tileOptions was reduced 'false' if it was not  
*/
bool Cell::updateTileOptions(std::vector<Tile*> allowedTileOptions) {

    tileOptions.erase(
        std::remove_if(
            tileOptions.begin(), 
            tileOptions.end(), 
            [&allowedTileOptions](const Tile* tile) {
                return std::find(allowedTileOptions.begin(), allowedTileOptions.end(), tile) == allowedTileOptions.end();
            }
        ), 
        tileOptions.end()
    );

    if(tileOptions.empty()) {
        throw std::runtime_error("Error: A cell has no tile options left after an update.");
    }

    //check if the entropy has changed (check if some elements have been removed from tile options)
    if (entropy != static_cast<int>(tileOptions.size())) {
        updateEntropy();
        return true;
    }
 
    return false;
}