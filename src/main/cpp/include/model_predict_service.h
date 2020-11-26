
#include "ModelPredictService.h"
#include <utils.h>
#include <feature_configure.h>
#include <tf_model.h>
#include <ml.pb.h>
#include <tracking.pb.h>
#include <memory.h>
#include <model_manager.h>

using namespace ::xn_adp::ml;
using namespace ::xn_adp::tracking;

#ifndef MODEL_PREDICT_SERVICE
#define MODEL_PREDICT_SERVICE

class ModelPredictServiceHandler : virtual public ModelPredictServiceIf
{
public:
  ModelPredictServiceHandler();
  void predictPb(std::string &_return, const std::string &model_key, const std::string &request_msg);

  void convertPb(PredictRequest &request, vector<map<string, string>> &ret);

  double predict(const std::map<std::string, std::string> &row);

  void predictList(std::vector<double> &_return, const std::vector<std::map<std::string, std::string>> &rows);

  void get_model_versions(std::map<std::string, std::string> &_return);

  void update_model(const std::string &model_key, const std::string &model_dir_path);
};

#endif