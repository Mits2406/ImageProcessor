#pragma once

#include "base.h"

class EdgeDetection : public BaseFilter {
public:
    explicit EdgeDetection(double tracehold);

    void Apply(Image &image) const override;

private:
    RGB ApplyPix(RGB pix) const;

    double tracehold_;
};
