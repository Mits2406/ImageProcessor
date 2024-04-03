#pragma once

#include "base.h"

class Crystallize : public BaseFilter {
public:
    explicit Crystallize(int cryst_amount);

    void Apply(Image &image) const override;

private:
    int cryst_amount_;
};