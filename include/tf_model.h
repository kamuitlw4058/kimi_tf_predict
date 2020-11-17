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

class TFModel{
    public:
        int load(string & filepath);
        float predict(Tensor & input);

        static TFModel* tfmodel;
        static TFModel* get_tfmodel();

   private:
      Session *session;
      GraphDef graphdef;
    
};
