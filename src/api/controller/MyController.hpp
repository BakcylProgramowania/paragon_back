#pragma once

#include "core/authenticator.hpp"
#include "core/accountManager.hpp"
#include "dto/DTOs.hpp"
#include "dto/LoginDTOs.hpp"
#include "dto/RegisterDTOs.hpp"
#include "dto/BalanceDTOs.hpp"
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
  Database database; // Instantiate only one database object

  AccountManager accountMan;
  Authenticator auth;

MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper),
        database("mongodb+srv://"
                 "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/"),
        accountMan(database),
        auth(database) { // Pass the database to Authenticator constructor
    setDefaultAuthorizationHandler(
        std::make_shared<BearerAuthorizationHandler>("my-realm"));
  }


  ENDPOINT("GET", "/my/secret/resource", getResource,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject)) {
    if (!auth.tokenCheck(authObject->token))
      return createResponse(Status::CODE_401, "{\"success\":false}");

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

      std::string token = auth.authenticateUser(json->username, json->password);

      bool loginSuccess = false;
      if (token != "") loginSuccess = true;
      responseDto->success = loginSuccess;

      if (loginSuccess) {
        auto response = createDtoResponse(Status::CODE_200, responseDto);
        response->putHeader("Authorization", "Bearer " + token);
        return response;
      } else {
        return createDtoResponse(Status::CODE_403, responseDto);
      }
    } else {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }
  }

  ENDPOINT("POST", "/register", postRegister, BODY_STRING(String, body)) {
    OATPP_LOGD("TEST", "Registered with username: %s", body->c_str());

    auto json = oatpp::parser::json::mapping::ObjectMapper::createShared()
                    ->readFromString<oatpp::Object<RegisterDto>>(body);

    auto responseDto = RegisterResponseDto::createShared();

    if (json && json->username && json->password && json->email) {

      std::pair<int, std::string> registerPair =
          auth.registerUser(json->username, json->password, json->email);

      int errorCode = registerPair.first;
      std::string token = registerPair.second;

      if (errorCode == 0)
        responseDto->success = true;
      else
        responseDto->success = false;
      responseDto->errorCode = errorCode;

      if (errorCode == 0) {
        auto response = createDtoResponse(Status::CODE_201, responseDto);
        response->putHeader("Authorization", "Bearer " + token);
        return response;
      } else if (errorCode == 1) {
        return createDtoResponse(Status::CODE_400, responseDto);
      } else {
        return createDtoResponse(Status::CODE_409, responseDto);
      }
    } else {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }
  }

  ENDPOINT("POST", "/balance", changeBalance,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject), BODY_STRING(String, body)) {
    auto json = oatpp::parser::json::mapping::ObjectMapper::createShared()
                    ->readFromString<oatpp::Object<ChangeBalanceDto>>(body);

    auto responseDto = ChangeBalanceResponseDto::createShared();
    
    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    }else{
      auto amount = json->amount;
      bool balanceChanged = accountMan.changeBalance(authObject->token, amount);
      responseDto->success = balanceChanged;
      return createDtoResponse(Status::CODE_200, responseDto);
      }
  }

  ENDPOINT("GET", "/balance", getBalance,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject)) {
    auto responseDto = BalanceDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      responseDto->balance = 0.00;
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    responseDto->success = true;
    responseDto->balance = accountMan.getBalance(authObject->token);
    return createDtoResponse(Status::CODE_200, responseDto);
  }
};

#include OATPP_CODEGEN_END(ApiController)  //<-- End Codegen