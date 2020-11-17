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
         virtual  int opt(string &col_value,Tensor & output);
         string to_string();
        
};


class ScalarIndexer:   public  ValueIndexer {
    public:
        double mean;
        double std;
        int index;
        int opt(string & col_value,Tensor & output);
        string to_string();
};

class OneHotIndexer:   public  ValueIndexer {
    public:
        unordered_map<string,int> index_mapper;
        int opt(string &col_value,Tensor & output);
        string to_string();
};


class ColumnIndexer{
     public:
        string input_col;
        vector<ValueIndexer*> value_indexer;
        int opt(string &value, Tensor & output);
        string to_string();
};


class FeatureConfigure{
    public:
        int load(string & filepath);
       Json::Value config_json;
       int dim;
       vector<ColumnIndexer> indexer;
       string to_string();
};
