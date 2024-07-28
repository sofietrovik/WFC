#include "cell.h"

Cell::Cell(std::vector<Tile*> tileOptions, int x, int y, int z)
    : tileOptions(tileOptions), x(x), y(y), z(z), collapsed(false) {
        entropy = tileOptions.size();
    }

bool Cell::collapse() {
    if (tileOptions.empty()) {
        std::cerr << "Error: Attempting to collapse a cell with no tile options available." << std::endl;
        return false;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, tileOptions.size() - 1);
    int randomIndex = dis(gen);

    tileOptions = {tileOptions[randomIndex]};

    updateEntropy();
    
    return true;
}

bool Cell::isCollapsed() const{
    return collapsed;
}

void Cell::updateEntropy() {
    entropy = tileOptions.size();

    //a cell has been collapsed by propagation of another collapse
    if (entropy == 1) {
        collapsed = true;
        //std::cout << "\n x: " << x << "y: " << y << "z: " << z << " has been collapsed \n"; 
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
    //TODO: improve by sorting tileOptions before initializing, so that I can binary_search?

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
        std::cerr << "\na cell has no tile options left\n";
        exit(1);
    }

    //check if the entropy has changed (check if some elements have been removed from tile options)
    if (entropy != static_cast<int>(tileOptions.size())) {
        updateEntropy();
        return true;
    }

 
    return false;
}