#include<feature_configure.h>
#include<utils.h>

string ValueIndexer::to_string(){
    string ret;
    ret.append("<name:" + string(typeid(this).name()) + ">\n");
    return ret;

}

int ValueIndexer::opt(const string & col_value,float * output){
    cout<<"ValueIndexer\n";
    return 0;
}



int ScalarIndexer::opt(const string & col_value,float * output){
    float v = atof(col_value.c_str());
    v = (v - (this->mean)) / this->std;
    *(output + this->index) = v;
    return 0;
}

int OneHotIndexer::opt(const string & col_value,float * output){
    unordered_map<string,int>::const_iterator got = this->index_mapper.find(col_value);
    if (got !=  this->index_mapper.end()){
        // cout<< "onehot index:" + std::to_string(got->second) << endl;
        *(output + got->second) = 1.0;
    }
    return 0;
}


int ColumnIndexer::opt(const string & col_value,float * output){
    for(auto indexer : this->value_indexer){
        indexer->opt(col_value,output);
    }
    return 0;
}




string ColumnIndexer::to_string(){
    string ret;
    ret.append("<ColumnIndexer name:" + this->input_col + " ");
    ret.append("len:" + std::to_string((long )(this->value_indexer.size())) + ">");
    return ret;

}

Tensor* FeatureConfigure:: get_tensor(map<string,string> row_value){
    Tensor* input = new Tensor (DT_FLOAT, TensorShape({1,  this->dim}));
    float *pointor = input->flat<float>().data();
    for(int i =0;i <  this->dim;i++){
            *(pointor + (i * this->dim)) = 0.0;
    }
    for (auto indexer : this->indexers)
    {
        
        auto value =  row_value.find(indexer.input_col);
        if(value != row_value.end()){
            indexer.opt(value->second,pointor);
        }
    }
    return input;
}

Tensor* FeatureConfigure:: get_tensor( const vector<map<string, string> > & rows){
    int rows_size = rows.size();
    // cout << "rows_size:" + std:: to_string(rows_size) << endl;
    Tensor* input = new Tensor (DT_FLOAT, TensorShape({rows_size,  this->dim}));
    float *pointor = input->flat<float>().data();
    for(int i =0;i < rows_size;i++){
        for(int j= 0;j < this->dim;j ++){
            *(pointor + (i * this->dim + j)) = 0.0;
        }
    }
    for( int i =0; i < rows_size;i ++){
        // cout << "row:" + std::to_string(i) << endl;
        for (auto indexer : this->indexers)
        {
            auto value =  rows[i].find(indexer.input_col);
            if(value != rows[i].end()){
                // cout << "col:" + indexer.input_col + " value:" +  value->second << endl;
                indexer.opt(value->second,pointor+ (this->dim * i));
            }
            //cout << indexer.to_string() << endl;
        }
    }


    return input;

}


FeatureConfigure* FeatureConfigure::feature_config = FeatureConfigure::get_feature_config();

FeatureConfigure* FeatureConfigure::get_feature_config(){
    string config_path("data/features.json");
    FeatureConfigure* feature_configure = new FeatureConfigure();
    feature_configure->load(config_path);
    FeatureConfigure::feature_config = feature_configure;

    return FeatureConfigure::feature_config;
}


int FeatureConfigure::load(string &filepath){
    cout<<"start to load feature configure..."<<endl;
    Json::Value value =   get_json(filepath);
    this->dim = value["dim"].asInt();
    int indexer_size = value["indexer"].size();
    Json::Value cols =  value["indexer"];
    Json::Value::Members cols_keys  =  cols.getMemberNames();
    vector<ColumnIndexer> column_indexer_list;
    for (Json::Value::Members::iterator iter = cols_keys.begin(); iter != cols_keys.end(); iter++){
        string col_name = (*iter);
        ColumnIndexer col_indexer;
        col_indexer.input_col = col_name;
        vector<ValueIndexer*> value_indexer_list;
        Json::Value col_opts = cols[col_name];
         int col_opts_size = col_opts.size();
         for(int i = 0;i <col_opts_size ; i ++ ){
            Json::Value col_opt =  col_opts[i];
            string opt_type =  col_opt["opt"].asString();

            if(opt_type.compare("scaler") == 0){
                ScalarIndexer* indexer = new ScalarIndexer();
                indexer->index = col_opt["index"].asInt();
                indexer->mean = col_opt["mean"].asDouble();
                indexer->std = col_opt["std"].asDouble();
                value_indexer_list.push_back (indexer);
            }else if(opt_type.compare("one-hot") == 0){
                OneHotIndexer* indexer = new OneHotIndexer();
                unordered_map<string,int> index_mapper;
                Json::Value value_index = col_opt["index"];
                Json::Value::Members value_index_keys = value_index.getMemberNames();
                for (Json::Value::Members::iterator values_iter = value_index_keys.begin(); values_iter != value_index_keys.end(); values_iter++){
                    string value_index_key = (*values_iter);
                    index_mapper.insert(pair<string, int>(value_index_key, value_index[value_index_key].asInt()));
                }
                indexer->index_mapper = index_mapper;
                value_indexer_list.push_back(indexer);
            }
            else if (opt_type.compare("muti-one-hot") == 0){

            }
         }
         col_indexer.value_indexer = value_indexer_list;

         column_indexer_list.push_back(col_indexer);

    }
    this->indexers = column_indexer_list;
    return 0;

}