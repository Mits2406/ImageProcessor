#include "bmp.h"
#include "image.h"
#include "exceptions.h"

#include <fstream>
#include <limits.h>
#include <cmath>

const int INT_SIZE = 4;
const int ZEROS_COUNT = 5;
const int FILE_HEADER_SIZE = 14;
const int BMP_PIXEL_SIZE = 24;
const int DIB_HEADER_SIZE = 40;
const int COLOR_SIZE = 255;

Image Read(std::string path) {
    std::ifstream input_stream(path, std::ifstream::binary);

    if (!input_stream.is_open()) {
        throw FileNotOpens();
    }

    input_stream.seekg(0, input_stream.end);
    auto length = static_cast<std::streamsize>(input_stream.tellg());
    input_stream.seekg(0, input_stream.beg);

    std::vector<uint8_t> bytes_vector(length);
    input_stream.read(reinterpret_cast<char *>(bytes_vector.data()), length);

    if ('B' != static_cast<char>(bytes_vector[0]) || 'M' != static_cast<char>(bytes_vector[1])) {
        throw FileIsWrongFormat();
    }

    auto read_four_bytes = [&bytes_vector](const size_t &pos) {
        int ans = 0;
        size_t to_shift = 0;
        for (size_t i = pos; i < pos + INT_SIZE; ++i) {
            ans += bytes_vector[i] << to_shift;
            to_shift += CHAR_BIT;
        }
        return ans;
    };
    int height = read_four_bytes(FILE_HEADER_SIZE + 2 * INT_SIZE);
    int width = read_four_bytes(FILE_HEADER_SIZE + INT_SIZE);

    Image image(height, width);

    int row_size = (width * BMP_PIXEL_SIZE + (INT_SIZE * CHAR_BIT) - 1) / (INT_SIZE * CHAR_BIT) * INT_SIZE;

    int cur_pos = FILE_HEADER_SIZE + DIB_HEADER_SIZE;

    for (int row = height - 1; row >= 0; --row) {
        for (int pos = cur_pos; pos < cur_pos + width * 3; pos += 3) {
            double blue = static_cast<double>(bytes_vector[pos]) / COLOR_SIZE;
            double green = static_cast<double>(bytes_vector[pos + 1]) / COLOR_SIZE;
            double red = static_cast<double>(bytes_vector[pos + 2]) / COLOR_SIZE;
            RGB new_pix({red, green, blue});
            int column = (pos - cur_pos) / 3;
            image.SetPixel(row, column, new_pix);
        }
        cur_pos += row_size;
    }
    return image;
}

void HeadWrite(const Image &image, std::string path) {
    std::ofstream output_stream;
    output_stream.open(path, std::ostream::binary);

    if (!output_stream.is_open()) {
        throw FileForOutputNotExists();
    }
    output_stream << "BM";

    int row_size = (BMP_PIXEL_SIZE * image.GetWidth() + (INT_SIZE * CHAR_BIT) - 1) / (INT_SIZE * CHAR_BIT) * INT_SIZE;

    int file_size = FILE_HEADER_SIZE + DIB_HEADER_SIZE + image.GetHeight() * row_size;

    output_stream.write(reinterpret_cast<char *>(&file_size), INT_SIZE);

    int zero = 0;
    int one = 1;
    output_stream.write(reinterpret_cast<char *>(&zero), INT_SIZE);

    int pixel_array_offset = FILE_HEADER_SIZE + DIB_HEADER_SIZE;

    output_stream.write(reinterpret_cast<char *>(&pixel_array_offset), INT_SIZE);
    int dib_header_size = DIB_HEADER_SIZE;
    int width = image.GetWidth();
    int height = image.GetHeight();
    int bmp_pixel_size = BMP_PIXEL_SIZE;

    output_stream.write(reinterpret_cast<char *>(&dib_header_size), INT_SIZE);
    output_stream.write(reinterpret_cast<char *>(&width), INT_SIZE);
    output_stream.write(reinterpret_cast<char *>(&height), INT_SIZE);
    output_stream.write(reinterpret_cast<char *>(&one), INT_SIZE / 2);
    output_stream.write(reinterpret_cast<char *>(&bmp_pixel_size), INT_SIZE / 2);
    output_stream.write(reinterpret_cast<char *>(&zero), INT_SIZE);
    for (int i = 0; i < ZEROS_COUNT; ++i) {
        output_stream.write(reinterpret_cast<char *>(&zero), INT_SIZE);
    }
    for (int i = image.GetHeight() - 1; i >= 0; --i) {
        std::vector<uint8_t> img_vector(row_size, 0);
        for (int j = 0; j < image.GetWidth(); ++j) {
            RGB pix = image.GetPixel(i, j);
            img_vector[3 * j] = static_cast<int>(std::floor(pix.blue * COLOR_SIZE));
            img_vector[3 * j + 1] = static_cast<int>(std::floor(pix.green * COLOR_SIZE));
            img_vector[3 * j + 2] = static_cast<int>(std::floor(pix.red * COLOR_SIZE));
        }
        auto tmp = reinterpret_cast<char *>(img_vector.data());
        output_stream.write(tmp, row_size);
    }
    output_stream.close();
}