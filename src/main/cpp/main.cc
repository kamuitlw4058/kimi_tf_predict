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

#include <thrift/concurrency/ThreadManager.h>
#include <thrift/concurrency/ThreadFactory.h>
#include <thrift/server/TThreadPoolServer.h>
#include <thrift/server/TThreadedServer.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;
using namespace ::apache::thrift::concurrency;
using namespace ::xn_adp::ml;


int main()
{
  ModelManager::init();
    // FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
    // cout<< feature_configure->dim << endl;
    // for(auto indexer : feature_configure->indexers){
    //     cout << indexer.to_string() << endl;
    // }

  int port = 10090;
  int cpu_number = 8; 
  ::std::shared_ptr<ModelPredictServiceHandler> handler(new ModelPredictServiceHandler());
  ::std::shared_ptr<TProcessor> processor(new ModelPredictServiceProcessor(handler));
  ::std::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::std::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::std::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  // TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  // server.serve();



  shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(cpu_number);
  shared_ptr<ThreadFactory> threadFactory  = shared_ptr<ThreadFactory>(new ThreadFactory());
  threadManager->threadFactory(threadFactory);
  threadManager->start();
  printf("start.../n");
 
  TThreadPoolServer server(processor,
                           serverTransport,
                           transportFactory,
                           protocolFactory,
                           threadManager);

  server.serve();

  return 0;
}
