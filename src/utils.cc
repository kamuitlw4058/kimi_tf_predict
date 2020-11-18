#include<utils.h>

string get_file(string &filepath){
    std::ifstream t(filepath);  
    std::stringstream buffer;  
    buffer << t.rdbuf();  
    // cout << buffer.str();
    return buffer.str();
}


Json::Value get_json(string &filepath){
    string filestr = get_file(filepath);
    Json::Value root;
    Json::Reader reader;
    reader.parse(filestr, root);
    return root;
}

int show_tensor_value(Tensor *tensor,int len){
    float *t = tensor->flat<float>().data();
    for(int i =0;i <len;i++){
        cout << to_string(*(t + i)) << endl;
    }
    return 0;
}