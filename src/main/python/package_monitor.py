import os

from  pyinotify import WatchManager,Notifier
from  pyinotify import ALL_EVENTS
from  pyinotify import ProcessEvent

from python_common.utils.tar_utils import untar



wm = WatchManager()
wm.add_watch("/home/wls81/workspace/kimi/tensorflow/data/package",ALL_EVENTS)


def update_package(package_dir,package_file_name):
    if not package_file_name.endswith(".copy") and package_file_name.endswith(".tar.gz"):
        package_name = package_file_name[:-7]
        print(f"start update package:{package_name}")
        model_dir_base = "/home/wls81/workspace/kimi/tensorflow/data/model"
        model_dir = f'{model_dir_base}/{package_name}'
        if not os.path.exists(model_dir):
            os.makedirs(model_dir)
        package_path = f"{package_dir}/{package_file_name}"
        untar(package_path,model_dir)



class EventHandler(ProcessEvent):
    def process_IN_CREATE( self, event):
        print(f"Create file:{event.path} - {event.name}")
        update_package(event.path,event.name)
    
    def process_IN_DELETE( self, event):
        print(f"Delete file:{event.path} - {event.name}")

    def process_IN_MODIFY( self, event):
        print(f"Modify file:{event.path} - {event.name}")

    def process_IN_MOVED_TO( self, event):
        print(f"Move to file:{event.path} - {event.name}")
        update_package(event.path,event.name)

    def process_IN_MOVED_FROM( self, event):
        print(f"Move from file:{event.path} - {event.name}")


notifier = Notifier(wm, EventHandler())
notifier.loop()