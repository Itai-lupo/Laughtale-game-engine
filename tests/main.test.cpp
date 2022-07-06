#include <gtest/gtest.h>
#include "LaughTaleEngine.hpp"
#include <iostream>
#include <stdio.h>

int main(int argc, char **argv) {
    std::cout << argv[1] << std::endl; 
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
