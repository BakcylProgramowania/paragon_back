#include <iostream>

#include "./AppComponent.hpp"
#include "./controller/MyController.hpp"
#include "oatpp-swagger/Controller.hpp"
#include "oatpp/network/Server.hpp"

namespace bakcyl {
namespace api {

void run() {
  /* Register Components in scope of run() method */
  AppComponent components;

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  oatpp::web::server::api::Endpoints docEndpoints;

  // docEndpoints.append(router->addController(UserController::createShared())->getEndpoints());

  /* Create MyController and add all of its endpoints to router */
  router->addController(oatpp::swagger::Controller::createShared(docEndpoints));
  router->addController(std::make_shared<MyController>());

  /* Get connection handler component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>,
                  connectionHandler);

  /* Get connection provider component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>,
                  connectionProvider);

  /* Create server which takes provided TCP connections and passes them to HTTP
   * connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print info about server port */
  OATPP_LOGI("MyApp", "Server running on port %s",
             connectionProvider->getProperty("port").getData());

  /* Run server */
  server.run();
}

}
}