First type these lines

# openvpn --mktun --dev tun2
# ip link set tun2 up
# ip addr add 10.0.0.1/24 dev tun2

Then open another terminal and type this line 
# ping 10.0.0.2

Then run sudo ./IPoverTwitter

then run ./readbin

There is some bug in ./readbin I will try to fix it
