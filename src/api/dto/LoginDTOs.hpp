#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class LoginDto : public oatpp::DTO {
 public:
  DTO_INIT(LoginDto, DTO)

  DTO_FIELD(String, username);
  DTO_FIELD(String, password);
};

class LoginResponseDto : public oatpp::DTO {
 public:
  DTO_INIT(LoginResponseDto, DTO)

  DTO_FIELD(Boolean, success);
};

#include OATPP_CODEGEN_END(DTO)