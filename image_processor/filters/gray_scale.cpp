#include "gray_scale.h"

GS::GS(){};

RGB GS::ApplyPix(RGB pix) const {
    RGB new_pix{};
    const double red_coef = 0.299;
    const double green_coef = 0.587;
    const double blue_coef = 0.114;
    new_pix.red = new_pix.green = new_pix.blue = red_coef * pix.red + green_coef * pix.green + blue_coef * pix.blue;
    return new_pix;
}

void GS::Apply(Image &image) const {
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            image.SetPixel(i, j, ApplyPix(image.GetPixel(i, j)));
        }
    }
}
