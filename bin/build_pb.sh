cd src/main/proto
protoc --cpp_out=../cpp/pb ml.proto
protoc --cpp_out=../cpp/pb tracking.proto

echo end protoc
