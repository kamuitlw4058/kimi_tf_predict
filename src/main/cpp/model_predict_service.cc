#include "model_predict_service.h"

ModelPredictServiceHandler::ModelPredictServiceHandler()
{
}

void ModelPredictServiceHandler::convertPb(PredictRequest &request, vector<map<string, string>> &ret)
{
    auto ads_count = request.ads_size();
    
    // bidinfo
    auto bidRequest = request.bidreq();
   
    //network info
    auto mccmnc = bidRequest.operator_();
    auto conn = std::to_string(bidRequest.conn());
    auto carrier = bidRequest.carrier();

    //device info
    auto os = std::to_string(bidRequest.os());
    auto brand = bidRequest.brand();
    auto model = bidRequest.model();
    auto devtype = bidRequest.devtype();
    auto ppi = std::to_string(bidRequest.ppi());

    // location
    auto locationInfo =  bidRequest.location();
    auto province = locationInfo.province();
    auto city = locationInfo.city();
    auto district = locationInfo.district();
    auto street = locationInfo.street();
    auto poi_name = locationInfo.poi_name();

    //media info 
    auto app_id = bidRequest.app_id();
    auto imp_type = bidRequest.imp_type();

    for (int i = 0; i < ads_count; i++)
    {
        map<string, string> row_dict;
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
        row_dict["Geo_District"] = district;
        row_dict["Geo_Street"] = street;
        row_dict["Geo_PoiName"] = poi_name;

        row_dict["Media_Domain"] = app_id;
        row_dict["Slot_ImpType"] = imp_type;

        //ads info
        CandidateAd ad = request.ads(i);
        auto actiontype = std::to_string(ad.actiontype());
        auto landingtype = std::to_string(ad.landingtype());
        auto category = ad.category();

        row_dict["Slot_ActionType"] = actiontype;
        row_dict["Slot_LandingType"] = landingtype;
        row_dict["Slot_Category"] = category;

        ret.push_back(row_dict);
    }

    return;
}

void ModelPredictServiceHandler::predictPb(std::string &_return, const std::string &model_key, const std::string &request_msg)
{
    PredictRequest predictRequest;
    if (!predictRequest.ParseFromString(request_msg))
    {
        std::cout << "parse error\n";
    }

    vector<map<string, string>> feature_rows;
    this->convertPb(predictRequest, feature_rows);
    auto rows_len = feature_rows.size();
    auto model = ModelManager::get(model_key);
    if (model != nullptr)
    {
        vector<double> result;
        model->predictList(feature_rows, result);
        PredictResponse predictResponse;
        int count = result.size();
        for (int i = 0; i < count; i++)
        {
            auto result_ptr = predictResponse.add_data();
            result_ptr->set_pctr(result[i] * 1000000);
            result_ptr->set_pcvr(0);
            result_ptr->set_planid(predictRequest.ads(i).planid());
        }

        string result_msg("test");
        predictResponse.set_code(0);
        predictResponse.set_msg(result_msg);
        predictResponse.SerializeToString(&_return);
    }
}

double ModelPredictServiceHandler::predict(const std::map<std::string, std::string> &row)
{
    // FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
    // Tensor* v = feature_configure->get_tensor(row);
    // TFModel* tfmodel = TFModel::tfmodel;
    // return tfmodel->predict(v);
    return 0.0;
}

void ModelPredictServiceHandler::predictList(std::vector<double> &_return, const std::vector<std::map<std::string, std::string>> &rows)
{
    // int rows_len = rows.size();
    // FeatureConfigure* feature_configure = FeatureConfigure::feature_config;
    // Tensor* v = feature_configure->get_tensor(rows);
    // TFModel* tfmodel = TFModel::tfmodel;
    // tfmodel->predictList(v,rows_len,feature_configure->dim,_return);
}

void ModelPredictServiceHandler::get_model_versions(std::map<std::string, std::string> &_return)
{
    // Your implementation goes here
    printf("get_model_versions\n");
}

void ModelPredictServiceHandler::update_model(const std::string &model_key, const std::string &model_dir_path)
{
    // Your implementation goes here
    printf("update_model\n");
}