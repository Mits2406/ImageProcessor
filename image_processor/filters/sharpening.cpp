#include "sharpening.h"

std::array<std::array<double, 3>, 3> Sharpening::GetMatrix() const {
    const int five = 5;
    return {{{0, -1, 0}, {-1, five, -1}, {0, -1, 0}}};
}

void Sharpening::Apply(Image &image) const {
    image.ApplyMatrix(GetMatrix());
}
