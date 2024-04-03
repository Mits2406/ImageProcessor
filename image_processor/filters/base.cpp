#include "base.h"
#include <array>
#include "../exceptions.h"

BaseFilter::~BaseFilter() {
}

void BaseFilterWithMatrix::Apply(Image &image) const {
    image.ApplyMatrix(GetMatrix());
}

std::array<std::array<double, 3>, 3> BaseFilterWithMatrix::GetMatrix() const {
    return matrix_;
}