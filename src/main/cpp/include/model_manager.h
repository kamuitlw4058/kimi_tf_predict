#include <iostream>
#include <fstream>  
#include <sstream>  
#include <string>
#include <map>
#include <vector>
#include <json/json.h>
#include <tensorflow/core/platform/env.h>
#include <tensorflow/core/public/session.h>
#include <xn_errno.h>
#include <unordered_map>
#include <memory>
#include<predict_model.h>

using namespace std;
using namespace tensorflow;

#ifndef MODEL_MANAGER
#define MODEL_MANAGER

class ModelManager{
    public:
        static unordered_map<string,shared_ptr<PredictModel>> models;
        static void init();
        static void update_model(string &model_key, string &feature_path,string &model_path);
        static shared_ptr<PredictModel> get(const string &model_key);

};

#endif 