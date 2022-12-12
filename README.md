## Table of contents
* [About](#about)
* [Technologies](#technologies)
* [Setup](#setup)

## About 
BookMarker is a sipmple CL application for UNIX systems to mark often used location in file system and cd into them with custom shortcut.
	
## Technologies
Project is created with:
* C/C++ version: Doesn't matter 
* bash 
	
## Setup
To run project clone it and follow instructions described in wiki.

```
$ git clone git@github.com:kosior3kt/localBookmark.git
$ cd localBookmark
$ mkdir build && cd build 
$ g++ -g -std=c++20 ../main.cpp -o betterCD
$ export PATH=$PATH:$(pwd)
```

IMPORTANT - program requires you to set your XDG_CONFIG_HOME variable (suggested location is ~/.config).
If You don't know what You are doing, first of all, You are about to have a great time :), second of all, just copy these:
```
$ mkdir ~/.config
$ touch ~/.bash_profile
$ echo "export XDG_CONFIG_HOME='~/.config' >> ~/.bash_profile"
$ echo 'function m {
   input=$(betterCD "$@")
   local t1=$?
   temp=$1
    if [ $1 ] && [ $t1 -eq 1 ]; then
          cd $(cat ~/.config/.tempVar)
    fi 
    if [ $1 ] && [[ $temp == "." ]]; then
       popd
       return
    fi
   echo "$input"'
```
