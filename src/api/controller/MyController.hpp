#pragma once

#include "core/accountManager.hpp"
#include "core/authenticator.hpp"
#include "core/receiptOperations.hpp"
#include "dto/BalanceDTOs.hpp"
#include "dto/DTOs.hpp"
#include "dto/FriendsDTOs.hpp"
#include "dto/LoginDTOs.hpp"
#include "dto/ReceiptDTOs.hpp"
#include "dto/RegisterDTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/utils/ConversionUtils.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

using namespace oatpp::web::server::handler;

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen

namespace bakcyl {
namespace api {
/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
 public:
  bakcyl::database::Database database;

  bakcyl::core::AccountManager accountMan;
  bakcyl::core::Authenticator auth;
  bakcyl::core::ReceiptOperations receiptOper;

  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper),
        database(
            "mongodb+srv://"
            "bakcyl324:Bakcyl768324@paragondatabase.jedczob.mongodb.net/"),
        accountMan(database),
        auth(database),
        receiptOper(database) {
    setDefaultAuthorizationHandler(
        std::make_shared<BearerAuthorizationHandler>("my-realm"));
  }

  ENDPOINT_INFO(getResource) {
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
    auto dto = bakcyl::api::MyDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello World!";
    return createDtoResponse(Status::CODE_200, dto);
  
  }
  ENDPOINT_INFO(postUsers) {
    info->summary = "Authenticate users";
    info->addConsumes<oatpp::Object<bakcyl::api::LoginDto>>("application/json");
  }

