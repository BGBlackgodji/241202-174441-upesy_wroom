#include "server.h"

SimpleAuthProvider Server::authProvider;
RichHttpServer<RichHttpConfig> Server::server(80, Server::authProvider);

void Server::get(RequestContext &request)
{
  StaticJsonDocument<10 * 1024> obj;
  appSetting.toJson(obj);

  request.response.json.set(obj);
}

void Server::set(RequestContext &request) {
  appSetting.fromJson(request.getJsonBody());

  loadSetting(appSetting);

  request.response.setCode(200);
}

void Server::load() {
  server
    .buildHandler("/")
    .on(HTTP_GET, get)
    .on(HTTP_POST, set);

  server.clearBuilders();

  server.begin();
}

void Server::tick() {
  server.handleClient();
}
