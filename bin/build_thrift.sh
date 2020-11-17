cd thrift
thrift -r -gen cpp   -out ../thrift_model model_predict.thrift
echo end thrift build
