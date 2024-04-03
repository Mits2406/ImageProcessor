#include "processor.h"
#include "exceptions.h"

#include <functional>

const std::unordered_map<std::string, std::function<std::unique_ptr<BaseFilter>(const std::vector<std::string>)>>
    FILTER_PRODUCERS = {{"crop", CreateCropFilter},   {"gs", CreateGrayScaleFilter}, {"sharp", CreateSharpeningFilter},
                        {"edge", CreateEdgeFilter},   {"blur", CreateBlurFilter},    {"cryst", CreateCrystallFilter},
                        {"neg", CreateNegativeFilter}};

std::unique_ptr<BaseFilter> CreateFilter(const FilterDescription &filter_description) {
    auto producer_it = FILTER_PRODUCERS.find(filter_description.filter_name);
    if (producer_it == FILTER_PRODUCERS.end()) {
        throw FileExceptions();
    }
    return producer_it->second(filter_description.filter_arguments);
}

std::vector<std::unique_ptr<BaseFilter>> CreateFilters(const std::vector<FilterDescription> &filter_description) {
    std::vector<std::unique_ptr<BaseFilter>> filters = {};
    for (auto &filter_desc : filter_description) {
        filters.push_back(CreateFilter(filter_desc));
    }
    return filters;
}

void ApplyFilters(const std::vector<std::unique_ptr<BaseFilter>> &filters, Image &image) {
    for (auto &filter : filters) {
        filter->Apply(image);
    }
}