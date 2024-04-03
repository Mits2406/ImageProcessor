#pragma once

#include "base.h"

#include <vector>

const double PI = 3.14159265358979323846;
const double E = 2.7182818284590452;

class GaussianBlur : public BaseFilter {
public:
    explicit GaussianBlur(int rd);

    std::vector<std::vector<double>> GaussianMatrix() const;

    void Apply(Image &image) const override;

private:
    int rd_;
    std::vector<std::vector<double>> matrix_;

    double GaussianFunc(int y_pos, int x_pos) const;
};