#include "crystallize.h"
#include <math.h>

const int INF = 1e9;

Crystallize::Crystallize(int cryst_amount) {
    cryst_amount_ = cryst_amount;
}

void Crystallize::Apply(Image &image) const {
    std::vector<std::pair<int, int>> cryst_centers;
    int hor_side = image.GetWidth() / cryst_amount_;
    int vert_side = image.GetHeight() / cryst_amount_;
    for (int i = 0; i < cryst_amount_; ++i) {
        for (int j = 0; j < cryst_amount_; ++j) {
            cryst_centers.push_back({hor_side * j + std::rand() % hor_side, vert_side * i + std::rand() % vert_side});
        }
    }
    for (int i = 0; i < image.GetHeight(); ++i) {
        for (int j = 0; j < image.GetWidth(); ++j) {
            int min_dist = INF;
            std::pair<int, int> closest_center = {0, 0};
            for (auto &p : cryst_centers) {
                if ((j - p.first) * (j - p.first) + (i - p.second) * (i - p.second) < min_dist) {
                    min_dist = (j - p.first) * (j - p.first) + (i - p.second) * (i - p.second);
                    closest_center = p;
                }
            }
            image.SetPixel(i, j, image.GetPixel(closest_center.second, closest_center.first));
        }
    }
}