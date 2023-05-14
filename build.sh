set -e

exist_clear_nonexist_create() {
  if [ ! -d "$1" ];
  then
    mkdir $1
  else
    rm -rf $1/*
  fi
}

exist_clear_nonexist_create build
exist_clear_nonexist_create src/protocols
cd build
cmake ../src
exist_clear_nonexist_create() {
  if [ ! -d "$1" ];
  then
    mkdir $1
  else
    rm -rf $1/*
  fi
}
exist_clear_nonexist_create() {
  if [ ! -d "$1" ];
  then
    mkdir $1
  else
    rm -rf $1/*
  fi
}
make