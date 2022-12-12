#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

#define _PATH_MAX 4096

struct bookmark
{
      std::string name;
      std::string path;
};

std::vector<bookmark> contentsOfFile;
char cwd[_PATH_MAX];
std::vector<const char*> reservedWords = {".", "-s", "-a", "-r", "-h"};

void split(std::string str, std::string &a, std::string &b)
{
   int i = 0;
   while(str[i] != ' ')
   {
      if(i == str.size())
         return;
      a += str[i];
      ++i;
   }
   ++i;
   if(i == str.size())
      return;
   while(str[i] != '\0')
   {
      if(i == str.size())
         return;
      b += str[i];
      ++i;
   }
}

void readBookmark(std::string path)
{
   std::ifstream in(path);
   bookmark temp;
   std::string buf = "";
   std::string a;
   std::string b;

   while(std::getline(in, buf))
   {
      split(buf, a, b);
      temp.name = a.c_str();
      temp.path = b.c_str();
      contentsOfFile.push_back(temp);
      a = "";
      b = "";
   }
   in.close();
}

void saveBookmark(std::string path)
{
   std::ofstream out(path);
   for(int i = 0; i < contentsOfFile.size(); ++i)
   {
      out << contentsOfFile[i].name << " " << contentsOfFile[i].path << "\n";
   }
   out.close();
}

bool get_current_dir()
{
   if(getcwd(cwd, sizeof(cwd)) != NULL)
   {
      return true;
   }
   return false;
}

int main(int argc, char **argv)
{
   char *XDG               = getenv("XDG_CONFIG_HOME");
   std::string config_path = std::string(XDG) + "/.config.dupa";
   std::string tempVarPath = std::string(XDG) + "/.tempVar";

   if(argc == 1)
   {
      std::cout << "Usage: " << argv[0] << " [bookmark name]" << std::endl;
      return 0;
   }
   else if(argc == 2)
   {
      readBookmark(config_path);
      if((std::string)argv[1] == "-s")
      {
         for(int i = 1; i < contentsOfFile.size(); i++)
         {
            std::cout << contentsOfFile[i].name.c_str() << " <====>  "
                      << contentsOfFile[i].path.c_str() << std::endl;
         }
         return 0;
      }
      for(int i = 0; i < contentsOfFile.size(); i++)
      {
         if(contentsOfFile[i].name == argv[1])
         {
            std::ofstream envVar(tempVarPath);
            envVar << contentsOfFile[i].path.c_str();
            envVar.close();
            return 1;
         }
      }
      std::cout << "Bookmark not found" << std::endl;
   }
   else if(argc == 3)
   {
      readBookmark(config_path);
      if((std::string)argv[1] == "-a")
      {
         for(auto temp : reservedWords)
         {
            if(temp == (std::string)argv[2])
            {
               std::cout << "This name is reserved" << std::endl;
               return 0;
            }
         }
         for(int i = 0; i < contentsOfFile.size(); i++)
         {
            if(contentsOfFile[i].name == argv[2])
            {
               std::cout << "Bookmark with this name already exists"
                         << std::endl;
               return 0;
            }
         }
         if(get_current_dir())
         {
            bookmark newBookmark = { argv[2], cwd };
            contentsOfFile.push_back(newBookmark);
            saveBookmark(config_path);
         }
         else
         {
            std::cout << "Error while getting current directory" << std::endl;
            return 0;
         }
         return 0;
      }
      else if((std::string)argv[1] == "-r")
      {
         for(int i = 0; i < contentsOfFile.size(); i++)
         {
            if(contentsOfFile[i].name == argv[2])
            {
               contentsOfFile.erase(contentsOfFile.begin() + i);
               saveBookmark(config_path);
               return 0;
            }
         }
         std::cout << "Bookmark with this name doesn't exist" << std::endl;
      }
      else
      {
         std::cout << "Usage: " << argv[0] << " [bookmark name]" << std::endl;
         std::cout << "For help type: " << argv[0] << " -h" << std::endl;
         return 0;
      }
   }
   else
   {
      std::cout << "Too many arguments" << std::endl;
      return 0;
   }
   return 0;
}
