#include <iostream>
#include <fstream>  
#include <sstream>  
#include <string>
#include <map>
#include <vector>
#include <json/json.h>

#include <utils.h>
#include <feature_configure.h>
#include <tf_model.h>

using namespace std;
using namespace tensorflow;

#include <ml.pb.h>

#include "model_predict_service.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::xnad::ml;



// class ModelPredictServiceHandler : virtual public ModelPredictServiceIf {
//  public:
//   ModelPredictServiceHandler() {
//   }
//   void predictPb(std::string& _return, const std::string& request_msg) {
//      PredictRequest predictRequest;
//         if (!predictRequest.ParseFromString(request_msg)) {
//         std::cout << "parse error\n";
//     }
//     predictRequest.get
//     printf("predictPb\n");
//   }


//   double predict(const std::map<std::string, std::string> & row) {
//     FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
//     Tensor* v = feature_configure->get_tensor(row);
//     TFModel* tfmodel = TFModel::tfmodel;
//     return tfmodel->predict(v);
    
//   }

//     void predictList(std::vector<double> & _return, const std::vector<std::map<std::string, std::string> > & rows) {
//       int rows_len = rows.size();
//         FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
//       Tensor* v = feature_configure->get_tensor(rows);
//        TFModel* tfmodel = TFModel::tfmodel;
//        tfmodel->predictList(v,rows_len,feature_configure->dim,_return);
    
//   }

// };



int main()
{
    FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
    cout<< feature_configure->dim << endl;
    for(auto indexer : feature_configure->indexers){
        cout << indexer.to_string() << endl;
    }

  int port = 9090;
  ::std::shared_ptr<ModelPredictServiceHandler> handler(new ModelPredictServiceHandler());
  ::std::shared_ptr<TProcessor> processor(new ModelPredictServiceProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
