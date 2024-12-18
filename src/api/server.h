#ifndef SERVERHANDLER_H
#define SERVERHANDLER_H

#include <string>
#include <list>
#include <RichHttpServer.h>
#include <ArduinoJson.h>
#include <core/setting.h>
#include <Arduino.h>

using namespace std;

using RichHttpConfig = RichHttp::Generics::Configs::EspressifBuiltin;
using RequestContext = RichHttpConfig::RequestContextType;

extern RichHttpServer<RichHttpConfig> server;

void handleGet(RequestContext& request);
void handleSet(RequestContext& request);

void serverSetup();
void serverLoop();

#endif
