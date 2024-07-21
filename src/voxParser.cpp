
#include "voxParser.h"

// Helper function to create a uint32_t from ASCII characters at compile time
constexpr uint32_t makeVoxChunkID(const uint8_t a, const uint8_t b, const uint8_t c, const uint8_t d) {
    return a | (b << 8) | (c << 16) | (d << 24);
}

constexpr uint32_t FILE_HEADER_VOX  = makeVoxChunkID('V', 'O', 'X', ' ');
constexpr uint32_t FILE_HEADER_VERSION = makeVoxChunkID(200, 0, 0, 0);


constexpr uint32_t CHUNK_ID_MAIN = makeVoxChunkID('M', 'A', 'I', 'N');
constexpr uint32_t CHUNK_ID_PACK = makeVoxChunkID('P', 'A', 'C', 'K');
constexpr uint32_t CHUNK_ID_SIZE = makeVoxChunkID('S', 'I', 'Z', 'E');
constexpr uint32_t CHUNK_ID_XYZI = makeVoxChunkID('X', 'Y', 'Z', 'I');



bool isValidVoxFile(std::ifstream& file) {
    uint32_t fileHeader;
    uint32_t fileVersion;

    file.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));
    file.read(reinterpret_cast<char*>(&fileVersion), sizeof(fileVersion));

    //check if first word is "VOX " and second word is 150 or 200 (valid vox versions)
    if(fileHeader == FILE_HEADER_VOX && (fileVersion == 200 || fileVersion == 150)) {
        return true;
    }

    return false;
}

void printBinary(const char* filePath, int numWords) {
    std::ifstream file(filePath, std::ios::binary);

    if (!file) {
        std::cerr << "Error: Failed to open file " << filePath << std::endl;
        return;
    }

    char data;
    int count = 0;

    int wordCount = 0;


    while (file.read(&data, sizeof(data)) && wordCount < numWords) {
        std::bitset<8> bits(data);
        std::cout << bits << " ";
        count++;

        if (count == 4) {
            std::cout << std::endl;
            count = 0;
            wordCount++;
        }


    }

    file.close();

}


Vector3D<uint8_t> readVoxFile(const char* filePath) {
    std::ifstream file(filePath, std::ios::binary);

    if (!file.is_open()) {
        throw std::runtime_error(std::string("Failed to open .vox file: ") + filePath);;
    }

    if (!isValidVoxFile(file)) {
        throw std::runtime_error(std::string("Invalid .vox file format in file: ") + filePath);
    }

    Vector3D<uint8_t> voxelData;

    uint32_t chunkID;
    int voxelCount = 0;

    while (file.read(reinterpret_cast<char*>(&chunkID), sizeof(chunkID))){
        uint32_t numBytesChunkContent;
        uint32_t numBytesChildrenChunkContent;

        file.read(reinterpret_cast<char*>(&numBytesChunkContent), sizeof(numBytesChunkContent));
        file.read(reinterpret_cast<char*>(&numBytesChildrenChunkContent), sizeof(numBytesChildrenChunkContent));
        

        switch (chunkID)
        {
        case CHUNK_ID_MAIN:
            // std::cout << "MAIN chunk \n";

            // std::cout << "num bytes of chunk content: " << static_cast<int>(numBytesChunkContent) << std::endl;
            // std::cout << "num bytes of children chunk content: " << static_cast<int>(numBytesChildrenChunkContent) << std::endl;
            break;
/*         case CHUNK_ID_PACK:
            uint32_t discard;
            file.read(reinterpret_cast<char*>(&discard), sizeof(discard));
            

            std::cerr << "cannot handle vox files with several models \n"; 
            break; */

        case CHUNK_ID_SIZE:
            // std::cout << "SIZE chunk \n";

            // std::cout << "num bytes of chunk content: " << static_cast<int>(numBytesChunkContent) << std::endl;
            // std::cout << "num bytes of children chunk content: " << static_cast<int>(numBytesChildrenChunkContent) << std::endl;



            uint32_t sizeX;
            uint32_t sizeY;
            uint32_t sizeZ;

            file.read(reinterpret_cast<char*>(&sizeX), sizeof(sizeX));
            file.read(reinterpret_cast<char*>(&sizeY), sizeof(sizeY));
            file.read(reinterpret_cast<char*>(&sizeZ), sizeof(sizeZ));

            voxelData.resize(sizeX, sizeY, sizeZ);

            break;
        
        case CHUNK_ID_XYZI:
            //std::cout << "XYZI chunk \n";

            //std::cout << "num bytes of chunk content: " << static_cast<int>(numBytesChunkContent) << std::endl;
            //std::cout << "num bytes of children chunk content: " << static_cast<int>(numBytesChildrenChunkContent) << std::endl;

            uint32_t numVoxels;
            file.read(reinterpret_cast<char*>(&numVoxels), sizeof(numVoxels));

            for (uint32_t i = 0; i < numVoxels; ++i) {
                char x;
                char y;
                char z;
                char colorIndex;

                file.read(&x, sizeof(x));
                file.read(&y, sizeof(y));
                file.read(&z, sizeof(z));
                file.read(&colorIndex, sizeof(colorIndex));

                voxelData[x][y][z] = colorIndex;
                voxelCount++;
            } 

            break;
        
        default:
            //discard content of non-relevant chunks
            char discard; 

            for (uint32_t i = 0; i < numBytesChunkContent; ++i) {
                file.read(&discard, sizeof(discard));
            }
            if (numBytesChildrenChunkContent != 0) {
                std::cerr << "there are some unexpected children... \n";
            }
            break;
        }

    }

    if (file.eof()) {
        //std::cout << "End of file reached." << std::endl;
    } else if (file.fail()) {
        throw std::runtime_error("Error: Failed to read data from file.");
    }

    file.close(); // Close the file


    return voxelData;
}

