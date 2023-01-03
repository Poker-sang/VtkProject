#include "pch.h"
export module SetData2D;

import Config;

C_EXPORT void SetCellType(int cellType)
{
    Config2D::CellType = static_cast<CellType>(cellType);
}

C_EXPORT void SetElevationData(double* elevation, const int width, const int height)
{
    Data2D::Width = width;
    Data2D::Height = height;
    // 行
    for (auto i = 0; i < height; ++i) {
        Data2D::ElevationData->emplace_back();
        (*Data2D::ElevationData)[i].reserve(width);
        // 列
        for (auto j = 0; j < width; ++j) {
            (*Data2D::ElevationData)[i].emplace_back(elevation[i * width + j]);
        }
    }
}

C_EXPORT void SetScalarData(double* elevation)
{
    // 行
    for (auto i = 0; i < Data2D::Height; ++i) {
        Data2D::ScalarData->emplace_back();
        (*Data2D::ScalarData)[i].reserve(Data2D::Width);
        // 列
        for (auto j = 0; j < Data2D::Width; ++j) {
            (*Data2D::ScalarData)[i].emplace_back(elevation[i * Data2D::Width + j]);
        }
    }
}

C_EXPORT void SetScalarDataFromElevation()
{
    Data2D::ScalarName = Data2D::ElevationName;
    Data2D::ScalarData = Data2D::ElevationData;
}

C_EXPORT void ReleaseData2D()
{
    Data2D::ElevationData = nullptr;
    Data2D::ScalarData = nullptr;
}
