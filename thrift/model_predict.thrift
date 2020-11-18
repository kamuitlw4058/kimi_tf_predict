namespace java com.xiaoniuhy.adp.thrift

include 'nx_adp.thrift'


service ModelPredictService{
   double predict( 1: map<string,string> row );
   list<double> predictList( 1: list<map<string,string>> rows );

}
