#include "model_predict_service.h"

using namespace ::xnad::ml;

ModelPredictServiceHandler::ModelPredictServiceHandler() {
}

void ModelPredictServiceHandler::convertPb(PredictRequest & request,vector<map<string,string>>  &ret){

    auto ads_count = request.ads_size();
    auto os =  std::to_string( request.os());
    for(int i = 0;i < ads_count;i ++){
        map<string,string> row_dict;
        row_dict["Device_Os"] = os;
        ret.push_back(row_dict);
    }

    return;
}


void ModelPredictServiceHandler:: predictPb(std::string& _return, const std::string& request_msg) {
    PredictRequest predictRequest;
    if (!predictRequest.ParseFromString(request_msg)) {
        std::cout << "parse error\n";
    }

    vector<map<string,string>> feature_rows;
    this->convertPb(predictRequest,feature_rows);
    auto rows_len = feature_rows.size();
    // for(auto row : feature_rows){
    //     cout << map2string(row) << endl;
    // }
    FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
    Tensor* v = feature_configure->get_tensor(feature_rows);
    TFModel* tfmodel = TFModel::tfmodel;
    vector<double> result;
    tfmodel->predictList(v,rows_len,feature_configure->dim,result);
    for(auto r :result){
        cout << "result:" +  std::to_string(r) << endl;
    }
    //predictRequest.get
    cout <<"predictPb" << endl;
}


double  ModelPredictServiceHandler::predict(const std::map<std::string, std::string> & row) {
FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
Tensor* v = feature_configure->get_tensor(row);
TFModel* tfmodel = TFModel::tfmodel;
return tfmodel->predict(v);

}

void  ModelPredictServiceHandler::predictList(std::vector<double> & _return, const std::vector<std::map<std::string, std::string> > & rows) {
    int rows_len = rows.size();
    FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
    Tensor* v = feature_configure->get_tensor(rows);
    TFModel* tfmodel = TFModel::tfmodel;
    tfmodel->predictList(v,rows_len,feature_configure->dim,_return);
}

