#pragma once

#include "base.h"

class Crop : public BaseFilter {
public:
    Crop(int width, int height);

    void Apply(Image &image) const override;

private:
    int width_;
    int height_;
};
