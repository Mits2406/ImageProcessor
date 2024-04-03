#pragma once

#include <vector>
#include <array>

#include "../image.h"

class BaseFilter {
public:
    virtual ~BaseFilter();
    virtual void Apply(Image &image) const = 0;
};

class BaseFilterWithMatrix : public BaseFilter {
public:
    void Apply(Image &image) const override;

    virtual std::array<std::array<double, 3>, 3> GetMatrix() const;

private:
    std::array<std::array<double, 3>, 3> matrix_;
};
