#include "mocks/invoke.hpp"
#include <siplasplas/typeerasure/function.hpp>
#include <gmock/gmock.h>

using namespace ::testing;
using namespace ::cpp::typeerasure;
using namespace ::std::string_literals;


TEST(FunctionTest, Function8_freeFunctionIntsByValue)
{
    EXPECT_EQ(42, Function8(addIntsByValue)(20, 22).get<int>());
}

TEST(FunctionTest, Function32_freeFunctionStringsByConstReference)
{
    EXPECT_EQ("hello, world!", Function32(addStringsByConstReference)("hello, "s, "world!"s).get<std::string>());
}

TEST(FunctionTest, Function16_memberFunctionIntsByValue)
{
    EXPECT_EQ(42, Function16(&Class::addIntsByValue)(Class(), 20, 22).get<int>());
}

TEST(FunctionTest, Function32_memberFunctionStringsByConstReference)
{
    EXPECT_EQ("hello, world!", Function32(&Class::addStringsByConstReference)(Class(), "hello, "s, "world!"s).get<std::string>());
}

TEST(FunctionTest, Function16_constMemberFunctionIntsByValue)
{
    EXPECT_EQ(42, Function16(&Class::addIntsByValueConst)(Class(), 20, 22).get<int>());
}

TEST(FunctionTest, Function32_constMemberFunctionStringsByConstReference)
{
    EXPECT_EQ("hello, world!", Function32(&Class::addStringsByConstReferenceConst)(Class(), "hello, "s, "world!"s).get<std::string>());
}
