#include <gtest/gtest.h>

#include <sourcemeta/codegen/ir.h>
#include <sourcemeta/codegen/typescript.h>

#include <sourcemeta/core/json.h>
#include <sourcemeta/core/jsonschema.h>

#include <filesystem> // std::filesystem
#include <fstream>    // std::ifstream
#include <optional>   // std::optional, std::nullopt
#include <sstream>    // std::ostringstream
#include <string>     // std::string

class TypeScriptE2ETest : public testing::Test {
public:
  explicit TypeScriptE2ETest(const std::filesystem::path &test_directory)
      : directory{test_directory} {}

  auto TestBody() -> void override {
    const auto schema_path{this->directory / "schema.json"};
    const auto options_path{this->directory / "options.json"};
    const auto expected_path{this->directory / "expected.d.ts"};

    std::ifstream schema_stream{schema_path};
    schema_stream.exceptions(std::ios_base::badbit);
    const auto schema{sourcemeta::core::parse_json(schema_stream)};

    std::ifstream options_stream{options_path};
    options_stream.exceptions(std::ios_base::badbit);
    const auto options{sourcemeta::core::parse_json(options_stream)};

    std::ifstream expected_stream{expected_path};
    expected_stream.exceptions(std::ios_base::badbit);
    const std::string expected{std::istreambuf_iterator<char>(expected_stream),
                               std::istreambuf_iterator<char>()};

    std::optional<std::string> default_namespace{std::nullopt};
    if (options.defines("defaultNamespace")) {
      default_namespace = options.at("defaultNamespace").to_string();
    }

    const auto result{
        sourcemeta::codegen::compile(schema, sourcemeta::core::schema_walker,
                                     sourcemeta::core::schema_resolver)};

    std::ostringstream output;
    sourcemeta::codegen::typescript(output, result, default_namespace);

    EXPECT_EQ(output.str(), expected)
        << "Generated TypeScript does not match expected output";
  }

private:
  const std::filesystem::path directory;
};

auto main(int argc, char **argv) -> int {
  testing::InitGoogleTest(&argc, argv);

  const std::filesystem::path cases_path{TYPESCRIPT_CASES_PATH};
  for (const auto &entry : std::filesystem::directory_iterator(cases_path)) {
    if (!entry.is_directory()) {
      continue;
    }

    const auto test_name{entry.path().filename().string()};
    testing::RegisterTest("TypeScriptE2E", test_name.c_str(), nullptr, nullptr,
                          __FILE__, __LINE__, [=]() -> TypeScriptE2ETest * {
                            return new TypeScriptE2ETest(entry.path());
                          });
  }

  return RUN_ALL_TESTS();
}
