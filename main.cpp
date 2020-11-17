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


#include "ModelPredictService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

class ModelPredictServiceHandler : virtual public ModelPredictServiceIf {
 public:
  ModelPredictServiceHandler() {
    // Your initialization goes here
  }

  double predict(const std::map<std::string, std::string> & row) {
    FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
   // row["Device_Os"] = "ios";
    Tensor v = feature_configure->get_tensor(row);
    show_tensor_value(v,feature_configure->dim);

    TFModel* tfmodel = TFModel::tfmodel;
    printf("predict\n");

    return tfmodel->predict(v);
    
  }

};



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
