#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class FriendsDto : public oatpp::DTO {
 public:
  DTO_INIT(FriendsDto, DTO)

  DTO_FIELD(String, friends);
};

#include OATPP_CODEGEN_END(DTO)