#pragma once

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/macro/component.hpp"

namespace bakcyl {
namespace api {

/**
 *  Swagger ui is served at
 *  http://host:port/swagger/ui
 */
class SwaggerComponent {
 public:
  /**
   *  General API docs info
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>,
                         swaggerDocumentInfo)
  ([] {
    oatpp::swagger::DocumentInfo::Builder builder;

    builder.setTitle("PARAGON")
        .setDescription(
            "Example project for scanning receipts and splitting bills with "
            "friends, accompanied by Swagger documentation.")
        .setVersion("1.0")
        .setContactName("Bakcyl programowania 2024")
        .setContactUrl("https://paragon.wroc.ovh/")

        .setLicenseName("Apache License, Version 2.0")
        .setLicenseUrl("http://www.apache.org/licenses/LICENSE-2.0")

        .addServer("http://localhost:8000", "server on localhost")
        .addServer("https://paragon.wroc.ovh/", "Paragon")
        .addServer("https://paragon-staging.wroc.ovh/", "Paragon-staging")

        .addSecurityScheme("bearer_auth",
                           oatpp::swagger::DocumentInfo::SecuritySchemeBuilder::
                               DefaultBearerAuthorizationSecurityScheme("JWT"));

    return builder.build();
  }());

  /**
   *  Swagger-Ui Resources (<oatpp-examples>/lib/oatpp-swagger/res)
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>,
                         swaggerResources)
  ([] {
    // Make sure to specify correct full path to oatpp-swagger/res folder !!!
    return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
  }());
};

}  // namespace api
}  // namespace bakcyl