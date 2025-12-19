#include <sourcemeta/codegen/typescript.h>

#include <stdexcept> // std::runtime_error
#include <variant>   // std::visit

namespace sourcemeta::codegen {

static auto pointer_to_name(const sourcemeta::core::PointerTemplate &pointer,
                            const std::optional<std::string> &default_namespace)
    -> std::string {
  if (pointer.empty()) {
    if (!default_namespace.has_value()) {
      throw std::runtime_error(
          "Empty pointer without default namespace provided");
    }
    return default_namespace.value();
  }

  std::string result;
  for (const auto &token : pointer) {
    if (!result.empty()) {
      result += "_";
    }
    const auto &property_token{
        std::get<sourcemeta::core::Pointer::Token>(token)};
    result += property_token.to_property();
  }
  return result;
}

static auto scalar_type_to_typescript(IRScalarType type) -> std::string {
  switch (type) {
    case IRScalarType::String:
      return "string";
    default:
      return "unknown";
  }
}

auto typescript(std::ostream &output, const IRResult &result,
                const std::optional<std::string> &default_namespace) -> void {
  for (const auto &entity : result) {
    std::visit(
        [&output, &default_namespace](const auto &entry) {
          using T = std::decay_t<decltype(entry)>;
          const auto name{pointer_to_name(entry.pointer, default_namespace)};

          if constexpr (std::is_same_v<T, IRScalar>) {
            output << "export type " << name << " = "
                   << scalar_type_to_typescript(entry.value) << ";\n";
          } else if constexpr (std::is_same_v<T, IRObject>) {
            output << "export interface " << name << " {\n";
            for (const auto &[member_name, member_value] : entry.members) {
              const auto optional_marker{member_value.required ? "" : "?"};
              const auto readonly_marker{member_value.immutable ? "readonly "
                                                                : ""};
              const auto member_type_name{
                  pointer_to_name(member_value.pointer, default_namespace)};
              output << "  " << readonly_marker << member_name
                     << optional_marker << ": " << member_type_name << ";\n";
            }
            output << "}\n";
          }
        },
        entity);
  }
}

} // namespace sourcemeta::codegen
