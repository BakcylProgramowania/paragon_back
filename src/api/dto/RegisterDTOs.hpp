#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class RegisterDto : public oatpp::DTO {
 public:
  DTO_INIT(RegisterDto, DTO)

  DTO_FIELD(String, username);
  DTO_FIELD(String, password);
  DTO_FIELD(String, email);
};

class RegisterResponseDto : public oatpp::DTO {
 public:
  DTO_INIT(RegisterResponseDto, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(Int32, errorCode);
};

#include OATPP_CODEGEN_END(DTO)