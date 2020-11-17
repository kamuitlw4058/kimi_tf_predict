#include<feature_configure.h>
#include <tensorflow/core/platform/env.h>
#include <tensorflow/core/public/session.h>
#include<utils.h>

string ValueIndexer::to_string(){
    string ret;
    ret.append("<name:" + string(typeid(this).name()) + ">\n");
    return ret;

}


int ValueIndexer::opt(string & col_value,Tensor & output){
    cout<<"ValueIndexer\n";
    return 0;
}



int ScalarIndexer::opt(string & col_value,Tensor & output){
    cout<<"ScalarIndexer\n";
    return 0;
}

int OneHotIndexer::opt(string & col_value,Tensor & output){
    cout<<"OneHotIndexer\n";
    return 0;
}



string ColumnIndexer::to_string(){
    string ret;
    ret.append("<name:" + string(typeid(this).name()) + " ");
    ret.append("len:" + std::to_string((long )(this->value_indexer.size())) + ">\n");
    int value_indexer_len = this->value_indexer.size();
    for(int i =0;i < value_indexer_len; i ++){
        cout << this->value_indexer[i]->to_string() << endl;
        ValueIndexer* indexer =  this->value_indexer[i];
        ret.append("\t" +indexer->to_string());
        string s("test");
         cout << s << endl;
        Tensor input(DT_FLOAT, TensorShape({1,  5}));
         cout << "end input" << endl;
        indexer->opt(s,input);
         cout << "end opt" << endl;
    }
    return ret;

}


int FeatureConfigure::load(string &filepath){
    Json::Value value =   get_json(filepath);
    this->dim = value["dim"].asInt();
    int indexer_size = value["indexer"].size();
    Json::Value cols =  value["indexer"];
    Json::Value::Members cols_keys  =  cols.getMemberNames();
    vector<ColumnIndexer> column_indexer_list;
    for (Json::Value::Members::iterator iter = cols_keys.begin(); iter != cols_keys.end(); iter++){
        string col_name = (*iter);
        cout<<col_name<<endl;
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
         }
         col_indexer.value_indexer = value_indexer_list;

         column_indexer_list.push_back(col_indexer);

    }
    this->indexer = column_indexer_list;
    return 0;

}