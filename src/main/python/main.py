from api.thrift  import ModelPredictService 

import sys
import json
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol

from api.pb.ml_pb2 import PredictRequest 
from api.pb.ml_pb2 import PredictResponse 
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

msg = client.predictPb("default", v)
#msg = client.predictList([{"Device_Os":"ios"},{"Device_Os":"ios"},{"Device_Os":"android","Slot_Width":"1"}])
print(msg)
resonse = PredictResponse()
resonse.ParseFromString(msg)
print(resonse.code)
print(resonse.msg)
print(resonse.data)

transport.close()