  ENDPOINT("POST", "/login", postUsers, BODY_STRING(String, body)) {
    OATPP_LOGD("Test", "Request Body: %s", body->c_str());

    auto json =
        oatpp::parser::json::mapping::ObjectMapper::createShared()
            ->readFromString<oatpp::Object<bakcyl::api::LoginDto>>(body);

    auto responseDto = bakcyl::api::LoginResponseDto::createShared();

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

  ENDPOINT_INFO(postRegister) {
    info->summary = "Create users";
    info->addConsumes<oatpp::Object<bakcyl::api::RegisterDto>>("application/json");
  }
  ENDPOINT("POST", "/register", postRegister, BODY_STRING(String, body)) {
    OATPP_LOGD("TEST", "Registered with username: %s", body->c_str());

    auto json =
        oatpp::parser::json::mapping::ObjectMapper::createShared()
            ->readFromString<oatpp::Object<bakcyl::api::RegisterDto>>(body);

    auto responseDto = bakcyl::api::RegisterResponseDto::createShared();

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

  ENDPOINT_INFO(changeBalance) {
    info->summary = "Change balance";
    info->addConsumes<oatpp::Object<bakcyl::api::ChangeBalanceDto>>("application/json");
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("POST", "/balance", changeBalance,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject),
           BODY_STRING(String, body)) {
    auto json =
        oatpp::parser::json::mapping::ObjectMapper::createShared()
            ->readFromString<oatpp::Object<bakcyl::api::ChangeBalanceDto>>(
                body);

    auto responseDto = bakcyl::api::ChangeBalanceResponseDto::createShared();

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

  ENDPOINT_INFO(getBalance) {
    info->summary = "getBalance endpoint";
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("GET", "/balance", getBalance,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject)) {
    auto responseDto = bakcyl::api::BalanceDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      responseDto->balance = 0.00;
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    responseDto->success = true;
    responseDto->balance = accountMan.getBalance(authObject->token);
    return createDtoResponse(Status::CODE_200, responseDto);
  }

  ENDPOINT_INFO(getFriends) {
    info->summary = "getFriends endpoint";
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("GET", "/friends", getFriends,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject)) {
    auto responseDto = bakcyl::api::FriendsDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      responseDto->data = {};
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    std::vector<std::pair<std::string, std::string>> returnUserFriendList =
        accountMan.returnUserFriendList(authObject->token);

    oatpp::List<oatpp::Object<bakcyl::api::FriendDto>> siblings =
        oatpp::List<oatpp::Object<bakcyl::api::FriendDto>>::createShared();

    for (const auto& friendPair : returnUserFriendList) {
      auto friendDto = bakcyl::api::FriendDto::createShared();
      friendDto->id = friendPair.first;
      friendDto->username = friendPair.second;
      siblings->push_back(friendDto);
    }

    responseDto->success = true;
    responseDto->data = {};
    responseDto->data->push_back({"friends", siblings});

    return createDtoResponse(Status::CODE_200, responseDto);
  }

  ENDPOINT_INFO(addFriend) {
    info->summary = "Add Friend";
    info->addConsumes<oatpp::Object<bakcyl::api::AddFriendDto>>("application/json");
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("POST", "/addFriend", addFriend,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject),
           BODY_STRING(String, body)) {
    auto json =
        oatpp::parser::json::mapping::ObjectMapper::createShared()
            ->readFromString<oatpp::Object<bakcyl::api::AddFriendDto>>(body);

    auto responseDto = bakcyl::api::AddFriendResponseDto::createShared();

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

  ENDPOINT_INFO(removeFriend) {
    info->summary = "Remove Friend";
    info->addConsumes<oatpp::Object<bakcyl::api::RemoveFriendDto>>("application/json");
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("POST", "/removeFriend", removeFriend,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject),
           BODY_STRING(String, body)) {
    auto json =
        oatpp::parser::json::mapping::ObjectMapper::createShared()
            ->readFromString<oatpp::Object<bakcyl::api::RemoveFriendDto>>(body);

    auto responseDto = bakcyl::api::RemoveFriendResponseDto::createShared();

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

  ENDPOINT_INFO(receipt) {
    info->summary = "Create receipt";
    info->addConsumes<oatpp::Object<bakcyl::api::ReceiptDto>>("application/json");
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("POST", "/receipt", receipt,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject),
           BODY_STRING(String, body)) {
    auto json =
        oatpp::parser::json::mapping::ObjectMapper::createShared()
            ->readFromString<oatpp::Object<bakcyl::api::ReceiptDto>>(body);

    auto responseDto = bakcyl::api::ReceiptResponseDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    } else {
      std::vector<bakcyl::core::Item> items;
      for (const auto& pair : *json->data) {
        auto& itemsList = pair.second;
        for (const auto& itemJson : *itemsList) {
          auto item = bakcyl::core::Item{itemJson->whoBuy->c_str(),
                                         itemJson->item->c_str(),
                                         itemJson->price, itemJson->amount};
          items.push_back(item);
        }
      }

      auto friends = receiptOper.calculateReceipt(items);

      if (friends.empty()) {
        responseDto->success = false;
        return createDtoResponse(Status::CODE_400, responseDto);
      }

      bakcyl::core::Receipt receipt;
      receipt.author = database.getUserIDUsingToken(authObject->token);
      receipt.receiptName = json->receiptName;
      receipt.items = items;

      auto errorCode = receiptOper.saveReceipt(receipt);

      if (errorCode != 0) {
        responseDto->success = false;
        return createDtoResponse(Status::CODE_400, responseDto);
      }

      oatpp::List<oatpp::Object<bakcyl::api::ReceiptFriendsDto>> friendsDto =
          oatpp::List<
              oatpp::Object<bakcyl::api::ReceiptFriendsDto>>::createShared();

      for (const auto& friendItem : friends) {
        auto receiptFriendsDto = bakcyl::api::ReceiptFriendsDto::createShared();
        receiptFriendsDto->userID = friendItem.userID;
        receiptFriendsDto->price = friendItem.price;
        friendsDto->push_back(receiptFriendsDto);
      }

      responseDto->success = true;
      responseDto->data = {};
      responseDto->data->push_back({"friends", friendsDto});
      return createDtoResponse(Status::CODE_200, responseDto);
    }
  }

  ENDPOINT_INFO(getItemsToPay) {
    info->summary = "Get items to pay";
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("GET", "/itemsToPay", getItemsToPay,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject)) {
    auto responseDto = bakcyl::api::ReceiptItemsToPayDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    return createDtoResponse(Status::CODE_200, responseDto);
  }


  ENDPOINT_INFO(itemPaid) {
    info->summary = "The item will be marked as purchased";
    info->addConsumes<oatpp::Object<bakcyl::api::ReceiptItemPaidDto>>("application/json");
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("POST", "/itemPaid", itemPaid,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject),
          BODY_STRING(String, body)) {

    auto json =
        oatpp::parser::json::mapping::ObjectMapper::createShared()
            ->readFromString<oatpp::Object<bakcyl::api::ReceiptItemPaidDto>>(body);  

    auto responseDto = bakcyl::api::ReceiptResponseItemPaidDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    responseDto->success = true;
    return createDtoResponse(Status::CODE_200, responseDto);
  }
};

}  // namespace api
}  // namespace bakcyl

#include OATPP_CODEGEN_END(ApiController)