from model_predict  import ModelPredictService 

import sys
import json
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol


transport = TSocket.TSocket('127.0.0.1', 9090)
transport = TTransport.TBufferedTransport(transport)
protocol = TBinaryProtocol.TBinaryProtocol(transport)
client = ModelPredictService.Client(protocol)
# Connect!
transport.open()


msg = client.predictList([{"Device_Os":"ios"},{"Device_Os":"ios"},{"Device_Os":"android","Slot_Width":"1"}])
print(msg)
transport.close()