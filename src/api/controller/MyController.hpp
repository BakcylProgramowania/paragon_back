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
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/utils/ConversionUtils.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include <oatpp/web/protocol/http/outgoing/Response.hpp>

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

    if (!json && !json->username && !json->password) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }

    std::string token = auth.authenticateUser(json->username, json->password);

    bool loginSuccess = false;
    if (token != "") loginSuccess = true;
    responseDto->success = loginSuccess;

    if (loginSuccess) {
      auto response = createDtoResponse(Status::CODE_200, responseDto);
      response->putHeader("Authorization", "Bearer " + token);
      return response;
    } else
      return createDtoResponse(Status::CODE_403, responseDto);
  }

  ENDPOINT_INFO(postRegister) {
    info->summary = "Create users";
    info->addConsumes<oatpp::Object<bakcyl::api::RegisterDto>>(
        "application/json");
  }

  ENDPOINT("POST", "/register", postRegister, BODY_STRING(String, body)) {
    OATPP_LOGD("TEST", "Registered with username: %s", body->c_str());

    auto json =
        oatpp::parser::json::mapping::ObjectMapper::createShared()
            ->readFromString<oatpp::Object<bakcyl::api::RegisterDto>>(body);

    auto responseDto = bakcyl::api::RegisterResponseDto::createShared();

    if (!json && !json->username && !json->password && !json->email) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }

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
    } else if (errorCode == 1)
      return createDtoResponse(Status::CODE_400, responseDto);
    else
      return createDtoResponse(Status::CODE_409, responseDto);
  }

  ENDPOINT_INFO(changeBalance) {
    info->summary = "Change balance";
    info->addConsumes<oatpp::Object<bakcyl::api::ChangeBalanceDto>>(
        "application/json");
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
    }

    if (!json || !json->amount) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }

    bool balanceChanged =
        accountMan.changeBalance(authObject->token, json->amount);
    responseDto->success = balanceChanged;
    return createDtoResponse(Status::CODE_200, responseDto);
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
    info->addConsumes<oatpp::Object<bakcyl::api::AddFriendDto>>(
        "application/json");
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
    }

    if (!json || !json->username) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }

    bool addUserToFriendList =
        accountMan.addUserToFriendList(authObject->token, json->username);
    responseDto->success = addUserToFriendList;
    return createDtoResponse(Status::CODE_200, responseDto);
  }

  ENDPOINT_INFO(removeFriend) {
    info->summary = "Remove Friend";
    info->addConsumes<oatpp::Object<bakcyl::api::RemoveFriendDto>>(
        "application/json");
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
    }

    if (!json || !json->username) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }

    bool removeUserFromFriendList =
        accountMan.removeUserFromFriendList(authObject->token, json->username);
    responseDto->success = removeUserFromFriendList;
    return createDtoResponse(Status::CODE_200, responseDto);
  }

  ENDPOINT_INFO(receipt) {
    info->summary = "Create receipt";
    info->addConsumes<oatpp::Object<bakcyl::api::ReceiptDto>>(
        "application/json");
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
    }
    
    if (!json || !json->data || !json->receiptName) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }

    std::vector<bakcyl::core::Item> items;
    for (const auto& pair : *json->data) {
      auto& itemsList = pair.second;
      for (const auto& itemJson : *itemsList) {
        auto item = bakcyl::core::Item{itemJson->whoBuy->c_str(),
                                       itemJson->item->c_str(), itemJson->price,
                                       itemJson->amount};
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

  ENDPOINT_INFO(getReceipts) {
    info->summary = "getReceipts endpoint";
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("GET", "/receipts", getReceipts,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject)) {
    auto responseDto = bakcyl::api::ReceiptsResponseDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      responseDto->data = {};
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    auto recipts = receiptOper.getReceipts(authObject->token);

    if (recipts.empty()) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }

    oatpp::List<oatpp::Object<bakcyl::api::ReceiptShortDto>> receiptsDto =
        oatpp::List<
            oatpp::Object<bakcyl::api::ReceiptShortDto>>::createShared();

    for (const auto& recipt : recipts) {
      auto receiptDto = bakcyl::api::ReceiptShortDto::createShared();
      receiptDto->receiptName = recipt.receiptName;
      receiptDto->receiptID = recipt.receiptID;
      receiptsDto->push_back(receiptDto);
    }

    responseDto->success = true;
    responseDto->data = {};
    responseDto->data->push_back({"receipts", receiptsDto});
    return createDtoResponse(Status::CODE_200, responseDto);
  }

  ENDPOINT_INFO(getReceipt) {
    info->summary = "getReceipt endpoint";
    info->addConsumes<oatpp::Object<bakcyl::api::getReceiptDto>>(
        "application/json");
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("POST", "/getReceipt", getReceipt,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject),
           BODY_STRING(String, body)) {
    auto json =
        oatpp::parser::json::mapping::ObjectMapper::createShared()
            ->readFromString<oatpp::Object<bakcyl::api::getReceiptDto>>(body);

    auto responseDto = bakcyl::api::getReceiptResponseDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    if (!json || !json->receiptID) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }

    auto receipt = receiptOper.getReceipt(json->receiptID);

    oatpp::List<oatpp::Object<bakcyl::api::ReceiptItemsDto>> receiptItemsDto =
        oatpp::List<
            oatpp::Object<bakcyl::api::ReceiptItemsDto>>::createShared();

    for (const auto& item : receipt.items) {
      auto receiptItemDto = bakcyl::api::ReceiptItemsDto::createShared();
      receiptItemDto->whoBuy = item.whoBuy;
      receiptItemDto->item = item.itemName;
      receiptItemDto->price = item.price;
      receiptItemsDto->push_back(receiptItemDto);
    }

    responseDto->success = true;
    responseDto->author = receipt.author;
    responseDto->receiptName = receipt.receiptName;
    responseDto->date = receipt.date;
    responseDto->data = {};
    responseDto->data->push_back({"items", receiptItemsDto});
    return createDtoResponse(Status::CODE_200, responseDto);
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
      responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    auto itemsToPay = receiptOper.getItemsToPay(authObject->token);

    oatpp::List<oatpp::Object<bakcyl::api::ReceiptItemToPayDto>>
        receiptItemsToPayDto = oatpp::List<
            oatpp::Object<bakcyl::api::ReceiptItemToPayDto>>::createShared();

    for (const auto& item : itemsToPay) {
      auto receiptItemToPayDto =
          bakcyl::api::ReceiptItemToPayDto::createShared();
      receiptItemToPayDto->receiptID = item.receiptID;
      receiptItemToPayDto->itemName = item.itemName;
      receiptItemToPayDto->price = item.price;
      receiptItemsToPayDto->push_back(receiptItemToPayDto);
    }

    responseDto->success = true;
    responseDto->data = {};
    responseDto->data->push_back({"items", receiptItemsToPayDto});
    return createDtoResponse(Status::CODE_200, responseDto);
  }

  ENDPOINT_INFO(itemPaid) {
    info->summary = "The item will be marked as purchased";
    info->addConsumes<oatpp::Object<bakcyl::api::ReceiptItemPaidDto>>(
        "application/json");
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("POST", "/itemPaid", itemPaid,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>,
                         authObject),
           BODY_STRING(String, body)) {
    auto json =
        oatpp::parser::json::mapping::ObjectMapper::createShared()
            ->readFromString<oatpp::Object<bakcyl::api::ReceiptItemPaidDto>>(
                body);

    auto responseDto = bakcyl::api::ReceiptResponseItemPaidDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    if (!json || !json->receiptID || !json->itemName) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }

    responseDto->success = receiptOper.paidForItem(
        json->receiptID, json->itemName, authObject->token);
    return createDtoResponse(Status::CODE_200, responseDto);
  }
  
  ENDPOINT_INFO(mergeReceipts) {
    info->summary = "MergeReceipt endpoint";
    info->addSecurityRequirement("bearer_auth");
  }


  ENDPOINT("POST", "/mergeReceipt", mergeReceipts,
           AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>, authObject),
           BODY_STRING(String, body)) {

    auto json = oatpp::parser::json::mapping::ObjectMapper::createShared()
    ->readFromString<oatpp::Object<bakcyl::api::MergeReceiptsDto>>(body);

    auto responseDto = bakcyl::api::MergeReceiptsResponseDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
        responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    if (!json || !json->receiptsId || !json->receiptName) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }

    std::vector<std::string> receiptIDs;

    for (auto& receiptId : *json->receiptsId)
      receiptIDs.push_back(receiptId);

    std::string receiptName = json->receiptName;
    std::string author = database.getUserIDUsingToken(authObject->token);

    int errorCode = receiptOper.mergeReceipt(receiptIDs, receiptName, author);

    if (errorCode != 0) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    } else {
      responseDto->success = true;
      responseDto->receiptName = receiptName;
      return createDtoResponse(Status::CODE_200, responseDto);
    }
  }

  ENDPOINT_INFO(unmergeReceipts) {
    info->summary = "UnmergeReceipt endpoint";
    info->addSecurityRequirement("bearer_auth");
  }

  ENDPOINT("POST", "/unmergeReceipt", unmergeReceipts,
            AUTHORIZATION(std::shared_ptr<DefaultBearerAuthorizationObject>, authObject),
            BODY_STRING(String, body)) {
    
    auto json = oatpp::parser::json::mapping::ObjectMapper::createShared()
    ->readFromString<oatpp::Object<bakcyl::api::UnmergeReceiptsDto>>(body);

    auto responseDto = bakcyl::api::UnmergeReceiptResponseDto::createShared();

    if (!auth.tokenCheck(authObject->token)) {
        responseDto->success = false;
      return createDtoResponse(Status::CODE_401, responseDto);
    }

    if (!json || !json->receiptId) {
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }

    std::string receiptId = json->receiptId;
    
    int errorCode = receiptOper.unmergeReceipt(receiptId);

    if (errorCode != 0) {
        responseDto->success = false;
        return createDtoResponse(Status::CODE_400, responseDto);
    } else{
      responseDto->success = true;
      return createDtoResponse(Status::CODE_200, responseDto);
    }
  }
};

}  // namespace api
}  // namespace bakcyl

#include OATPP_CODEGEN_END(ApiController)