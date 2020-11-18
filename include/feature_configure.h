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

using namespace std;
using namespace tensorflow;


class ValueIndexer{
    public:
         virtual  int opt(const string &col_value,float * output);
         string to_string();
        
};


class ScalarIndexer:   public  ValueIndexer {
    public:
        double mean;
        double std;
        int index;
        int opt(const string & col_value,float * output);
        string to_string();
};

class OneHotIndexer:   public  ValueIndexer {
    public:
        unordered_map<string,int> index_mapper;
        int opt(const string &col_value,float * output);
        string to_string();
};


class ColumnIndexer{
     public:
        string input_col;
        vector<ValueIndexer*> value_indexer;
        int opt(const string &value, float * output);
        string to_string();
};


class FeatureConfigure{
    public:
        int load(string & filepath);
       Json::Value config_json;
       int dim;
       vector<ColumnIndexer> indexers;
       Tensor* get_tensor( map<string,string> row_value);
       Tensor* get_tensor( const vector<map<string, string> > & rows);
       string to_string();
       static FeatureConfigure* get_feature_config();
       static FeatureConfigure* feature_config;
};
