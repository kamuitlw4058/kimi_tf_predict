namespace java com.xiaoniuhy.adp.thrift

include 'nx_adp.thrift'


service ModelPredictService{
   # 线上接口
   binary predictPb( 1: binary request_msg );
   # 测试接口
   double predict( 1: map<string,string> row );
   list<double> predictList( 1: list<map<string,string>> rows );

}
