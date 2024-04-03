#include "image.h"
#include "exceptions.h"

Image::Image(const int &height, const int &width, const std::vector<std::vector<RGB>> &image) {
    Image(height, width);
    for (size_t i = 0; i < height_; ++i) {
        for (size_t j = 0; j < width_; ++j) {
            SetPixel(i, j, image[i][j]);
        }
    }
}

Image::Image(const int &height, const int &width) {
    height_ = height;
    width_ = width;
    image_.resize(height_);
    for (auto &i : image_) {
        i.resize(width_);
    }
}

void Image::SetPixel(const size_t &y_pos, const size_t &x_pos, const RGB &pix) {
    image_[y_pos][x_pos] = pix;
}

RGB Image::GetPixel(const size_t &y_pos, const size_t &x_pos) const {
    return image_[y_pos][x_pos];
}

int Image::GetHeight() const {
    return height_;
}

int Image::GetWidth() const {
    return width_;
}

void Image::ResizeHeight(const int &new_height) {
    image_.resize(new_height);
    height_ = new_height;
}

void Image::ResizeWidth(const int &new_width) {
    for (auto &i : image_) {
        i.resize(new_width);
    }
    width_ = new_width;
}

std::pair<int, int> ClosePixel(int y_pos, int x_pos, const int &width, const int &height) {
    y_pos = std::max(0, std::min(height - 1, y_pos));
    x_pos = std::max(0, std::min(width - 1, x_pos));
    return {y_pos, x_pos};
}

RGB Image::NewPixel(const std::array<std::array<double, 3>, 3> &matrix, const int x_pos, const int y_pos) const {
    RGB new_pix = {0, 0, 0};
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            int y = y_pos + i;
            int x = x_pos + j;
            y = ClosePixel(y, x, width_, height_).first;
            x = ClosePixel(y, x, width_, height_).second;
            new_pix.red += matrix[1 + i][1 + j] * GetPixel(y, x).red;
            new_pix.green += matrix[1 + i][1 + j] * GetPixel(y, x).green;
            new_pix.blue += matrix[1 + i][1 + j] * GetPixel(y, x).blue;
        }
    }
    new_pix.red = std::max(0., std::min(1., new_pix.red));
    new_pix.green = std::max(0., std::min(1., new_pix.green));
    new_pix.blue = std::max(0., std::min(1., new_pix.blue));
    return new_pix;
}

RGB Image::NewPixel(const std::vector<std::vector<double>> &matrix, const int x_pos, const int y_pos) const {
    int size = static_cast<int>(matrix.size());
    if (size <= 0 || matrix[0].size() != size || size % 2 != 1) {
        throw InvalidMatrix();
    }
    RGB new_pix = {0, 0, 0};
    for (int i = -(size / 2); i < size / 2 + 1; ++i) {
        for (int j = -(size / 2); j < size / 2 + 1; ++j) {
            int y = y_pos + i;
            int x = x_pos + j;
            auto y_x = ClosePixel(y, x, width_, height_);
            y = y_x.first;
            x = y_x.second;
            new_pix.red += matrix[(size / 2) + i][(size / 2) + j] * GetPixel(y, x).red;
            new_pix.green += matrix[(size / 2) + i][(size / 2) + j] * GetPixel(y, x).green;
            new_pix.blue += matrix[(size / 2) + i][(size / 2) + j] * GetPixel(y, x).blue;
        }
    }
    new_pix.red = std::max(0., std::min(1., new_pix.red));
    new_pix.green = std::max(0., std::min(1., new_pix.green));
    new_pix.blue = std::max(0., std::min(1., new_pix.blue));
    return new_pix;
}

RGB Image::NewPixel(const std::array<std::array<double, 2>, 3> &linear_function, const int x_pos,
                    const int y_pos) const {
    RGB new_pix = {0, 0, 0};
    new_pix.red = linear_function[0][0] + GetPixel(y_pos, x_pos).red * linear_function[0][1];
    new_pix.green = linear_function[1][0] + GetPixel(y_pos, x_pos).green * linear_function[1][1];
    new_pix.blue = linear_function[2][0] + GetPixel(y_pos, x_pos).blue * linear_function[2][1];
    new_pix.red = std::max(0., std::min(1., new_pix.red));
    new_pix.green = std::max(0., std::min(1., new_pix.green));
    new_pix.blue = std::max(0., std::min(1., new_pix.blue));
    return new_pix;
}

void Image::ApplyMatrix(const std::array<std::array<double, 3>, 3> &matrix) {
    std::vector<std::vector<RGB>> new_pixels(GetHeight(), std::vector<RGB>(GetWidth()));
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            new_pixels[i][j] = NewPixel(matrix, j, i);
        }
    }
    for (size_t i = 0; i < GetHeight(); ++i) {
        for (size_t j = 0; j < GetWidth(); ++j) {
            SetPixel(i, j, new_pixels[i][j]);
        }
    }
}

void Image::ApplyMatrix(const std::vector<std::vector<double>> &matrix) {
    std::vector<std::vector<RGB>> new_pixels(GetHeight(), std::vector<RGB>(GetWidth()));
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            new_pixels[i][j] = NewPixel(matrix, j, i);
        }
    }
    for (size_t i = 0; i < GetHeight(); ++i) {
        for (size_t j = 0; j < GetWidth(); ++j) {
            SetPixel(i, j, new_pixels[i][j]);
        }
    }
}

void Image::ApplyLinearFunction(const std::array<std::array<double, 2>, 3> &linear_function) {
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            SetPixel(i, j, NewPixel(linear_function, j, i));
        }
    }
}