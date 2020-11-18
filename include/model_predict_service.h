
#include "ModelPredictService.h"
#include <utils.h>
#include <feature_configure.h>
#include <tf_model.h>
#include <ml.pb.h>
#include <memory.h>

using namespace ::xnad::ml;

#ifndef MODEL_PREDICT_SERVICE
#define MODEL_PREDICT_SERVICE



class ModelPredictServiceHandler : virtual public ModelPredictServiceIf {
 public:
  ModelPredictServiceHandler() ;
  void predictPb(std::string& _return, const std::string& request_msg);

  void convertPb(PredictRequest & request,vector<map<string,string>>  &ret);

  double predict(const std::map<std::string, std::string> & row);

    void predictList(std::vector<double> & _return, const std::vector<std::map<std::string, std::string> > & rows);
};

#endif