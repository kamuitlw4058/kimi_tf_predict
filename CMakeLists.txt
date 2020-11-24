cmake_minimum_required(VERSION 3.5)

project(my_project)

# Abseil requires C++11
set(CMAKE_CXX_STANDARD 14)

include_directories(/usr/local/include)
include_directories(/usr/local/inotify/include)

include_directories(/home/wls81/envs/tensorflow/tensorflow-1.15.4)
include_directories(~/envs/anaconda3/envs/py36/lib/python3.6/site-packages/tensorflow_core/include)
include_directories(~/envs/tensorflow/tensorflow-1.15.4/bazel-genfiles)
include_directories(~/envs/thrift-0.13.0/lib/cpp/src)

include_directories(src/main/cpp/jsoncpp)
include_directories(src/main/cpp/include)
include_directories(src/main/cpp/pb)
include_directories(src/main/cpp/thrift)


add_executable(hello_tf src/main/cpp/main.cpp 
                src/main/cpp/tf_model.cc
                src/main/cpp/feature_configure.cc
                src/main/cpp/utils.cc
                src/main/cpp/model_predict_service.cc
                src/main/cpp/pb/ml.pb.cc
                )
add_library( # Sets the name of the library.
        jsoncpp

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        #native-lib.cpp
        src/main/cpp/jsoncpp/json_reader.cpp
        src/main/cpp/jsoncpp/json_valueiterator.inl
        src/main/cpp/jsoncpp/json_value.cpp
        src/main/cpp/jsoncpp/json_writer.cpp
        )

add_library( # Sets the name of the library.
        thrift_model_predict

        # Sets the library as a shared library.
        STATIC

        # Provides a relative path to your source file(s).
        src/main/cpp/thrift/model_predict_constants.cpp
        src/main/cpp/thrift/model_predict_types.cpp
        src/main/cpp/thrift/ModelPredictService_server.skeleton.cpp
        src/main/cpp/thrift/ModelPredictService.cpp
        src/main/cpp/thrift/nx_adp_constants.cpp
        src/main/cpp/thrift/nx_adp_types.cpp
        )

link_directories(
    build
)

# Declare dependency on the absl::strings library
target_link_libraries(hello_tf
        ~/envs/tensorflow/tensorflow-1.15.4/bazel-bin/tensorflow/libtensorflow_cc.so
        ~/envs/tensorflow/tensorflow-1.15.4/bazel-bin/tensorflow/libtensorflow_framework.so
        /usr/local/lib/libthrift-0.13.0.so
        /usr/local/inotify/lib/libinotifytools.so
        jsoncpp
        thrift_model_predict
        )