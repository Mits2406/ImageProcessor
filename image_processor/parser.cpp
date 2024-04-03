#include "parser.h"
#include "exceptions.h"

#include <cstring>

ParserResults Parse(int argc, char **argv) {
    std::string path_file_in = argv[1];
    if (argc == 2) {
        throw ParserGotNotEnoughArgs();
    }
    std::string path_file_out = argv[2];
    std::vector<FilterDescription> filter_descriptions;
    for (int index = 3; index < argc; ++index) {
        if (strcmp(argv[index], "-gs") == 0) {
            filter_descriptions.push_back({"gs", {}});
        } else if (strcmp(argv[index], "-crop") == 0) {
            if (argc < index + 2) {
                throw ParserGotNotEnoughArgs();
            }
            filter_descriptions.push_back({"crop", {argv[++index], argv[++index]}});
        } else if (strcmp(argv[index], "-sharp") == 0) {
            filter_descriptions.push_back({"sharp", {}});
        } else if (strcmp(argv[index], "-edge") == 0) {
            if (argc < index + 1) {
                throw ParserGotNotEnoughArgs();
            }
            filter_descriptions.push_back({"edge", {argv[++index]}});
        } else if (strcmp(argv[index], "-blur") == 0) {
            if (argc < index + 1) {
                throw ParserGotNotEnoughArgs();
            }
            filter_descriptions.push_back({"blur", {argv[++index]}});
        } else if (strcmp(argv[index], "-crystallize") == 0) {
            if (argc < index + 1) {
                throw ParserGotNotEnoughArgs();
            }
            filter_descriptions.push_back({"cryst", {argv[++index]}});

        } else if (strcmp(argv[index], "-neg") == 0) {
            filter_descriptions.push_back({"neg", {}});
        } else {
            throw ParserExceptions();
        }
    }
    return {path_file_in, path_file_out, filter_descriptions};
}