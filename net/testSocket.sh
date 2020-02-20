g++ testSocket.cc -o tsocket &&
./tsocket &
pid=$!
cd /proc/$pid/fdinfo
inode=`ls -l | awk 'END {print}' |awk '{print $NF}'`
echo "tsocket: pid = "$pid", inode number = "$inode
#kill $pid
#rm -rf tsocket

# https://oroboro.com/finding-state-tcpip-sockets-linux/
# http://diranieh.com/SOCKETS/SocketStates.htm

# ``type=TYPE ->INO=INODE PID,cmd,FDmode''
# https://www.howtogeek.com/426031/how-to-use-the-linux-lsof-command/
# https://gestantepremium.com.br/7ut98mwm/lsof-tcp-sockets.html
# https://serverfault.com/questions/153983/sockets-found-by-lsof-but-not-by-netstat
# https://stackoverflow.com/questions/27014955/socket-connect-vs-bind
# https://unix.stackexchange.com/a/116616
# https://en.wikipedia.org/wiki/Network_socket
# https://tools.ietf.org/html/rfc147
# https://docs.oracle.com/cd/E19455-01/806-1017/sockets-4/index.html

# protocol: TCP
# *:45843 (LISTEN)