#pragma once

#include "base.h"

class Negative : public BaseFilter {
public:
    Negative();

    void Apply(Image &image) const override;

private:
    std::array<std::array<double, 2>, 3> linear_function_;
};
