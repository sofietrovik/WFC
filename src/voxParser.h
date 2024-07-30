#pragma once

#include <iostream>
#include <fstream>
#include <bitset>
#include <cstdint>


#include "Vector3D.h"






Vector3D<uint8_t> readVoxFile(const char* filePath); 

void writeVoxFile(const Vector3D<uint8_t>& voxelData, const char* filePath);


void openInMagicaVoxel(const std::string& filePath, const std::string& magicaPath); 