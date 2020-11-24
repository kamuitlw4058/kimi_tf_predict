cd src/main/proto
ls ../cpp
protoc --cpp_out=../cpp/pb ml.proto
protoc --python_out=../python/pb ml.proto
echo end protoc
