#include "server.h"

SimpleAuthProvider authProvider;

RichHttpServer<RichHttpConfig> server(80, authProvider);

void handleGet(RequestContext& request) {
  StaticJsonDocument<10 * 1024> obj;
  appSetting.toJson(obj);

  request.response.json.set(obj);
}

void handleSet(RequestContext& request) {
  appSetting.fromJson(request.getJsonBody());

  loadSetting(appSetting);

  request.response.setCode(200);
}

void serverSetup() {
  server
    .buildHandler("/get")
    .on(HTTP_GET, handleGet);

  server
    .buildHandler("/set")
    .on(HTTP_POST, handleSet);

  server.clearBuilders();

  server.begin();
}

void serverLoop() {
  server.handleClient();
}
