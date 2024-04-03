#pragma once

#include "image.h"

#include <string>

Image Read(std::string path);

void HeadWrite(const Image& image, std::string path);