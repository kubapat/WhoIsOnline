#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>

#include "config.hpp"
#include "download.hpp"

  void writeTimeToFile() { //Writes current time in seconds to config file, which allows to reduce download frequency
       long long int curTime = time(0);
       system("rm updated.txt > /dev/null 2> /dev/null");
       std::ofstream timeFile("updated.txt");
       timeFile << curTime;
       timeFile.close();
  }

  bool Download::isConfigured() { //Checks whether system contains required software
      bool exec = system(("wget > /dev/null 2> ./"+CHECKFILE).c_str());
      if(!exec) return false;

      std::ifstream configFile(CHECKFILE);
      if(configFile.good()) {
           std::string line;
           bool found = false;
           while(std::getline(configFile,line)) {
                 if(line.find("missing URL") != std::string::npos) {
                      found = true;
                      break;
                 }
           }

           system(("rm "+CHECKFILE).c_str());
           return found;
      } else return false;
  }

  void Download::downloadData() { //Downloads desired file
     std::ifstream dataFile(FILENAME.c_str());
     if(!dataFile.good()) system(("wget "+ADDRESS+" > /dev/null 2> /dev/null").c_str()), writeTimeToFile(); //If File doesn't exist
     else {
        long long int readTime,curTime = time(0);

        std::ifstream timeFile("updated.txt"); //Download last download time
        timeFile >> readTime;
        timeFile.close();

        if(curTime-TIMESTAMP > readTime) { //If it was updated more than TIMESTAMP ago, update it
               system(("rm "+FILENAME).c_str());
               system(("wget "+ADDRESS+" > /dev/null 2> /dev/null").c_str());
               writeTimeToFile();
        }
     }
  }
