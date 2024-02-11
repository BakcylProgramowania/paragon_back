#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class FriendDto : public oatpp::DTO {
 public:
  DTO_INIT(FriendDto, DTO)

  DTO_FIELD(String, id);
  DTO_FIELD(String, username);
};

class FriendsDto : public oatpp::DTO {
 public:
  DTO_INIT(FriendsDto, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(Fields<List<Object<FriendDto>>>, data);
};

class AddFriendDto : public oatpp::DTO {
 public:
  DTO_INIT(AddFriendDto, DTO)

  DTO_FIELD(String, id);
};

class AddFriendResponseDto : public oatpp::DTO {
 public:
  DTO_INIT(AddFriendResponseDto, DTO)

  DTO_FIELD(Boolean, success);
};

class RemoveFriendDto : public oatpp::DTO {
 public:
  DTO_INIT(RemoveFriendDto, DTO)

  DTO_FIELD(String, id);
};

class RemoveFriendResponseDto : public oatpp::DTO {
 public:
  DTO_INIT(RemoveFriendResponseDto, DTO)

  DTO_FIELD(Boolean, success);
};

#include OATPP_CODEGEN_END(DTO)