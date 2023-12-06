#include <gmock/gmock.h>
#include "api/Api.hpp"

using namespace ::testing;

TEST(ApiWorking, CheckIfCodeWillCompile)
{
    const int expectedValue{13};
    paragon::Api api{expectedValue};
    EXPECT_THAT(api.get(), Eq(expectedValue));
}