/* void writeChar(std::ofstream file, char) {

} */






void writeInt(std::ofstream& file, uint32_t value) {
    file.write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void writeWord(std::ofstream& file, const std::string& word) {
    if (word.size() != 4) {
        std::cerr << "Error: Word must have exactly 4 characters" << std::endl;
        return;
    }

    file.write(word.c_str(), 4);
}

void writeChar(std::ofstream& file, const char c) {
    file.write(&c, 1);
}


//counts solid voxels
int countVoxels(const Vector3D<uint8_t>& voxelData) {
    int count = 0;


    for (uint8_t i = 0; i < voxelData.dimX(); i++) {
        for (uint8_t j = 0; j < voxelData.dimY(); j++) {
            for (uint8_t k = 0; k < voxelData.dimZ(); k++) {
                if (voxelData[i][j][k] != 0) {
                    count++;
                }
            }
        }
    }
    return count;    
}


uint32_t calculateMAINchunkSize(const Vector3D<uint8_t>& voxelData) {
    uint32_t size = 0;

    //size of SIZE chunk header (in number of bytes)
    size += 12;  
    //size of SIZE chunk content
    size += 12;

    //size of XYZI chunk header
    size += 12;
    //size of XYZI chunk content
    size += 4 + 4*static_cast<uint32_t>(countVoxels(voxelData));
    
    return size;
}

const char* createBuffer(char a, char b, char c, char d) {
    static char buffer[4] = {a, b, c, d};
    return buffer;
}




void writeVoxFile(const Vector3D<uint8_t>& voxelData, const char* filePath) {
    std::ofstream file;

    if (filePath) {
        file.open(filePath, std::ios::binary);
    } else {
        file.open("vox_tiles/output.vox", std::ios::binary | std::ios::trunc);
    }

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file." << std::endl;
        return ;
    }



    //--------------- vox file header ---------------
    writeWord(file, "VOX ");    //header ID
    writeInt(file, 200);        //file version



    //--------------- MAIN chunk ---------------
    //header
    writeWord(file, "MAIN");                        //chunk ID
    writeInt(file, 0);                              //num bytes of chunk content
    writeInt(file, calculateMAINchunkSize(voxelData));  //num bytes of children chunk content

    
    //--------------- SIZE chunk ---------------
    //header
    writeWord(file, "SIZE");  //chunk ID
    writeInt(file, 12);       //num bytes of chunk content
    writeInt(file, 0);        //num bytes of children chunk content

    //content
    writeInt(file, voxelData.dimX());    //size X
    writeInt(file, voxelData.dimY());    //size Y
    writeInt(file, voxelData.dimZ());    //Size Z



    //--------------- XYZI chunk ---------------
    //header
    writeWord(file, "XYZI");
    writeInt(file, 4 + 4*static_cast<uint32_t>(countVoxels(voxelData)));
    writeInt(file, 0);
    
    //content
    writeInt(file, static_cast<uint32_t>(countVoxels(voxelData)));

    for (uint8_t i = 0; i < voxelData.dimX(); ++i) {
        for (uint8_t j = 0; j < voxelData.dimY(); ++j) {
            for (uint8_t k = 0; k < voxelData.dimZ(); ++k) {
                //count++;
                uint8_t value = voxelData[i][j][k];
                if (value != 0) {
                    writeChar(file, i);
                    writeChar(file, j);
                    writeChar(file, k);
                    writeChar(file, value);
                }
            }
        }
    } 


    file.close();


}

void openInMagicaVoxel(const std::string& filePath, const std::string& magicaPath) {
    std::string command = "powershell.exe -Command \"& '" + magicaPath + "' '" + filePath + "'\"";
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "Failed to open MagicaVoxel: " << result << std::endl;
    }
}

 


