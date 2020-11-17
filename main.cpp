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






int main()
{
    string config_path("data/features.json");
    FeatureConfigure feature_configure;
    feature_configure.load(config_path);
    cout<< feature_configure.dim << endl;
    int indexer_len =  feature_configure.indexer.size();
    for(int i =0;i<indexer_len ;i ++){
        cout << feature_configure.indexer[i].to_string();
    }

    TFModel tfmodel;
    string model_path("model/frozen_model.pb");
    tfmodel.load(model_path);
    
    Tensor input(DT_FLOAT, TensorShape({1,  feature_configure.dim}));
    float *pointor = input.flat<float>().data();
    *pointor = 1.0;
    *(pointor + 1) = 1.0;
    *(pointor + 2) = 1.0;
    *(pointor + 3) = 0.0;
    *(pointor + 4) = 1.67;

    tfmodel.predict(input);
}
