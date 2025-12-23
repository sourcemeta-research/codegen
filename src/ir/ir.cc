#include <sourcemeta/codegen/ir.h>
#include <sourcemeta/core/alterschema.h>

#include <algorithm>     // std::ranges::sort
#include <cassert>       // assert
#include <unordered_set> // std::unordered_set

#include "ir_handlers.h"

namespace sourcemeta::codegen {

namespace {

auto handle_schema(const sourcemeta::core::JSON &schema,
                   const sourcemeta::core::Vocabularies &vocabularies,
                   const sourcemeta::core::JSON &subschema,
                   const sourcemeta::core::Pointer &pointer,
                   const sourcemeta::core::PointerTemplate &instance_location)
    -> IREntity {
  // The canonicaliser ensures that every subschema schema is only in one of the
  // following shapes

  if (subschema.defines("type")) {
    const auto &type_value{subschema.at("type")};
    if (!type_value.is_string()) {
      throw UnsupportedKeywordValue(schema, pointer, "type",
                                    "Expected a string value");
    }

    const auto &type_string{type_value.to_string()};

    // The canonicaliser transforms any other type
    if (type_string == "string") {
      return handle_string(schema, vocabularies, pointer, instance_location);
    } else if (type_string == "object") {
      return handle_object(schema, vocabularies, subschema, pointer,
                           instance_location);
    } else if (type_string == "integer") {
      return handle_integer(schema, vocabularies, subschema, pointer,
                            instance_location);
    } else if (type_string == "number") {
      return handle_number(schema, vocabularies, subschema, pointer,
                           instance_location);
    } else if (type_string == "array") {
      return handle_array(schema, vocabularies, subschema, pointer,
                          instance_location);
    } else {
      throw UnsupportedKeywordValue(schema, pointer, "type",
                                    "Unsupported type value");
    }
  } else if (subschema.defines("enum")) {
    return handle_enum(schema, vocabularies, subschema, pointer,
                       instance_location);
  } else if (subschema.defines("anyOf")) {
    return handle_anyof(schema, vocabularies, subschema, pointer,
                        instance_location);
    // Only the recursive case
  } else if (subschema.defines("$ref")) {
    return handle_ref(schema, vocabularies, subschema, pointer,
                      instance_location);
  } else {
    throw UnexpectedSchema(schema, pointer, "Unsupported subschema");
  }
}

} // namespace

auto compile(
    const sourcemeta::core::JSON &input,
    const sourcemeta::core::SchemaWalker &walker,
    const sourcemeta::core::SchemaResolver &resolver,
    const std::optional<sourcemeta::core::JSON::String> &default_dialect,
    const std::optional<sourcemeta::core::JSON::String> &default_id)
    -> IRResult {
  // --------------------------------------------------------------------------
  // (1) Bundle the schema to resolve external references
  // --------------------------------------------------------------------------

  auto schema{sourcemeta::core::bundle(input, walker, resolver, default_dialect,
                                       default_id)};

  // --------------------------------------------------------------------------
  // (2) Canonicalize the schema for easier analysis
  // --------------------------------------------------------------------------

  sourcemeta::core::SchemaTransformer canonicalizer;
  sourcemeta::core::add(canonicalizer,
                        sourcemeta::core::AlterSchemaMode::Canonicalizer);
  const auto canonicalized{canonicalizer.apply(
      schema, walker, resolver,
      [](const auto &, const auto, const auto, const auto &) {})};
  // Canonicalization should only consists of transformable rules, so this would
  // never be false and the callback would never be called
  assert(canonicalized.first);

  // --------------------------------------------------------------------------
  // (3) Frame the resulting schema with instance location information
  // --------------------------------------------------------------------------

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Instances};
  frame.analyse(schema, walker, resolver);

  // --------------------------------------------------------------------------
  // (4) Convert every subschema into a code generation object
  // --------------------------------------------------------------------------

  IRResult result;
  for (const auto &[key, location] : frame.locations()) {
    if (location.type !=
            sourcemeta::core::SchemaFrame::LocationType::Resource &&
        location.type !=
            sourcemeta::core::SchemaFrame::LocationType::Subschema) {
      continue;
    }

    const auto &subschema{sourcemeta::core::get(schema, location.pointer)};

    // Canonicalisation ensures subschemas are objects or the `false` subschema,
    // in the latter case, we will deal with it in the corresponding containers
    if (!subschema.is_object()) {
      assert(subschema.is_boolean());
      assert(!subschema.to_boolean());
      continue;
    }

    const auto &instance_locations{frame.instance_locations(location)};
    // Canonicalisation is expected to take care of this
    assert(!instance_locations.empty());
    const auto vocabularies{frame.vocabularies(location, resolver)};
    assert(!vocabularies.empty());

    // Be strict with vocabulary support
    using Known = sourcemeta::core::Vocabularies::Known;
    static std::unordered_set<sourcemeta::core::Vocabularies::URI>
        SUPPORTED_VOCABULARIES{Known::JSON_Schema_2020_12_Core,
                               Known::JSON_Schema_2020_12_Applicator,
                               Known::JSON_Schema_2020_12_Unevaluated,
                               Known::JSON_Schema_2020_12_Validation,
                               Known::JSON_Schema_2020_12_Meta_Data,
                               Known::JSON_Schema_2020_12_Format_Annotation,
                               Known::JSON_Schema_2020_12_Format_Assertion,
                               Known::JSON_Schema_2020_12_Content,
                               Known::JSON_Schema_2019_09_Core,
                               Known::JSON_Schema_2019_09_Applicator,
                               Known::JSON_Schema_2019_09_Validation,
                               Known::JSON_Schema_2019_09_Meta_Data,
                               Known::JSON_Schema_2019_09_Format,
                               Known::JSON_Schema_2019_09_Content,
                               Known::JSON_Schema_2019_09_Hyper_Schema,
                               Known::JSON_Schema_Draft_7,
                               Known::JSON_Schema_Draft_7_Hyper,
                               Known::JSON_Schema_Draft_6,
                               Known::JSON_Schema_Draft_6_Hyper,
                               Known::JSON_Schema_Draft_4,
                               Known::JSON_Schema_Draft_4_Hyper,
                               Known::OpenAPI_3_1_Base,
                               Known::OpenAPI_3_2_Base};
    vocabularies.throw_if_any_unsupported(
        SUPPORTED_VOCABULARIES, "Cannot analyse unsupported vocabulary");

    result.push_back(handle_schema(schema, vocabularies, subschema,
                                   location.pointer,
                                   instance_locations.front()));
  }

  // --------------------------------------------------------------------------
  // (6) Sort entries so that dependencies come before dependents
  // --------------------------------------------------------------------------

  std::ranges::sort(
      result, [](const IREntity &left, const IREntity &right) -> bool {
        return std::visit(
                   [](const auto &entry) { return entry.instance_location; },
                   right) <
               std::visit(
                   [](const auto &entry) { return entry.instance_location; },
                   left);
      });

  return result;
}

} // namespace sourcemeta::codegen
