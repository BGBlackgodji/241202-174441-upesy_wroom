#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <WiFi.h>

using namespace std;

class Network {
    private:
        static string _ssid;
        static string _password;
        static int timeout;

    public:
        // return is success
        static bool connect(string ssid, string password);
        static bool load(string ssid, string password = "");
        
        static bool is2_4GHz(int networkIndex);

        static string GetLocalIPv4();
};

#endif
