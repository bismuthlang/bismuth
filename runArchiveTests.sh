# Require 1st arg (should really later check it is what we expected
if [ -z "$1" ]
  then
    echo "No argument supplied"
    exit -1
fi


unzip $1 -d ./tmp # Unzip the folder in a ./tmp

cd ./tmp # Change to inner directory

sudo docker run -it -v $PWD/ahfriedman-wpl:/home/shared ahfriedman/cs544-cs4533-docker

# User then does stuff

cd ..
rm -r ./tmp

