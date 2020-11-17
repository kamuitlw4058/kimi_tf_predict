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
        int predict(Tensor & input);
   private:
      Session *session;
      GraphDef graphdef;
    
};
