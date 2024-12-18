#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <WiFi.h>

class Network {
    private:
        static bool __connect(int timeout);

    public:
        // return is success
        static bool connect(std::string ssid, std::string password, int timeout = 20 * 1000);
        static void disconnect();

        static std::string GetIPv4();
};

#endif
