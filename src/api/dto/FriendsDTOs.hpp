#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class FriendDto : public oatpp::DTO {
 public:
  DTO_INIT(FriendDto, DTO)

  DTO_FIELD(String, id);       // ID of the friend
  DTO_FIELD(String, username); // Username of the friend
};

class FriendsDto : public oatpp::DTO {
 public:
  DTO_INIT(FriendsDto, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(Fields<List<Object<FriendDto>>>, data);
};

#include OATPP_CODEGEN_END(DTO)