#include <iostream>
#include <fstream>  
#include <sstream>  
#include <string>
#include <map>
#include <vector>
#include <json/json.h>
#include <xn_errno.h>

using namespace std;

string get_file(string &filepath);

Json::Value get_json(string &filepath);