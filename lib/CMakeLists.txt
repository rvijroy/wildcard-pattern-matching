cmake_minimum_required(VERSION 3.16.0)

project(pattern_matcher VERSION 0.1.0 LANGUAGES CXX)

# Make an automatic library - will be static or dynamic based on user setting
add_library(
    pattern_matcher
    STATIC
    src/matcher.cpp
)

# All users of this library will need at least C++20
target_compile_features(pattern_matcher PUBLIC cxx_std_20)

# We need this directory, and users of our library will need it too
target_include_directories(
    pattern_matcher
    PUBLIC
    include/
)