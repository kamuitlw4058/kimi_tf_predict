#include<tf_model.h>

int TFModel::load(string & filepath){
    Status status;

    status = NewSession(SessionOptions(), &this->session);
    if (!status.ok())
    {
        cout << status.ToString() << endl;
        return ERROR_COMMON;
    }
    cout << "Session Succ" << endl;

    status = ReadBinaryProto(Env::Default(),filepath, &this->graphdef);
    if (!status.ok())
    {
        cout << status.ToString() << endl;
        return ERROR_COMMON;
    }
    cout << "Read Graph Succ" << endl;

    status = session->Create(this->graphdef);
    if (!status.ok())
    {
        cout << status.ToString() << endl;
        return 1;
    }
    cout << "Session Create Succ" << endl;

    return 0;
}


 int TFModel::predict(Tensor & input){
    Status status;
    vector<pair<string, Tensor>> inputs = {{"input/x:0", input}};
    vector<Tensor> outputs;

    status = this->session->Run(inputs, {"lr/Sigmoid:0"}, {}, &outputs);
    if (!status.ok())
    {
        cout << status.ToString() << endl;
        return 1;
    }
    cout << "Session Run Succ" << endl;

    cout << outputs[0].flat<float>() << endl;

    return 0;
 }