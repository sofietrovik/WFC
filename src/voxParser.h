#pragma once

#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdint>


#include "Vector3D.h"






bool isValidVoxFile(std::ifstream& stream);


Vector3D<uint8_t> readVoxFile(const char* filePath); 

void writeVoxFile(const Vector3D<uint8_t>& voxelData, const char* filePath);

void printBinary(const char* filePath, int numWords);

void openInMagicaVoxel(const std::string& filePath, const std::string& magicaPath); 