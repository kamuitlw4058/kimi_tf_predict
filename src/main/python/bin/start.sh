base_path=$(cd `dirname $0`; cd ..; pwd)
cd $base_path
nohup python package_monitor.py > logs/update_package.log &