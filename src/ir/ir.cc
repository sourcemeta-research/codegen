#include <sourcemeta/codegen/ir.h>

#include <sourcemeta/core/alterschema.h>

#include <algorithm>  // std::ranges::sort
#include <functional> // std::reference_wrapper
#include <map>        // std::map
#include <vector>     // std::vector

namespace sourcemeta::codegen {

struct InstanceLocationEntry {
  std::reference_wrapper<const sourcemeta::core::PointerTemplate>
      instance_location;
  std::reference_wrapper<const sourcemeta::core::SchemaFrame::Location>
      location;
};

using InstanceLocationMap = std::map<sourcemeta::core::PointerTemplate,
                                     std::vector<InstanceLocationEntry>>;

static auto group(const sourcemeta::core::SchemaFrame &frame)
    -> InstanceLocationMap {
  InstanceLocationMap trivial;
  InstanceLocationMap non_trivial;

  for (const auto &[key, location] : frame.locations()) {
    if (location.type ==
            sourcemeta::core::SchemaFrame::LocationType::Resource ||
        location.type ==
            sourcemeta::core::SchemaFrame::LocationType::Subschema) {
      for (const auto &instance_location : frame.instance_locations(location)) {
        auto &target{instance_location.trivial() ? trivial : non_trivial};
        target[instance_location].emplace_back(InstanceLocationEntry{
            .instance_location = instance_location, .location = location});
      }
    }
  }

  for (const auto &[non_trivial_location, entries] : non_trivial) {
    auto matched{false};
    for (auto &[trivial_location, trivial_entries] : trivial) {
      if (non_trivial_location.matches(trivial_location)) {
        for (const auto &entry : entries) {
          trivial_entries.emplace_back(entry);
        }

        matched = true;
      }
    }

    if (!matched) {
      trivial[non_trivial_location] = entries;
    }
  }

  return trivial;
}

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
                        sourcemeta::core::AlterSchemaMode::StaticAnalysis);
  canonicalizer.apply(
      schema, walker, resolver,
      [](const auto &, const auto, const auto, const auto &) {});

  // --------------------------------------------------------------------------
  // (3) Frame the resulting schema with instance location information
  // --------------------------------------------------------------------------

  sourcemeta::core::SchemaFrame frame{
      sourcemeta::core::SchemaFrame::Mode::Instances};
  frame.analyse(schema, walker, resolver);

  const auto instance_to_locations{group(frame)};

  IRResult result;

  // Process each instance location group
  for (const auto &[instance_location, entries] : instance_to_locations) {
    for (const auto &entry : entries) {
      const auto &subschema{
          sourcemeta::core::get(schema, entry.location.get().pointer)};
      if (!subschema.is_object()) {
        continue;
      }

      const auto vocabularies{
          frame.vocabularies(entry.location.get(), resolver)};

      if (subschema.defines("type")) {
        const auto &type_result{walker("type", vocabularies)};
        if (type_result.type !=
            sourcemeta::core::SchemaKeywordType::Assertion) {
          continue;
        }

        const auto &type_value{subschema.at("type")};
        if (!type_value.is_string()) {
          continue;
        }

        const auto &type_string{type_value.to_string()};

        if (type_string == "string") {
          result.emplace_back(IRScalar{.pointer = instance_location,
                                       .value = IRScalarType::String});
        } else if (type_string == "object") {
          IRObject object;
          object.pointer = instance_location;

          // Find child instance locations (one property token deeper)
          for (const auto &[child_instance, child_locations] :
               instance_to_locations) {
            if (!child_instance.trivial() || child_instance.empty()) {
              continue;
            }

            // Check if child is exactly one property token deeper
            auto child_size{
                std::distance(child_instance.begin(), child_instance.end())};
            auto parent_size{std::distance(instance_location.begin(),
                                           instance_location.end())};
            if (child_size != parent_size + 1) {
              continue;
            }

            // Verify parent prefix matches
            auto matches{true};
            auto child_iter{child_instance.begin()};
            for (const auto &parent_token : instance_location) {
              if (*child_iter != parent_token) {
                matches = false;
                break;
              }
              ++child_iter;
            }

            if (!matches) {
              continue;
            }

            // Get the property name from the last token
            const auto &last_token{*child_instance.rbegin()};
            if (!std::holds_alternative<sourcemeta::core::Pointer::Token>(
                    last_token)) {
              continue;
            }

            const auto &property_token{
                std::get<sourcemeta::core::Pointer::Token>(last_token)};
            if (!property_token.is_property()) {
              continue;
            }

            object.members.emplace(property_token.to_property(),
                                   IRObjectValue{.required = false,
                                                 .immutable = false,
                                                 .pointer = child_instance});
          }

          result.emplace_back(std::move(object));
        }
      }
    }
  }

  // Sort by pointer template (longer paths come first, so dependencies
  // appear before their parents)
  const auto get_pointer{
      [](const auto &entry) -> const sourcemeta::core::PointerTemplate & {
        return entry.pointer;
      }};
  std::ranges::sort(
      result, [&get_pointer](const IREntity &a, const IREntity &b) -> bool {
        return std::visit(get_pointer, b) < std::visit(get_pointer, a);
      });

  return result;
}

} // namespace sourcemeta::codegen
