#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <string>
#include <list>
#include <RichHttpServer.h>
#include <ArduinoJson.h>
#include <core/setting.h>

using namespace std;

using RichHttpConfig = RichHttp::Generics::Configs::EspressifBuiltin;
using RequestContext = RichHttpConfig::RequestContextType;

class Server {
    private:
        static SimpleAuthProvider authProvider;
        static RichHttpServer<RichHttpConfig> server;

        static void get(RequestContext& request);
        static void set(RequestContext& request);

    public:
        static void load();
        static void tick();
};

#endif
