


#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <fstream>
#include <map>
#include <iterator>
#include <algorithm>
#include <cstdlib>
#include <pthread.h>
#include <stdlib.h> 
using namespace std; 









int main(){


      std::ifstream infile("seeder_list_1.txt");

      std::multimap<string, string> rem;

      std::string line;


      while (std::getline(infile, line))
      {
          std::istringstream iss(line);
          string a, b;
          if (!(iss >> a >> b)) { break; } // error

          rem.insert(std::pair<string, string>(a, b));
          // process pair (a,b)
      }



      for (std::pair<string, string> elem : rem){
        cout<<"chla";
       std::cout << elem.first << " :: " << elem.second << std::endl;
      }

return 0;

}


