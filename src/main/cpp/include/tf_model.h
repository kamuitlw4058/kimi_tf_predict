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

using namespace std;
using namespace tensorflow;

#ifndef TF_MODEL
#define TF_MODEL

class TFModel{
    public:
        int load(string & filepath);
        float predict(Tensor * input);
        void predictList(Tensor * input,int list_size, int dim,vector<double> & output);

   private:
      Session *session;
      GraphDef graphdef;
    
};

#endif