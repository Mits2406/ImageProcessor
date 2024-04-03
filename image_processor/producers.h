#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "filters/base.h"
#include "filters/crop.h"
#include "filters/sharpening.h"
#include "filters/gray_scale.h"
#include "filters/crystallize.h"
#include "filters/negative.h"
#include "filters/gaussian_blur.h"
#include "filters/edge_detection.h"
#include "parser.h"

std::unique_ptr<BaseFilter> CreateCropFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateEdgeFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateGrayScaleFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateBlurFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateNegativeFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateCrystallFilter(const std::vector<std::string> &filter_arguments);

std::unique_ptr<BaseFilter> CreateSharpeningFilter(const std::vector<std::string> &filter_arguments);