#include <gtest/gtest.h>
#include <string>

bool verbose = false;
   

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    // Parse your custom verbose flag
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == "--verbose_mode") {
            verbose = true;
        }
    }

    return RUN_ALL_TESTS();
}