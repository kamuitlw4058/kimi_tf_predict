namespace java com.xiaoniuhy.adp.thrift

include 'nx_adp.thrift'


service ModelPredictService{
   double predict( 1: map<string,string> row );

}
