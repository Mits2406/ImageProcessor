#pragma once

#include <string>
#include <vector>

struct FilterDescription {
    std::string filter_name;
    std::vector<std::string> filter_arguments;
};

struct ParserResults {
    std::string path_file_in;
    std::string path_file_out;
    std::vector<FilterDescription> filter_descriptions;
};

ParserResults Parse(int argc, char **argv);
