sourcemeta_library(NAMESPACE sourcemeta PROJECT codegen NAME ir
  FOLDER "Codegen/IR"
  PRIVATE_HEADERS group.h
  SOURCES ir.cc ir_group.cc)

if(CODEGEN_INSTALL)
  sourcemeta_library_install(NAMESPACE sourcemeta PROJECT codegen NAME ir)
endif()

target_link_libraries(sourcemeta_codegen_ir PUBLIC
  sourcemeta::core::json)
target_link_libraries(sourcemeta_codegen_ir PUBLIC
  sourcemeta::core::jsonschema)
target_link_libraries(sourcemeta_codegen_ir PRIVATE
  sourcemeta::core::alterschema)
