#include "model_predict_service.h"

using namespace ::xnad::ml;

ModelPredictServiceHandler::ModelPredictServiceHandler() {
}

void ModelPredictServiceHandler::convertPb(PredictRequest & request,vector<map<string,string>>  &ret){

    auto ads_count = request.ads_size();
    auto os =  std::to_string( request.os());
    auto brand = request.brand();
    auto model = request.model();
    auto devtype = request.devtype();
    auto ppi = std::to_string(request.ppi());
    auto mccmnc = request.operator_();
    auto conn = std::to_string(request.conn());
    auto province = request.province();
    auto city = request.city();
    auto carrier = request.carrier();

    for(int i = 0;i < ads_count;i ++){
        map<string,string> row_dict;
        row_dict["Device_Os"] = os;
        row_dict["Device_Brand"] = brand;
        row_dict["Device_Model"] = model;
        row_dict["Device_Type"] = devtype;
        row_dict["Device_Ppi"] = ppi;

        row_dict["Network_MccMnc"] = mccmnc;
        row_dict["Network_Carrier"] = carrier;
        row_dict["Network_Connection"] = conn;

        row_dict["Geo_City"] = city;
        row_dict["Geo_Province"] = province;

        CandidateAd ad = request.ads(i);
        auto actiontype = std::to_string(ad.actiontype());
        auto imptype = std::to_string(ad.imptype());
        auto landingtype = std::to_string(ad.landingtype());
        auto category = ad.category();


        row_dict["Slot_Type"] = imptype;
        row_dict["Slot_ActionType"] = actiontype;
        row_dict["Slot_LandingType"] = landingtype;
        row_dict["Slot_Category"] = category;


        ret.push_back(row_dict);
    }

    return;
}

void ModelPredictServiceHandler:: predictPb(std::string& _return , const std::string& model_key,const std::string& request_msg) {
    PredictRequest predictRequest;
    if (!predictRequest.ParseFromString(request_msg)) {
        std::cout << "parse error\n";
    }

    vector<map<string,string>> feature_rows;
    this->convertPb(predictRequest,feature_rows);
    auto rows_len = feature_rows.size();
    auto model =   ModelManager::get(model_key);
    if (model != nullptr){
        vector<double> result;
        model->predictList(feature_rows,result);
        PredictResponse predictResponse;
        for(auto r :result){
            cout << "result:" +  std::to_string(r) << endl;
            auto result_ptr =  predictResponse.add_data();
            result_ptr->set_pctr(r * 1000000);
        }
        string result_msg("test");
        predictResponse.set_code(0);
        predictResponse.set_msg(result_msg);
        predictResponse.SerializeToString(&_return);
    }

    //predictRequest.get
    cout <<"predictPb" << endl;
    
}


double  ModelPredictServiceHandler::predict( const std::map<std::string, std::string> & row) {
// FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
// Tensor* v = feature_configure->get_tensor(row);
// TFModel* tfmodel = TFModel::tfmodel;
// return tfmodel->predict(v);
return 0.0;

}

void  ModelPredictServiceHandler::predictList(std::vector<double> & _return, const std::vector<std::map<std::string, std::string> > & rows) {
    // int rows_len = rows.size();
    // FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
    // Tensor* v = feature_configure->get_tensor(rows);
    // TFModel* tfmodel = TFModel::tfmodel;
    // tfmodel->predictList(v,rows_len,feature_configure->dim,_return);
}

