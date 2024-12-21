#include "rest.h"

#include <ArduinoJson.h>

#include <core/setting.h>

SimpleAuthProvider Rest::authProvider;
RichHttpServer<RichHttpConfig> Rest::server(80, Rest::authProvider);

void Rest::get(RequestContext &request)
{
  StaticJsonDocument<10 * 1024> obj;
  appSetting.toJson(obj);

  request.response.json.set(obj);
}

void Rest::set(RequestContext &request) {
  appSetting.fromJson(request.getJsonBody());

  loadSetting(appSetting);

  request.response.setCode(200);
}

void Rest::load() {
  server
    .buildHandler("/")
    .on(HTTP_GET, get)
    .on(HTTP_POST, set);

  server.clearBuilders();

  server.begin();

  Serial.println("server ok");
}

void Rest::tick() {
  server.handleClient();
}
