base_path=$(cd `dirname $0`; cd ..; pwd)
cd $base_path
nohup build/tf_predictor >> logs/tf_predictor.log 2>&1 &