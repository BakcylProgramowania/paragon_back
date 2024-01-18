#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

namespace bakcyl {
namespace api {

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class MyDto : public oatpp::DTO {
 public:
  DTO_INIT(MyDto, DTO)

  DTO_FIELD(Int32, statusCode);  // Add this line
  DTO_FIELD(String, message);    // Add this line
};

#include OATPP_CODEGEN_END(DTO)

}  // namespace api
}  // namespace bakcyl
