#include "producers.h"
#include "exceptions.h"

std::unique_ptr<BaseFilter> CreateCropFilter(const std::vector<std::string> &filter_arguments) {
    if (filter_arguments.size() != 2) {
        throw ParserGotNotEnoughArgs();
    }
    std::size_t width = std::stoull(filter_arguments[0]);
    std::size_t height = std::stoull(filter_arguments[1]);
    return std::make_unique<Crop>(width, height);
}

std::unique_ptr<BaseFilter> CreateGrayScaleFilter(const std::vector<std::string> &filter_arguments) {
    return std::make_unique<GS>();
}

std::unique_ptr<BaseFilter> CreateNegativeFilter(const std::vector<std::string> &filter_arguments) {
    return std::make_unique<Negative>();
}

std::unique_ptr<BaseFilter> CreateBlurFilter(const std::vector<std::string> &filter_arguments) {
    if (filter_arguments.size() != 1) {
        throw ParserGotNotEnoughArgs();
    }
    size_t rd = std::stoull(filter_arguments[0]);
    return std::make_unique<GaussianBlur>(rd);
}

std::unique_ptr<BaseFilter> CreateCrystallFilter(const std::vector<std::string> &filter_arguments) {
    if (filter_arguments.size() != 1) {
        throw ParserGotNotEnoughArgs();
    }
    std::size_t cryst_amount = std::stoull(filter_arguments[0]);
    return std::make_unique<Crystallize>(cryst_amount);
}

std::unique_ptr<BaseFilter> CreateEdgeFilter(const std::vector<std::string> &filter_arguments) {
    if (filter_arguments.size() != 1) {
        throw ParserGotNotEnoughArgs();
    }
    std::size_t tracehold = std::stoull(filter_arguments[0]);
    return std::make_unique<EdgeDetection>(tracehold);
}

std::unique_ptr<BaseFilter> CreateSharpeningFilter(const std::vector<std::string> &filter_arguments) {
    return std::make_unique<Sharpening>();
}