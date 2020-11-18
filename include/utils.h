#include <iostream>
#include <fstream>  
#include <sstream>  
#include <string>
#include <map>
#include <vector>
#include <json/json.h>
#include <xn_errno.h>
#include <tensorflow/core/platform/env.h>
#include <tensorflow/core/public/session.h>

using namespace std;
using namespace tensorflow;
#ifndef XNAD_ML_UTILS
#define XNAD_ML_UTILS

string get_file(string &filepath);

Json::Value get_json(string &filepath);

int show_tensor_value(Tensor *tensor,int len);

string map2string(map<string,string>& m);
#endif