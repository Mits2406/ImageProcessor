#include "crop.h"
#include "../exceptions.h"

Crop::Crop(int width, int height) : width_(width), height_(height) {
    if (width_ < 0 || height_ < 0) {
        throw WrongArguments();
    }
}

void Crop::Apply(Image &image) const {
    if (width_ > image.GetHeight() || height_ > image.GetHeight()) {
        throw WrongArguments();
    }
    image.ResizeHeight(height_);
    image.ResizeWidth(width_);
}
