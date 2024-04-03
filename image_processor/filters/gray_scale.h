#pragma once

#include "base.h"

class GS : public BaseFilter {
public:
    GS();

    void Apply(Image &image) const override;

private:
    RGB ApplyPix(RGB pix) const;
};