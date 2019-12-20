cmake_minimum_required(VERSION 3.14 FATAL_ERROR)


list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
# We need a standard package manager "https://github.com/ruslo/hunter"  to download alternatives "Eigen and Blast" to compare with our matrix arithmetics
include(HunterGate)
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.214.tar.gz"
    SHA1 "e14bc153a7f16d6a5eeec845fb0283c8fad8c358"
)
project(matrix_arithmetics VERSION 1.0.0)

