#include <fstream>
#include <iostream>

#include "bmp.h"
#include "parser.h"
#include "processor.h"
#include "exceptions.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        return 0;
    }
    try {
        auto parser_results = Parse(argc, argv);
        auto image = Read(parser_results.path_file_in);
        auto filters = CreateFilters(parser_results.filter_descriptions);
        ApplyFilters(filters, image);
        HeadWrite(image, parser_results.path_file_out);
    } catch (ParserExceptions) {
        std::cout << "Описание формата аргументов командной строки:\n"
                     "\n"
                     "{имя программы} {путь к входному файлу} {путь к выходному файлу} [-{имя фильтра 1}"
                     " [параметр фильтра 1] [параметр фильтра 2] ...] [-{имя фильтра 2} [параметр фильтра 1]"
                     " [параметр фильтра 2] ...] ...";
        std::cout << "Реализованные фильтры:" << std::endl;
        std::cout << "Crop (-crop)" << std::endl;
        std::cout << "Аргументы - width, height (не должны превышать соответствующие размеры изображения)\n"
                  << std::endl;
        std::cout << "Negitive (-neg)\n" << std::endl;
        std::cout << "Sharpness (-sharp)\n" << std::endl;
        std::cout << "Edge Detection (-edge)" << std::endl;
        std::cout << "Аргументы - threshold (0 <= threshold <= 1\n" << std::endl;
        std::cout << "Gaussian Blur (-blur)" << std::endl;
        std::cout << "Аргументы - radius (integer, radius > 0)\nНеиспользуйте большие радиусы и файлы - алгорит не "
                     "оптимизирован\n"
                  << std::endl;
        std::cout << "Crystallize (-cryst)" << std::endl;
        std::cout << "Аргументы - количество центров кристаллов на сторону" << std::endl;
    } catch (FileIsWrongFormat) {
        std::cout << "Используйте 24-битные BMP файлы";
    } catch (FileNotOpens) {
        std::cout << "Файл не открывается!";
    } catch (...) {
        std::cout << "Error! :(";
    }
}