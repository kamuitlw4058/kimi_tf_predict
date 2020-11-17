cmake_minimum_required(VERSION 3.5)

project(my_project)

# Abseil requires C++11
set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/include)
include_directories(jsoncpp)
include_directories(/home/wls81/envs/tensorflow/tensorflow-1.15.4)
include_directories(~/envs/anaconda3/envs/py36/lib/python3.6/site-packages/tensorflow_core/include)
include_directories(~/envs/tensorflow/tensorflow-1.15.4/bazel-genfiles)
include_directories(include)
#include_directories(abseil-cpp)


add_executable(hello_tf main.cpp 
                src/tf_model.cc
                src/feature_configure.cc
                src/utils.cc)
add_library( # Sets the name of the library.
        jsoncpp

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        #native-lib.cpp
        jsoncpp/json_reader.cpp
        jsoncpp/json_valueiterator.inl
        jsoncpp/json_value.cpp
        jsoncpp/json_writer.cpp
        )

link_directories(
    build
)

# Declare dependency on the absl::strings library
target_link_libraries(hello_tf
        ~/envs/tensorflow/tensorflow-1.15.4/bazel-bin/tensorflow/libtensorflow_cc.so
        ~/envs/tensorflow/tensorflow-1.15.4/bazel-bin/tensorflow/libtensorflow_framework.so
        jsoncpp
        )