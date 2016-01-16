if [ $# -ne 1 ];then
    echo "*"
    echo "* Usage: $0  \"log\""
    echo "*"
    exit
fi
sudo git add --all
sudo git commit -m $1
sudo git push
sudo git reflog
