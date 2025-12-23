#include <sourcemeta/codegen/generator.h>

#include <cassert> // assert
#include <cctype>  // std::isalpha, std::isdigit, std::toupper
#include <iomanip> // std::setfill, std::setw
#include <sstream> // std::ostringstream

namespace sourcemeta::codegen {

static auto string_to_pascal_case(const std::string &input) -> std::string {
  std::ostringstream result;
  bool capitalize_next{true};
  for (const char character : input) {
    if (std::isalpha(static_cast<unsigned char>(character)) != 0) {
      if (capitalize_next) {
        result << static_cast<char>(
            std::toupper(static_cast<unsigned char>(character)));
        capitalize_next = false;
      } else {
        result << character;
      }
    } else if (std::isdigit(static_cast<unsigned char>(character)) != 0) {
      result << character;
    } else {
      result << 'X' << std::uppercase << std::hex << std::setfill('0')
             << std::setw(2)
             << static_cast<unsigned int>(
                    static_cast<unsigned char>(character));
      capitalize_next = true;
    }
  }
  return result.str();
}

auto to_pascal_case(const sourcemeta::core::PointerTemplate &instance_location,
                    const std::string &default_namespace) -> std::string {
  assert(!default_namespace.empty());
  std::string result{string_to_pascal_case(default_namespace)};

  if (instance_location.empty()) {
    return result;
  }

  for (const auto &token : instance_location) {
    if (const auto *property_token =
            std::get_if<sourcemeta::core::Pointer::Token>(&token)) {
      const auto &property{property_token->to_property()};
      std::string token_pascal{string_to_pascal_case(property)};
      if (!token_pascal.empty()) {
        result += token_pascal;
      }
    } else if (const auto *wildcard =
                   std::get_if<sourcemeta::core::PointerTemplate::Wildcard>(
                       &token)) {
      switch (*wildcard) {
        case sourcemeta::core::PointerTemplate::Wildcard::Property:
          result += "AnyProperty";
          break;
        case sourcemeta::core::PointerTemplate::Wildcard::Item:
          result += "AnyItem";
          break;
        case sourcemeta::core::PointerTemplate::Wildcard::Key:
          result += "AnyKey";
          break;
      }
    } else if (const auto *condition =
                   std::get_if<sourcemeta::core::PointerTemplate::Condition>(
                       &token)) {
      result += "Maybe";
      if (condition->suffix.has_value()) {
        result += string_to_pascal_case(condition->suffix.value());
      }
    } else if (std::holds_alternative<
                   sourcemeta::core::PointerTemplate::Negation>(token)) {
      result += "Not";
    } else if (const auto *regex =
                   std::get_if<sourcemeta::core::PointerTemplate::Regex>(
                       &token)) {
      result += "Regex";
      result += string_to_pascal_case(*regex);
    }
  }

  return result;
}

} // namespace sourcemeta::codegen
