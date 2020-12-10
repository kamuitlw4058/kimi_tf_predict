base_path=$(cd `dirname $0`; cd ..; pwd)
cd $base_path
bin/stop.sh
bin/start.sh