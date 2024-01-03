#pragma once

#include "dto/DTOs.hpp"
#include "dto/LoginDTOs.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)  //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

 public:
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

    if (json && json->username && json->password) {
      if (json->username == "Jan34") {
        auto responseDto = LoginResponseDto::createShared();
        responseDto->success = true;
        return createDtoResponse(Status::CODE_200, responseDto);
      } else {
        auto responseDto = LoginResponseDto::createShared();
        responseDto->success = false;
        return createDtoResponse(Status::CODE_403, responseDto);
      }
    } else {
      auto responseDto = LoginResponseDto::createShared();
      responseDto->success = false;
      return createDtoResponse(Status::CODE_400, responseDto);
    }
  }
};

#include OATPP_CODEGEN_END(ApiController)  //<-- End Codegen