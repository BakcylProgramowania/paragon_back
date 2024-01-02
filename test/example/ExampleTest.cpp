#include <gmock/gmock.h>
#include "example/Example.hpp"

using namespace ::testing;

TEST(SomeTest, GetShouldReturnConstructionArgument)
{
    const int expectedValue{14};
    paragon::Example example{expectedValue};
    EXPECT_THAT(example.get(), Eq(expectedValue));
}
