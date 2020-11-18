cd protobuf
protoc --cpp_out=../src/protobuf_model/ ml.proto
protoc --python_out=../python/pb ml.proto
echo end protoc
