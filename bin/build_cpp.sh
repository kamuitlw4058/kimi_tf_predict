base_path=$(cd `dirname $0`; cd ..; pwd)
cd $base_path/build
cmake ..
make
echo end make
