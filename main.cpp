#include <iostream>
#include <string>

#include "config.hpp"
#include "download.hpp"
#include "retrieve.hpp"
#include "error.hpp"

 int main(void) {
    std::cout << "IVAO Who is Online Finder by Jakub Pat\nTo find out details of the logged user, type their callsign and hit an ENTER button\nFor exit, type 'q' and hit an ENTER button\n";
    if(!Download::isConfigured()) { //Checks system configuration
        std::cout << FRED("FATAL ERROR:") << " You need to install wget in order to use IVAO Who is Online Finder\n";
        return -1;
    }
    Retrieve getData;

    while(true) {
        std::string command;
        std::cin >> command; //Get command

        if(command == "q") break; //Exit
        else {
          Download::downloadData(); //Update data
          if(!getData.retrieveUser(command)) return -2;
        }
    }

    return 0;
 }
