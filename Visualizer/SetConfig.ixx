#include "pch.h"
export module SetConfig;

import Config;

export void SetWindowSize(const int width, const int height)
{
    Config::WindowWidth = width;
    Config::WindowHeight = height;
}
