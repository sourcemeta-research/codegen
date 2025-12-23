#include <gtest/gtest.h>

#include <sourcemeta/codegen/generator.h>

#include <sourcemeta/core/jsonpointer.h>

TEST(Generator_to_pascal_case,
     empty_instance_location_returns_default_namespace) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location;
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "Schema");
}

TEST(Generator_to_pascal_case, empty_instance_location_with_custom_namespace) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location;
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "MyNamespace")};
  EXPECT_EQ(result, "MyNamespace");
}

TEST(Generator_to_pascal_case, single_property_token) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "foo");
}

TEST(Generator_to_pascal_case, multiple_property_tokens) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo", "bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "foo_bar");
}

TEST(Generator_to_pascal_case, three_property_tokens) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo", "bar", "baz"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "foo_bar_baz");
}

TEST(Generator_to_pascal_case, property_with_hyphen) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo-bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "foo-bar");
}

TEST(Generator_to_pascal_case, property_starting_with_number) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"123foo"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "123foo");
}

TEST(Generator_to_pascal_case, property_that_is_only_numbers) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"123"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "123");
}

TEST(Generator_to_pascal_case, property_with_underscore) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo_bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "foo_bar");
}

TEST(Generator_to_pascal_case, property_with_spaces) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "foo bar");
}

TEST(Generator_to_pascal_case, property_with_special_characters) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"foo@bar"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "foo@bar");
}

TEST(Generator_to_pascal_case, empty_property_name) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{""}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "");
}

TEST(Generator_to_pascal_case, deeply_nested_path) {
  const sourcemeta::core::Pointer pointer;
  const sourcemeta::core::PointerTemplate instance_location{
      sourcemeta::core::Pointer{"a", "b", "c", "d", "e"}};
  const auto result{sourcemeta::codegen::to_pascal_case(
      pointer, instance_location, "Schema")};
  EXPECT_EQ(result, "a_b_c_d_e");
}
