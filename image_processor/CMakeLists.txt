add_executable(
    image_processor
    image_processor.cpp
        parser.cpp
        filters/base.cpp
        filters/crop.cpp
        bmp.cpp
        processor.cpp
        producers.cpp
        image.cpp
        filters/sharpening.cpp
        filters/edge_detection.cpp
        filters/gray_scale.cpp
        filters/negative.cpp
        filters/gaussian_blur.cpp
        filters/crystallize.cpp
        exceptions.cpp
)