#include<predict_model.h>

PredictModel::PredictModel(){
    this->feature_config = make_shared<FeatureConfigure>();
    this->tfmodel =  make_shared<TFModel>();
}

int PredictModel::load(string &model_key, string & feature_config_path,string &tf_model_path){
    this->model_key = model_key;
    FeatureConfigure* feature_config = this->feature_config.get();
    feature_config->load(feature_config_path);

    TFModel* tfmodel = this->tfmodel.get();
    tfmodel->load(tf_model_path);
    return 0;
}

PredictModel::~PredictModel(){
}


void PredictModel::predictList( const vector<map<string,string>> &features,vector<double> &output){
    auto rows_len = features.size();
    FeatureConfigure* feature_configure =  this->feature_config.get();
    Tensor* v = feature_configure->get_tensor(features);
    TFModel* tfmodel =  this->tfmodel.get();
    tfmodel->predictList(v,rows_len,feature_configure->dim,output);
}