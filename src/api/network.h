#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <WiFi.h>

using namespace std;

class Network {
    public:
        // return is success
        static bool connect(string ssid, string password = "", int timeout = 20 * 1000);
        static void disconnect();
        
        static bool is2_4GHz(int networkIndex);

        static string GetLocalIPv4();
};

#endif
