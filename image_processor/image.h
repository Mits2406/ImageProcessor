#pragma once

#include <vector>
#include <array>
#include <algorithm>

struct RGB {
    double red;
    double green;
    double blue;
};

class Image {

public:
    Image(const int &height, const int &width, const std::vector<std::vector<RGB>> &image);

    Image(const int &height, const int &width);

    void SetPixel(const size_t &y_pos, const size_t &x_pos, const RGB &pix);

    RGB GetPixel(const size_t &y_pos, const size_t &x_pos) const;

    int GetWidth() const;

    int GetHeight() const;

    void ResizeWidth(const int &new_width);

    void ResizeHeight(const int &new_height);

    RGB NewPixel(const std::array<std::array<double, 3>, 3> &matrix, const int x_pos, const int y_pos) const;

    RGB NewPixel(const std::vector<std::vector<double>> &matrix, const int x_pos, const int y_pos) const;

    RGB NewPixel(const std::array<std::array<double, 2>, 3> &linear_function, const int x_pos, const int y_pos) const;

    void ApplyMatrix(const std::array<std::array<double, 3>, 3> &matrix);

    void ApplyMatrix(const std::vector<std::vector<double>> &matrix);

    void ApplyLinearFunction(const std::array<std::array<double, 2>, 3> &linear_function);

private:
    std::vector<std::vector<RGB>> image_;

    int width_;
    int height_;
};