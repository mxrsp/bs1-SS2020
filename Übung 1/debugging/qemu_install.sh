sudo apt-get clean
sudo echo "deb http://archive.ubuntu.com/ubuntu trusty main restricted" > /etc/apt/sources.list
sudo add-apt-repository universe
sudo apt-get update
sudo apt-get install qemu-system-x86
