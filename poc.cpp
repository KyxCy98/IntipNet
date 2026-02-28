// Source - https://stackoverflow.com/q/23258464
// Posted by user1902689, modified by community. See post 'Timeline' for change history
// Retrieved 2026-02-28, License - CC BY-SA 3.0

#include <string>
#include <iostream>
using namespace std;

#include <netdb.h> // struct sockaddr, AF_INET, NI_NAMEREQD, getnameinfo
#include <string.h> // memset
#include <arpa/inet.h> // inet_pton

int main() {
   const string IPAddress { "66.249.68.9" };

   struct sockaddr structSockAddr;
   memset(&structSockAddr, 0, sizeof(structSockAddr));

   structSockAddr.sa_family = AF_INET;
   int inetPtonReturnValue { inet_pton(AF_INET, IPAddress.c_str(), &structSockAddr.sa_data) };
   if(1 != inetPtonReturnValue) {
      cout << "inetPtonReturnValue : " << inetPtonReturnValue << endl; // 0 = src doesn't contain valid address, -1 = af isn't a valid family
   }

   char hostBuffer[10000];
   char serviceBuffer[1000];

   int getNameInfoReturnValue { getnameinfo(&structSockAddr, sizeof(structSockAddr), hostBuffer, sizeof(hostBuffer), serviceBuffer, sizeof(serviceBuffer), NI_NAMEREQD) };

   if(0 != getNameInfoReturnValue) {
      cout << "getNameInfoReturnValue : " << getNameInfoReturnValue << endl
           << "gai_strerror() : " << gai_strerror(getNameInfoReturnValue) << endl;
   } else {
      cout << "IPAddress : " << IPAddress << endl
           << "hostBuffer : " << hostBuffer << endl
           << "serviceBuffer : " << serviceBuffer << endl;
   }
}
