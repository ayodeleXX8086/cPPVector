cmake_minimum_required(VERSION 4.0)
project(vectors)

set(CMAKE_CXX_STANDARD 20)
file(GLOB CORE_SOURCES
        "core_implementation/*"
)
add_executable(vectors main.cpp
        IntVectors.h
        IntVectors.cpp
        core_implementation/Vectors.cpp
        core_implementation/Vectors.h
        core_implementation/utils.h
        core_implementation/Vectors.tpp
        core_implementation/RawStorage.h
        core_implementation/RawStorage.tpp
)

add_executable(vectors_tests
        unittests/intvectors_tests.cpp
        IntVectors.h
        IntVectors.cpp)

add_executable(vector_core_tests
                unittests/vectors_tests.cpp
                ${CORE_SOURCES}
        core_implementation/RawStorage.tpp)

enable_testing()
add_test(NAME intvectors_tests COMMAND vectors_tests)
add_test(NAME vectors_tests COMMAND vector_core_tests)