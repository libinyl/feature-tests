g++ testSocket.cc -o tsocket &&
./tsocket &
pid=$!
cd /proc/$pid/fdinfo
inode=`ls -l | awk 'END {print}' |awk '{print $NF}'`
echo "tsocket: pid = "$pid", inode number = "$inode
kill $pid
rm -rf tsocket