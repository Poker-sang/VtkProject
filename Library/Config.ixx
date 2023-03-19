#include "pch.h"
export module Config;

export namespace Data2D {
auto ElevationData = std::make_shared<std::vector<std::vector<double>>>();
auto ScalarData = ElevationData;
int Width;
int Height;
std::string ElevationName = "ElevationData";
std::string ScalarName = "ScalarData";
}

export enum class CellType {
    Strip,
    Vertex,
    Line,
    Poly
};

export namespace Config {
int WindowWidth = 1280;
int WindowHeight = 720;
}

export namespace Config2D {
auto CellType = CellType::Line;
}
