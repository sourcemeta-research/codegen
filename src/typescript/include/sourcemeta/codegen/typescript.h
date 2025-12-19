#ifndef SOURCEMETA_CODEGEN_TYPESCRIPT_H_
#define SOURCEMETA_CODEGEN_TYPESCRIPT_H_

#ifndef SOURCEMETA_CODEGEN_TYPESCRIPT_EXPORT
#include <sourcemeta/codegen/typescript_export.h>
#endif

#include <sourcemeta/codegen/ir.h>

#include <optional> // std::optional, std::nullopt
#include <ostream>  // std::ostream
#include <string>   // std::string

/// @defgroup typescript TypeScript
/// @brief The codegen JSON Schema TypeScript support package

namespace sourcemeta::codegen {

/// @ingroup typescript
SOURCEMETA_CODEGEN_TYPESCRIPT_EXPORT
auto typescript(
    std::ostream &output, const IRResult &result,
    const std::optional<std::string> &default_namespace = std::nullopt) -> void;

} // namespace sourcemeta::codegen

#endif
