#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace bakcyl {
namespace api {

class BalanceDto : public oatpp::DTO {
 public:
  DTO_INIT(BalanceDto, DTO)

  DTO_FIELD(Boolean, success);
  DTO_FIELD(Float64, balance);
};

class ChangeBalanceDto : public oatpp::DTO {
 public:
  DTO_INIT(ChangeBalanceDto, DTO)

  DTO_FIELD(Float64, amount);
};

class ChangeBalanceResponseDto : public oatpp::DTO {
  DTO_INIT(ChangeBalanceResponseDto, DTO);

  DTO_FIELD(Boolean, success);
};

}  // namespace api
}  // namespace bakcyl

#include OATPP_CODEGEN_END(DTO)