#pragma once

#include <iostream>
#include <vector>

template <typename T>
class Vector3D {
public:

    Vector3D() = default;

    Vector3D(size_t dimX, size_t dimY, size_t dimZ) 
        : data(dimX, std::vector<std::vector<T>>(dimY, std::vector<T>(dimZ))) {}

    ~Vector3D() = default;

    size_t dimX() const {
        return data.size();
    }

    size_t dimY() const {
        return (data.size() > 0) ? data[0].size() : 0;
    }

    size_t dimZ() const {
        return (data.size() > 0 && data[0].size() > 0) ? data[0][0].size() : 0;
    }

    std::vector<std::vector<T>>& operator[](size_t i) {
        return data[i];
    }

    const std::vector<std::vector<T>>& operator[](size_t i) const {
        return data[i];
    }

    std::vector<std::vector<std::vector<T>>>& getData() {
        return data;
    }

    const std::vector<std::vector<std::vector<T>>>& getData() const {
        return data;
    }


    void print() const{
        std::cout << std::endl;

        for (size_t i = 0; i < dimZ(); ++i) {
            for (size_t j = 0; j < dimY(); ++j) {
                for (size_t k = 0; k < dimX(); ++k) {
                    if (data[k][j][i] != 0) {
                        std::cout << "X ";
                    } else {
                    std::cout << "- ";
                    }
                }
                std::cout << "\n";
            }
            std::cout << "\n\n";
        }
    }


    void resize(size_t dimX, size_t dimY, size_t dimZ) {
        data.resize(dimX);
        for (auto& plane : data) {
            plane.resize(dimY);
            for (auto& row : plane) {
                row.resize(dimZ);
            }
        }
    }

    //rotates the data numRotations x 90 degrees clockwise along the z-axis
    void rotateClockwise(int numRotations) {
        for (int r = 0; r < numRotations; ++r) {
            size_t x = dimX();
            size_t y = dimY();
            size_t z = dimZ();

            std::vector<std::vector<std::vector<T>>> newData(y, std::vector<std::vector<T>>(x, std::vector<T>(z)));

            //rotate 90 degrees clockwise along the z-axis
            for (size_t i = 0; i < x; ++i) {
                for (size_t j = 0; j < y; ++j) {
                    for (size_t k = 0; k < z; ++k) {
                        newData[j][x - 1 - i][k] = data[i][j][k];
                    }
                }
            }
            data = newData;
        }
    }

    std::vector<T> flatten() const {
        std::vector<T> flatVector;

        for (const auto& matrix : data) {
            for (const auto& row : matrix) {
                for (const auto& element : row) {
                    flatVector.push_back(element);
                }
            }
        }
        return flatVector;
    }


private:
    std::vector<std::vector<std::vector<T>>> data;
};