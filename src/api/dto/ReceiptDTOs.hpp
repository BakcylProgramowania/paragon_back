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
  DTO_FIELD(Float32, price);
  DTO_FIELD(Float32, amount);
};

class ReceiptShortDto : public oatpp::DTO {
 public:
  DTO_INIT(ReceiptShortDto, DTO)

  DTO_FIELD(String, receiptName);
  DTO_FIELD(String, receiptID);
};

class ReceiptItemToPayDto : public oatpp::DTO {
  DTO_INIT(ReceiptItemToPayDto, DTO);

  DTO_FIELD(Float32, price);
  DTO_FIELD(String, itemName);
  DTO_FIELD(String, receiptID);
};

class ReceiptItemsToPayDto : public oatpp::DTO {
  DTO_INIT(ReceiptItemsToPayDto, DTO);

  DTO_FIELD(Boolean, success);
  DTO_FIELD(Fields<List<Object<ReceiptItemToPayDto>>>, data);
};

class ReceiptItemPaidDto : public oatpp::DTO {
  DTO_INIT(ReceiptItemPaidDto, DTO);

  DTO_FIELD(String, receiptID);
  DTO_FIELD(String, itemName);
};

class ReceiptResponseItemPaidDto : public oatpp::DTO {
  DTO_INIT(ReceiptResponseItemPaidDto, DTO);

  DTO_FIELD(Boolean, success);
};

class ReceiptFriendsDto : public oatpp::DTO {
 public:
  DTO_INIT(ReceiptFriendsDto, DTO)

  DTO_FIELD(String, userID);
  DTO_FIELD(Float32, price);
};

class ReceiptDto : public oatpp::DTO {
 public:
  DTO_INIT(ReceiptDto, DTO)

  DTO_FIELD(String, receiptName);
  DTO_FIELD(Fields<List<Object<ReceiptItemsDto>>>, data);
};

class getReceiptDto : public oatpp::DTO {
 public:
  DTO_INIT(getReceiptDto, DTO)

  DTO_FIELD(String, receiptID);
};

class getReceiptResponseDto : public oatpp::DTO {
 public:
  DTO_INIT(getReceiptResponseDto, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(String, author);
  DTO_FIELD(String, receiptName);
  DTO_FIELD(String, date);
  DTO_FIELD(Fields<List<Object<ReceiptItemsDto>>>, data);
};

class ReceiptResponseDto : public oatpp::DTO {
  DTO_INIT(ReceiptResponseDto, DTO);

  DTO_FIELD(Boolean, success);
  DTO_FIELD(Fields<List<Object<ReceiptFriendsDto>>>, data);
};

class MergeReceiptsDto : public oatpp::DTO {
    DTO_INIT(MergeReceiptsDto, DTO)

    DTO_FIELD(String, receiptName);
    DTO_FIELD(List<String>, receiptsId);
};

class MergeReceiptsResponseDto : public oatpp::DTO {
  DTO_INIT(MergeReceiptsResponseDto, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(String, receiptName);
};

class UnmergeReceiptsDto : public oatpp::DTO {
    DTO_INIT(UnmergeReceiptsDto, DTO)

    DTO_FIELD(String, receiptId);
};

class UnmergeReceiptResponseDto : public oatpp::DTO{
  DTO_INIT(UnmergeReceiptResponseDto, DTO)

  DTO_FIELD(Boolean, success);
};

class ReceiptsResponseDto : public oatpp::DTO {
  DTO_INIT(ReceiptsResponseDto, DTO);

  DTO_FIELD(Boolean, success);
  DTO_FIELD(Fields<List<Object<ReceiptShortDto>>>, data);
};

}  // namespace api
}  // namespace bakcyl


#include OATPP_CODEGEN_END(DTO)