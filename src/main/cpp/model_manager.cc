#include <model_manager.h>

unordered_map<string,shared_ptr<PredictModel>> ModelManager::models;

void ModelManager::init(){
    string model_name("default");
    string feature_path("data/default/features.json");
    string model_path("data/default/frozen_model.pb");
    update_model(model_name,feature_path,model_path);
}

void ModelManager::update_model(string &model_key, string &feature_path,string &model_path){
    shared_ptr <PredictModel> predictModel = make_shared<PredictModel>();
    predictModel->load(model_key, feature_path,model_path);
    models.insert(pair<string,shared_ptr <PredictModel>>(model_key,predictModel));
}


shared_ptr<PredictModel> ModelManager::get(const string &model_key){
     auto iterator = models.find(model_key);//find()返回一个指向2的迭代器
    if (iterator != models.end()){
        return iterator->second;
    }
    return nullptr;
	    
}