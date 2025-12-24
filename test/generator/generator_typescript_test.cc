#include <gtest/gtest.h>

#include <sourcemeta/codegen/generator.h>

#include <sstream> // std::ostringstream

TEST(Generator_typescript, test_1) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRScalar{{}, IRScalarType::String});

  std::ostringstream output;
  typescript(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = string;\n");
}

TEST(Generator_typescript, test_2) {
  using namespace sourcemeta::codegen;

  IRResult result;

  result.emplace_back(IRScalar{
      {{}, sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"foo"}}},
      IRScalarType::String});

  IRObject object;
  object.instance_location = {};
  object.members.emplace("foo",
                         IRObjectValue{{{},
                                        sourcemeta::core::PointerTemplate{
                                            sourcemeta::core::Pointer{"foo"}}},
                                       false,
                                       false});
  result.emplace_back(std::move(object));

  std::ostringstream output;
  typescript(output, result, "MyObject");

  const auto expected{R"TS(export type MyObject_Foo = string;

export interface MyObject {
  foo?: MyObject_Foo;
}
)TS"};

  EXPECT_EQ(output.str(), expected);
}

TEST(Generator_typescript, impossible_at_root) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRImpossible{{}});

  std::ostringstream output;
  typescript(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType = never;\n");
}

TEST(Generator_typescript, impossible_nested) {
  using namespace sourcemeta::codegen;

  IRResult result;
  result.emplace_back(IRImpossible{
      {sourcemeta::core::Pointer{"foo"},
       sourcemeta::core::PointerTemplate{sourcemeta::core::Pointer{"foo"}}}});

  std::ostringstream output;
  typescript(output, result, "MyType");

  EXPECT_EQ(output.str(), "export type MyType_Foo = never;\n");
}
