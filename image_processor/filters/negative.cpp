#include "negative.h"
#include "../exceptions.h"

Negative::Negative() {
    linear_function_ = {{{1., -1}, {1., -1}, {1., -1}}};
}

void Negative::Apply(Image &image) const {
    image.ApplyLinearFunction(linear_function_);
}