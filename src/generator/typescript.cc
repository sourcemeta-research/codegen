#include <sourcemeta/codegen/generator.h>

#include <sstream> // std::ostringstream

namespace {

// TODO: Move to Core
auto escape_string(const std::string &input) -> std::string {
  std::ostringstream result;
  for (const auto character : input) {
    switch (character) {
      case '\\':
        result << "\\\\";
        break;
      case '"':
        result << "\\\"";
        break;
      case '\n':
        result << "\\n";
        break;
      case '\r':
        result << "\\r";
        break;
      case '\t':
        result << "\\t";
        break;
      default:
        result << character;
        break;
    }
  }

  return result.str();
}

} // namespace

namespace sourcemeta::codegen {

TypeScript::TypeScript(std::ostream &stream, const std::string &type_prefix)
    : output{stream}, prefix{type_prefix} {}

auto TypeScript::operator()(const IRScalar &entry) const -> void {
  this->output << "export type "
               << to_pascal_case(entry.instance_location, this->prefix)
               << " = ";

  switch (entry.value) {
    case IRScalarType::String:
      this->output << "string";
      break;
    case IRScalarType::Number:
    case IRScalarType::Integer:
      this->output << "number";
      break;
    case IRScalarType::Boolean:
      this->output << "boolean";
      break;
    case IRScalarType::Null:
      this->output << "null";
      break;
  }

  this->output << ";\n";
}

auto TypeScript::operator()(const IREnumeration &entry) const -> void {
  this->output << "export type "
               << to_pascal_case(entry.instance_location, this->prefix)
               << " = ";

  const char *separator{""};
  for (const auto &value : entry.values) {
    this->output << separator;
    sourcemeta::core::prettify(value, this->output);
    separator = " | ";
  }

  this->output << ";\n";
}

auto TypeScript::operator()(const IRObject &entry) const -> void {
  this->output << "export interface "
               << to_pascal_case(entry.instance_location, this->prefix)
               << " {\n";
  for (const auto &[member_name, member_value] : entry.members) {
    const auto optional_marker{member_value.required ? "" : "?"};
    const auto readonly_marker{member_value.immutable ? "readonly " : ""};
    // We always quote property names for safety. JSON Schema allows any string
    // as a property name, but unquoted TypeScript/ECMAScript property names
    // must be valid IdentifierName productions (see ECMA-262 section 12.7).
    // Quoting allows any string to be used as a property name.
    // See: https://tc39.es/ecma262/#sec-names-and-keywords
    // See: https://mathiasbynens.be/notes/javascript-properties
    this->output << "  " << readonly_marker << "\""
                 << escape_string(member_name) << "\"" << optional_marker
                 << ": "
                 << to_pascal_case(member_value.instance_location, this->prefix)
                 << ";\n";
  }

  this->output << "}\n";
}

auto TypeScript::operator()(const IRImpossible &entry) const -> void {
  this->output << "export type "
               << to_pascal_case(entry.instance_location, this->prefix)
               << " = never;\n";
}

auto TypeScript::operator()(const IRArray &entry) const -> void {
  this->output << "export type "
               << to_pascal_case(entry.instance_location, this->prefix) << " = "
               << to_pascal_case(entry.items.instance_location, this->prefix)
               << "[];\n";
}

auto TypeScript::operator()(const IRReference &entry) const -> void {
  this->output << "export type "
               << to_pascal_case(entry.instance_location, this->prefix) << " = "
               << to_pascal_case(entry.target.instance_location, this->prefix)
               << ";\n";
}

auto TypeScript::operator()(const IRTuple &entry) const -> void {
  this->output << "export type "
               << to_pascal_case(entry.instance_location, this->prefix)
               << " = [";

  const char *separator{""};
  for (const auto &item : entry.items) {
    this->output << separator
                 << to_pascal_case(item.instance_location, this->prefix);
    separator = ", ";
  }

  if (entry.additional.has_value()) {
    this->output << separator << "..."
                 << to_pascal_case(entry.additional->instance_location,
                                   this->prefix)
                 << "[]";
  }

  this->output << "];\n";
}

auto TypeScript::operator()(const IRUnion &entry) const -> void {
  this->output << "export type "
               << to_pascal_case(entry.instance_location, this->prefix)
               << " = ";

  const char *separator{""};
  for (const auto &value : entry.values) {
    this->output << separator
                 << to_pascal_case(value.instance_location, this->prefix);
    separator = " | ";
  }

  this->output << ";\n";
}

} // namespace sourcemeta::codegen
