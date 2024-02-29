#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class ReciptItemsDto : public oatpp::DTO {
 public:
  DTO_INIT(ReciptItemsDto, DTO)

  DTO_FIELD(String, whoBuy);
  DTO_FIELD(String, item);
  DTO_FIELD(Int32, price);
  DTO_FIELD(Int32, amount);
};

class ReciptDto : public oatpp::DTO{
 public:
  DTO_INIT(ReciptDto, DTO)

  DTO_FIELD(String, reciptName);
  DTO_FIELD(Fields<List<Object<ReciptItemsDto>>>, data);
  
};

class ReciptResponseDto : public oatpp::DTO{
  DTO_INIT(ReciptResponseDto, DTO);

  DTO_FIELD(Boolean, success);
};

#include OATPP_CODEGEN_END(DTO)