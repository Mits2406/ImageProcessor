#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <functional>

#include "filters/base.h"
#include "image.h"
#include "producers.h"
#include "parser.h"

std::unique_ptr<BaseFilter> CreateFilter(const FilterDescription &filter_description);

std::vector<std::unique_ptr<BaseFilter>> CreateFilters(const std::vector<FilterDescription> &filter_description);

void ApplyFilters(const std::vector<std::unique_ptr<BaseFilter>> &filters, Image &image);
