#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class BalanceDto : public oatpp::DTO {
 public:
  DTO_INIT(BalanceDto, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(Float64, balance);    // Add this line
};

class ChangeBalanceDto : public oatpp::DTO{
 public:
  DTO_INIT(ChangeBalanceDto, DTO)

  DTO_FIELD(Float64, amount);
  
};

class ChangeBalanceResponseDto : public oatpp::DTO{
  DTO_INIT(ChangeBalanceResponseDto, DTO);

  DTO_FIELD(Boolean, success);
};

#include OATPP_CODEGEN_END(DTO)