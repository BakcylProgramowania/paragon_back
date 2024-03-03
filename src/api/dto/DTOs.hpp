#pragma once

#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

namespace bakcyl {
namespace api {

class MyDto : public oatpp::DTO {
 public:
  DTO_INIT(MyDto, DTO)

  DTO_FIELD(Int32, statusCode);  // Add this line
  DTO_FIELD(String, message);    // Add this line
};

}
}

#include OATPP_CODEGEN_END(DTO)

