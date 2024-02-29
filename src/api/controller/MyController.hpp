#pragma once

#include "core/accountManager.hpp"
#include "core/authenticator.hpp"
#include "core/reciptOperations.hpp"
#include "dto/BalanceDTOs.hpp"
#include "dto/DTOs.hpp"
#include "dto/FriendsDTOs.hpp"
#include "dto/LoginDTOs.hpp"
#include "dto/ReciptDTOs.hpp"
#include "dto/RegisterDTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/utils/ConversionUtils.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

using namespace oatpp::web::server::handler;

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
 public:
  Database database;

  AccountManager accountMan;
  Authenticator auth;
  ReciptOperations reciptOper;

  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper),
        database(
            "mongodb+srv://"
            "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/"),
        accountMan(database),
        auth(database),
        reciptOper(database) {
    setDefaultAuthorizationHandler(
        std::make_shared<BearerAuthorizationHandler>("my-realm"));
  }

  ENDPOINT_INFO(getResource){
    info->summary = "getResource endpoint";
    info->addSecurityRequirement("bearer_auth");
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

  ENDPOINT_INFO(changeBalance){
    info->summary = "changeBalance endpoint";
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("POST", "/balance", changeBalance,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject),
           BODY_STRING(String, body)) {
    auto json = oatpp::parser::json::mapping::ObjectMapper::createShared()
                    ->readFromString<oatpp::Object<ChangeBalanceDto>>(body);

    auto responseDto = ChangeBalanceResponseDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    } else {
      auto amount = json->amount;
      bool balanceChanged = accountMan.changeBalance(authObject->token, amount);
      responseDto->success = balanceChanged;
      return createDtoResponse(Status::CODE_200, responseDto);
    }
  }

  ENDPOINT_INFO(getBalance){
    info->summary = "getBalance endpoint";
    info->addSecurityRequirement("bearer_auth");
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

  ENDPOINT_INFO(getFriends){
    info->summary = "getFriends endpoint";
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("GET", "/friends", getFriends,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject)) {
    auto responseDto = FriendsDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      responseDto->data = {};
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    std::vector<std::pair<std::string, std::string>> returnUserFriendList =
        accountMan.returnUserFriendList(authObject->token);

    oatpp::List<oatpp::Object<FriendDto>> siblings =
        oatpp::List<oatpp::Object<FriendDto>>::createShared();

    for (const auto& friendPair : returnUserFriendList) {
      auto friendDto = FriendDto::createShared();
      friendDto->id = friendPair.first;
      friendDto->username = friendPair.second;
      siblings->push_back(friendDto);
    }

    responseDto->success = true;
    responseDto->data = {};
    responseDto->data->push_back({"friends", siblings});

    return createDtoResponse(Status::CODE_200, responseDto);
  }

  ENDPOINT_INFO(addFriend){
    info->summary = "addFriends endpoint";
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("POST", "/addFriend", addFriend,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject),
           BODY_STRING(String, body)) {
    auto json = oatpp::parser::json::mapping::ObjectMapper::createShared()
                    ->readFromString<oatpp::Object<AddFriendDto>>(body);

    auto responseDto = AddFriendResponseDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    } else {
      bool addUserToFriendList =
          accountMan.addUserToFriendList(authObject->token, json->id);
      responseDto->success = addUserToFriendList;
      return createDtoResponse(Status::CODE_200, responseDto);
    }
  }

  ENDPOINT_INFO(removeFriend){
    info->summary = "removeFriends endpoint";
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("POST", "/removeFriend", removeFriend,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject),
           BODY_STRING(String, body)) {
    auto json = oatpp::parser::json::mapping::ObjectMapper::createShared()
                    ->readFromString<oatpp::Object<RemoveFriendDto>>(body);

    auto responseDto = RemoveFriendResponseDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    } else {
      bool removeUserFromFriendList =
          accountMan.removeUserFromFriendList(authObject->token, json->id);
      responseDto->success = removeUserFromFriendList;
      return createDtoResponse(Status::CODE_200, responseDto);
    }
  }

  ENDPOINT("POST", "/receipt", receipt,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject),
           BODY_STRING(String, body)) {
    auto json = oatpp::parser::json::mapping::ObjectMapper::createShared()
                    ->readFromString<oatpp::Object<ReciptDto>>(body);

    auto responseDto = ReciptResponseDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    } else {
      std::vector<Item> items;
      for (const auto& pair : *json->data) {
        auto& itemsList = pair.second;
        for (const auto& itemJson : *itemsList) {
          auto item = Item{itemJson->whoBuy->c_str(), itemJson->item->c_str(),
                           itemJson->price, itemJson->amount};
          items.push_back(item);
        }
      }

      auto friends = reciptOper.calculateReceipt(items);

      oatpp::List<oatpp::Object<ReciptFriendsDto>> friendsDto =
          oatpp::List<oatpp::Object<ReciptFriendsDto>>::createShared();

      for (const auto& friendItem : friends) {
          auto reciptFriendsDto = ReciptFriendsDto::createShared();
          reciptFriendsDto->userID = friendItem.userID;
          reciptFriendsDto->price = friendItem.price;
          friendsDto->push_back(reciptFriendsDto);
      }

      responseDto->success = true;
      responseDto->data = {};
      responseDto->data->push_back({"friends", friendsDto});
      return createDtoResponse(Status::CODE_200, responseDto);
    }
  }
};

#include OATPP_CODEGEN_END(ApiController)