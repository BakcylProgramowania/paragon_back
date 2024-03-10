#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace bakcyl {
namespace api {

class ReceiptItemsDto : public oatpp::DTO {
 public:
  DTO_INIT(ReceiptItemsDto, DTO)

  DTO_FIELD(String, whoBuy);
  DTO_FIELD(String, item);
  DTO_FIELD(Int32, price);
  DTO_FIELD(Int32, amount);
};

class ReceiptFriendsDto : public oatpp::DTO {
 public:
  DTO_INIT(ReceiptFriendsDto, DTO)

  DTO_FIELD(String, userID);
  DTO_FIELD(Int32, price);
};

class ReceiptDto : public oatpp::DTO {
 public:
  DTO_INIT(ReceiptDto, DTO)

  DTO_FIELD(String, receiptName);
  DTO_FIELD(Fields<List<Object<ReceiptItemsDto>>>, data);
};

class ReceiptResponseDto : public oatpp::DTO {
  DTO_INIT(ReceiptResponseDto, DTO);

  DTO_FIELD(Boolean, success);
  DTO_FIELD(Fields<List<Object<ReceiptFriendsDto>>>, data);
};

}
}

#include OATPP_CODEGEN_END(DTO)