#include<tf_model.h>


int TFModel::load(string & filepath){
     cout<<"start to load tfmodel["<< filepath << "]..."<<endl;
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


 float TFModel::predict(Tensor * input){
    Status status;
    vector<pair<string, Tensor>> inputs = {{"input/x:0", *input}};
    vector<Tensor> outputs;

    status = this->session->Run(inputs, {"lr/Sigmoid:0"}, {}, &outputs);
    if (!status.ok())
    {
        // cout << status.ToString() << endl;
        return 1;
    }


    return *(outputs[0].flat<float>().data());
 }


 
 void TFModel::predictList(Tensor * input,int list_size, int dim,vector<double> & output){
     int output_size = output.size();
    Status status;
    vector<pair<string, Tensor>> inputs = {{"input/x:0", *input}};
    vector<Tensor> outputs;
    //  auto v = input->flat<float>();
    // for( int i =0;i < list_size;i ++)
    // {
    //     for(int j = 0;j < dim;j++)
    //     {
    //         cout << "Row:" + std::to_string(i) + "input data index:" + std::to_string(j) + " value:" + std::to_string(v(i * dim + j)) <<endl;
    //     }
        
    // }

    status = this->session->Run(inputs, {"lr/Sigmoid:0"}, {}, &outputs);
    if (!status.ok())
    {
         cout << "run tensorflow failed!" + status.ToString() << endl;
        return;
    }
    auto values= outputs[0].flat<float>();

    for(int i =0;i < list_size;i++){
         //cout << "return :" + std::to_string(values(i)) << endl;
        output.push_back(values(i));
    }


 }