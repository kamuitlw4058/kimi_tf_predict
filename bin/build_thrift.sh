cd thrift
thrift -r -gen cpp   -out ../thrift/thrift_model model_predict.thrift
thrift -r -gen py   -out ../python model_predict.thrift
echo end thrift build
