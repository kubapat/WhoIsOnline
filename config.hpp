#ifndef CONFIG_HPP
#define CONFIG_HPP

#define DEBUG if(0)

  const std::string ADDRESS   = "http://api.ivao.aero/getdata/whazzup/whazzup.txt"; //IVAO API Address
  const std::string CHECKFILE = "sysconfig.txt"; //File for saving temporary system check data
  const std::string FILENAME  = "whazzup.txt"; //Name of downloaded IVAO API file
  const int TIMESTAMP = 120; //Refresh time in seconds

#endif
