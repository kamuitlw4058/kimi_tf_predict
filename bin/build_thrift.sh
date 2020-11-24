cd src/main/thrift
thrift -r -gen cpp   -out ../cpp/thrift model_predict.thrift
thrift -r -gen py   -out ../python model_predict.thrift
echo end thrift build
