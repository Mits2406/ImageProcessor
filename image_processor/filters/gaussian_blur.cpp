#include "gaussian_blur.h"
#include "math.h"

GaussianBlur::GaussianBlur(int rd) {
    rd_ = rd;
    matrix_ = GaussianMatrix();
}

std::vector<std::vector<double>> GaussianBlur::GaussianMatrix() const {
    std::vector<std::vector<double>> res_matrix;
    for (int i = -rd_; i < rd_ + 1; ++i) {
        res_matrix.push_back({});
        for (int j = -rd_; j < rd_ + 1; ++j) {
            res_matrix[res_matrix.size() - 1].push_back(GaussianFunc(i, j));
        }
    }
    return res_matrix;
}

double GaussianBlur::GaussianFunc(int y_pos, int x_pos) const {
    return 1 / (2 * PI * rd_ * rd_) * std::pow(E, -(y_pos * y_pos + x_pos * x_pos) / (2 * rd_ * rd_));
}

void GaussianBlur::Apply(Image &image) const {
    image.ApplyMatrix(matrix_);
}