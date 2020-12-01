import os

from  pyinotify import WatchManager,Notifier
from  pyinotify import ALL_EVENTS
from  pyinotify import ProcessEvent

from python_common.utils.tar_utils import untar
from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from api.thrift  import ModelPredictService 

wm = WatchManager()
wm.add_watch("/home/wls81/workspace/kimi/tensorflow/data/package",ALL_EVENTS)

def submit(package_name,path):
    transport = TSocket.TSocket('127.0.0.1', 9090)
    transport = TTransport.TBufferedTransport(transport)
    protocol = TBinaryProtocol.TBinaryProtocol(transport)
    client = ModelPredictService.Client(protocol)
    # Connect!
    transport.open()

    client.update_model(package_name,path)
    transport.close()
    print(f'end submit {package_name}  ...')



def update_package(package_dir,package_file_name):
    if package_file_name.endswith(".tar.gz"):
        package_name = package_file_name[:-7]
        print(f"start update package:{package_name}")
        model_dir_base = "/home/wls81/workspace/kimi/tensorflow/data/model"
        model_dir = f'{model_dir_base}/{package_name}'
        if not os.path.exists(model_dir):
            os.makedirs(model_dir)
        package_path = f"{package_dir}/{package_file_name}"
        untar(package_path,model_dir)
        submit(package_name,model_dir)



class EventHandler(ProcessEvent):
    def process_IN_CREATE( self, event):
        print(f"Create file:{event.path} - {event.name}")
        update_package(event.path,event.name)
    
    def process_IN_DELETE( self, event):
        print(f"Delete file:{event.path} - {event.name}")

    def process_IN_MODIFY( self, event):
        print(f"Modify file:{event.path} - {event.name}")
        update_package(event.path,event.name)

    def process_IN_MOVED_TO( self, event):
        print(f"Move to file:{event.path} - {event.name}")
        update_package(event.path,event.name)

    def process_IN_MOVED_FROM( self, event):
        print(f"Move from file:{event.path} - {event.name}")


print("start loop...")
notifier = Notifier(wm, EventHandler())
notifier.loop()