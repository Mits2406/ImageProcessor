#include "edge_detection.h"
#include "gray_scale.h"
#include "../exceptions.h"

EdgeDetection::EdgeDetection(double tracehold) {
    if (tracehold > 1 || tracehold < 0) {
        throw WrongArguments();
    }
    tracehold_ = tracehold;
}

RGB EdgeDetection::ApplyPix(RGB pix) const {
    RGB new_pix{};
    if (pix.red > tracehold_) {
        new_pix = {1, 1, 1};
    } else {
        new_pix = {0, 0, 0};
    }
    return new_pix;
}

void EdgeDetection::Apply(Image &image) const {
    GS gray_scale{};
    gray_scale.Apply(image);
    std::array<std::array<double, 3>, 3> sharp_matrix = {{{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}};
    image.ApplyMatrix(sharp_matrix);
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            image.SetPixel(i, j, ApplyPix(image.GetPixel(i, j)));
        }
    }
}