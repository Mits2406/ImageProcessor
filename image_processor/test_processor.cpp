#include <catch.hpp>
#include "processor.h"
#include "exceptions.h"

TEST_CASE("Test correct filters") {
    const std::vector<FilterDescription> filter_descriptions = {{"cryst", {"10"}}, {"crop", {"10", "10"}}};
    std::vector<std::unique_ptr<BaseFilter>> filters = CreateFilters(filter_descriptions);
    REQUIRE(filters.size() == 2);
}
