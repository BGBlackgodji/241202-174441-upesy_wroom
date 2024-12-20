#ifndef REST_H
#define REST_H

#include <RichHttpServer.h>

using namespace std;

using RichHttpConfig = RichHttp::Generics::Configs::EspressifBuiltin;
using RequestContext = RichHttpConfig::RequestContextType;

class Rest {
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
