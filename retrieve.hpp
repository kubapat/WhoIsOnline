#ifndef RETRIEVE_HPP
#define RETRIEVE_HPP

#include <vector>

  const std::vector <std::string> pilotRatings {
      "Observer","Basic Flight Student (FS1)","Flight Student (FS2)","Advanced Flight Student (FS3)","Private Pilot (PP)",
      "Senior Private Pilot (SPP)","Commercial Pilot (CP)","Airline Transport Pilot (ATP)",
      "Senior Flight Instructor (SFI)","Chief Flight Instructor (CFI)"
  };

  const std::vector <std::string> atcRatings {
      		"Observer","ATC Applicant (AS1)","ATC Trainee (AS2)","Advanced ATC Trainee (AS3)",
                "Aerodrome Controller (ADC)","Approach Controller (APC)","Center Controller (ACC)",
                "Senior Controller (SEC)","Senior ATC Instructor (SAI)","Chief ATC Instructor (CAI)"
  };

  const std::vector <std::string> atcFacilities {
                "Observer", "Flight Information", "Delivery",
                "Ground", "Tower", "Approach", "ACC", "Departure"
  };

  const std::vector <std::string> pilotTitles {
      "Callsign:","VID:","Name:","Type:","Latitude:",
      "Longitude:","Altitude:","Groundspeed:","Aircraft:","FPL cruise speed:",
      "Departure:","FPL cruise level:","Arrival:","Server:","Protocol:",
      "Rating:","Sqawk:","skip","skip","skip","Flight Rules:","skip","skip","skip","skip","skip","skip",
      "Alternate Aerodrome:","Remarks:","Route:"
  };

  const std::vector <std::string> atcTitles {
      "Callsign:","VID:","Name:","Type:","Frequency:","Latitude:",
      "Longitude","skip","skip","Server:","Protocol:","Rating:","skip","Facility:","skip","ATIS:"
  };


  class Retrieve {
      public:
        bool retrieveUser(std::string callsign);

      private:
        std::string getUserData(std::string callsign);
        std::string infoToNextColon(std::string &data);
        void outputData(std::vector <std::string> &data, short int type);
        int  stringToInt(std::string a);
  };

#endif
