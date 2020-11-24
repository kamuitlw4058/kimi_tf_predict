namespace java com.xiaoniuhy.adp.thrift
namespace py api.thrift

include 'nx_adp.thrift'


service ModelPredictService{
   # 线上接口
   binary predictPb( 1:string model_key, 2: binary request_msg );
   # 测试接口
   double predict( 1: map<string,string> row );
   list<double> predictList( 1: list<map<string,string>> rows );
   map<string,string> get_model_versions();
   void update_model(1:string model_key,2: string model_dir_path);

}
