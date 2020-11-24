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
#include <feature_configure.h>
#include <tf_model.h>

using namespace std;
using namespace tensorflow;

#ifndef PREDICT_MODEL
#define PREDICT_MODEL


class PredictModel{
    public:
        PredictModel();
        ~PredictModel();
        string model_key;
        shared_ptr<FeatureConfigure> feature_config;
        shared_ptr<TFModel> tfmodel;
        int load(string & model_key, string & feature_config_path,string &tf_model_path);
        void predictList( const vector<map<string,string>> &features,vector<double> &output);

};

#endif 