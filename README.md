## Table of contents
* [About](#about)
* [Technologies](#technologies)
* [Setup](#setup)
* [Usage](#usage)

## About 
BookMarker is a sipmple CL application for UNIX systems to mark often used location in file system and cd into them with custom shortcut.
	
## Technologies
Project is created with:
* C/C++ version: Doesn't matter (I think... On 17 works just fine)
* bash 
	
## Setup
To run project clone it and follow instructions described in wiki (when I finally make it... for now README should be eneouch anyways)

```
$ git clone git@github.com:kosior3kt/localBookmark.git
$ cd localBookmark
$ mkdir build && cd build 
$ g++ -g -std=c++20 ../main.cpp -o betterCD
$ export PATH=$PATH:$(pwd)
```
(if it physically pains You to add garbage directories to Your PATH, just create symlink to executable or move it to directory within existing PATH, or sth)
### IMPORTANT - program requires you to set your XDG_CONFIG_HOME variable (suggested location is ~/.config).
If You don't know what You are doing, first of all, You are about to have a great time :), second of all, just copy these:
```
$ mkdir ~/.config
$ touch ~/.bash_profile
$ echo "export XDG_CONFIG_HOME='~/.config'" >> ~/.bash_profile
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
   echo "$input"' >> ~/.bash_profile
$ source ~/.bash_profile
```
If You would rather call Your program something else than 'm' (m comes from vim marks) just rename function above

## Usage
To run program simply type 
```
$ m <name> - cd into the path corealated with <name>
```
At the beggining there are no flags (obvoiusly)
To add some use -a flag.
As of today program has 3 flags:
```
$ m -a <name> - creates a bookmark with given <name> in current directory 
$ m -r <name> - removes a bookmark with the given <name>
$ m -s - lists all the possibles bookmarks
```

Additionaly program allows you to jump to previous locations using following syntax:
```
$ m . - jumps to previous location
```

### showCase


https://user-images.githubusercontent.com/83113058/207537978-69feb17e-8092-411e-b140-9842d52d7f50.mov


