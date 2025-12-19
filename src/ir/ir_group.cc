#include <sourcemeta/codegen/ir_group.h>

namespace sourcemeta::codegen {

auto group(const sourcemeta::core::SchemaFrame &frame) -> IRGroup {
  IRGroup trivial;
  IRGroup non_trivial;

  for (const auto &[key, location] : frame.locations()) {
    if (location.type ==
            sourcemeta::core::SchemaFrame::LocationType::Resource ||
        location.type ==
            sourcemeta::core::SchemaFrame::LocationType::Subschema) {
      for (const auto &instance_location : frame.instance_locations(location)) {
        auto &target{instance_location.trivial() ? trivial : non_trivial};
        target[instance_location].emplace_back(IRGroupEntry{
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

} // namespace sourcemeta::codegen
