#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <sstream>

#include "config.hpp"
#include "retrieve.hpp"
#include "error.hpp"

  int Retrieve::stringToInt(std::string a) { //Utility for converting string to int
        int retVal;
        std::istringstream(a) >> retVal;
        return retVal;
  }

  std::string Retrieve::getUserData(std::string callsign) { //Download line containing user informations
        std::ifstream dataFile(FILENAME.c_str());
        if(!dataFile.good()) return "INVALID FILE";

        std::string line,result="";
        bool browsing = false;
        while(std::getline(dataFile,line)) {
            if(line.find("!CLIENTS") != std::string::npos) {
                browsing = true;
                continue;
            } else if(browsing && line.find("!AIRPORTS") != std::string::npos) break;
              else if(browsing && !line.rfind(callsign+":",0)) {
                  result = line;
                  break;
              }
        }

        if(!browsing || result=="") return "-1";
        else return result;
  }

  std::string Retrieve::infoToNextColon(std::string &data) { //Get next data separated from colons
      for(int i=0; i<(int)data.length(); i++) {
          if(data[i] != ':') continue;

          std::string toReturn = data.substr(0,i);
          data = data.substr(i+1,(int)data.length()-i-1);
          return toReturn;
      }

      return "";
  }

  void Retrieve::outputData(std::vector <std::string> &data, short int type) { //Output data
       if(type <=2) { //If Pilot or FollowMe
           for(int i=0; i<(int)pilotTitles.size(); i++) {
               if(pilotTitles[i] == "skip") continue;
               if(pilotTitles[i] == "Rating:") std::cout << pilotTitles[i] << " " << pilotRatings[this->stringToInt(data[i])] << "\n";
               else std::cout << pilotTitles[i] << " " << data[i] << "\n";
           }
       } else if(type == 3) { //if ATC
           for(int i=0; i<(int)atcTitles.size(); i++) {
               if(atcTitles[i] == "skip") continue;
               if(atcTitles[i] == "Rating:") std::cout << atcTitles[i] << " " << atcRatings[this->stringToInt(data[i])-1] << "\n";
               else if(atcTitles[i] == "Facility:") std::cout << atcTitles[i] << " " << atcFacilities[this->stringToInt(data[i])] << "\n";
               else std::cout << atcTitles[i] << " " << data[i] << "\n";
           }
       }

       std::cout << "\n";

  }

  bool Retrieve::retrieveUser(std::string callsign) {
       for(char& letter : callsign) letter = std::toupper(letter); //Capitalize callsign

       std::string result = this->getUserData(callsign).c_str();
       if(result == "INVALID FILE") {
           std::cout << FRED("FATAL ERROR:") << " There's a trouble with getting system runnin', please check your internet connectivity\n";
           return false;
       } else if(result == "-1") {
           std::cout << "User with this callsign isn't right now on IVAO, try again in 2mins - that's the refresh rate\n";
           return true;
       }

       short int type; //1-PILOT 2-ATC 3-FOLLOWME
       if(result.find(":PILOT::") != std::string::npos) type=1;
       else if(result.find(":FOLME::") != std::string::npos) type=2;
       else if(result.find(":ATC:") != std::string::npos) type=3;
       else {
          std::cout << FRED("FATAL ERROR:") << " Downloaded data are corrupted, wait 2mins and try running program once again\n";
          return false;
       }

       std::vector <std::string> sepData;
       int element=0;
       while(result.length()) {
            std::string value = this->infoToNextColon(result);
            if(value == "") continue;

            sepData.push_back(value);
            DEBUG printf("%d. %s\n",element+1,value.c_str());
            element++;
       }

       if(type <=2 && (int)sepData.size() != 40) {
            std::cout << FRED("ERROR:") << " User is connected, but they use colons in their Remarks, so we are unable to parse data correctly\n";
            return true;
       } else if(type == 3 && (int)sepData.size() != 22) {
            std::cout << FRED("ERROR") << " User is connected, but they use colons in their ATIS, so we are unable to parse data correctly\n";
            return true;
       }

       this->outputData(sepData,type);
       return true;
  }
