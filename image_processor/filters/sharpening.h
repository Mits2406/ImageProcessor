#pragma once

#include "base.h"

class Sharpening : public BaseFilterWithMatrix {
public:
    std::array<std::array<double, 3>, 3> GetMatrix() const override;

    void Apply(Image &image) const override;
};
