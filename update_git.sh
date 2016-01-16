if [ $# -ne 1 ];then
    echo "parameter error!"
    exit
fi
sudo git add --all
sudo git commit -m $1
sudo git push
