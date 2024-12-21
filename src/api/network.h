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
        static bool is2_4GHz(int networkIndex);

        /**
         * @return is sucess 
         */
        static bool connect(string ssid, string password);
           
        static string GetLocalIPv4();

        static bool load(string ssid, string password = "");
        static bool tick();
};

#endif
