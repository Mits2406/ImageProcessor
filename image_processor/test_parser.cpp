#include <catch.hpp>
#include "parser.h"
#include "exceptions.h"

TEST_CASE("Parser errors") {
    const char* input_string1[] = {"name", "in.bmp", "out.bmp", "-crystallize"};
    const char* input_string2[] = {"name", "in.bmp", "out.bmp", "-crystallize", "2", "2", "2"};
    const char* input_string3[] = {"name", "in.bmp", "out.bmp", "-crystallize", "2", "-blr"};

    int input_amout1 = 4;  // NOLINT
    int input_amout2 = 7;  // NOLINT
    int input_amout3 = 6;  // NOLINT

    ParserResults my_res1 = Parse(input_amout1, const_cast<char**>(input_string1));  // NOLINT
    ParserResults my_res2 = Parse(input_amout2, const_cast<char**>(input_string2));  // NOLINT
    ParserResults my_res3 = Parse(input_amout3, const_cast<char**>(input_string3));  // NOLINT

    REQUIRE_THROWS_AS(my_res1, ParserGotNotEnoughArgs);
    REQUIRE_THROWS_AS(my_res2, ParserExceptions);
    REQUIRE_THROWS_AS(my_res3, ParserExceptions);
}

TEST_CASE("Valid Parser arguments") {
    const char* input_string1[] = {"name", "in.bmp", "out.bmp", "-crystallize", "10"};
    const char* input_string2[] = {"name", "in.bmp", "out.bmp", "-crystallize", "2", "-blur", "10"};

    int input_amout1 = 5;  // NOLINT
    int input_amout2 = 7;  // NOLINT

    ParserResults r_out1 = {"in.bmp", "out.bmp", {{"cryst", {"10"}}}};
    ParserResults r_out2 = {"in.bmp", "out.bmp", {{"cryst", {"2"}}, {"blur", {"10"}}}};

    ParserResults my_res1 = Parse(input_amout1, const_cast<char**>(input_string1));  // NOLINT
    ParserResults my_res2 = Parse(input_amout2, const_cast<char**>(input_string2));  // NOLINT

    REQUIRE(r_out1.path_file_in == my_res1.path_file_in);
    REQUIRE(r_out1.filter_descriptions[0].filter_name == my_res1.filter_descriptions[0].filter_name);
    REQUIRE(r_out2.filter_descriptions[1].filter_arguments[0] == my_res2.filter_descriptions[1].filter_arguments[0]);
}