#pragma once

#include "core/authenticator.hpp"
#include "dto/DTOs.hpp"
#include "dto/LoginDTOs.hpp"
#include "dto/RegisterDTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

using namespace oatpp::web::server::handler;

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
 public:
  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) /* Inject object mapper */)
    : oatpp::web::server::api::ApiController(objectMapper) 
  {
    setDefaultAuthorizationHandler(std::make_shared<BearerAuthorizationHandler>("my-realm"));
  }

  ENDPOINT("GET", "/my/secret/resource", getResource,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>, authObject)) 
  {
    if (authObject->token != "4e99e8c12de7e01535248d2bac85e732") {
        return createResponse(Status::CODE_401, "{\"success\":false}");
    }
    return createResponse(Status::CODE_200, "{\"success\":true}");
  }

  ENDPOINT("GET", "/", root) {
    auto dto = MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  }

  ENDPOINT("POST", "/login", postUsers, BODY_STRING(String, body)) {
    OATPP_LOGD("Test", "Request Body: %s", body->c_str());

    auto json = oatpp::parser::json::mapping::ObjectMapper::createShared()
                    ->readFromString<oatpp::Object<LoginDto>>(body);

    auto responseDto = LoginResponseDto::createShared();

    if (json && json->username && json->password) {
      Authenticator auth;
      bool loginSuccess = auth.authenticateUser(json->username, json->password);

      responseDto->success = loginSuccess;

      if (loginSuccess) {
        return createDtoResponse(Status::CODE_200, responseDto);
      } else {
        return createDtoResponse(Status::CODE_403, responseDto);
      }
    } else {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }
  }
  
  ENDPOINT("POST", "/register", postRegister, BODY_STRING(String, body)) {
    OATPP_LOGD("TEST", "Registered with username: %s",
               body->c_str());

    auto json = oatpp::parser::json::mapping::ObjectMapper::createShared()
                    ->readFromString<oatpp::Object<RegisterDto>>(body);

    auto responseDto = RegisterResponseDto::createShared();

    if (json && json->username && json->password && json->email) {
      Authenticator auth;

      bool registrationSuccess =
          auth.registerUser(json->username, json->password, json->email);

      responseDto->success = registrationSuccess;

      if (registrationSuccess) {
        return createDtoResponse(Status::CODE_201, responseDto);
      } else {
        return createDtoResponse(Status::CODE_500, responseDto);
      }
    } else {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }
  }
};

#include OATPP_CODEGEN_END(ApiController)  //<-- End Codegen