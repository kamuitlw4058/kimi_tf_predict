from model_predict  import ModelPredictService 

import sys
import json
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

from pb.ml_pb2 import PredictRequest # 从刚才编译出来的 py 文件中 import 解析的类
message = PredictRequest()
message.os = 1 # 赋值
ad = message.ads.add() 
ad.category = "test"

ad = message.ads.add() 
ad.category = "test1"

ad = message.ads.add() 
ad.category = "test2"

v = message.SerializeToString()

transport = TSocket.TSocket('127.0.0.1', 9090)
transport = TTransport.TBufferedTransport(transport)
protocol = TBinaryProtocol.TBinaryProtocol(transport)
client = ModelPredictService.Client(protocol)
# Connect!
transport.open()

msg = client.predictPb(v)
#msg = client.predictList([{"Device_Os":"ios"},{"Device_Os":"ios"},{"Device_Os":"android","Slot_Width":"1"}])
print(msg)
transport.close()