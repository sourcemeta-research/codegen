sourcemeta_library(NAMESPACE sourcemeta PROJECT codegen NAME typescript
  FOLDER "Codegen/TypeScript"
  SOURCES typescript.cc)

if(CODEGEN_INSTALL)
  sourcemeta_library_install(NAMESPACE sourcemeta PROJECT codegen NAME typescript)
endif()

target_link_libraries(sourcemeta_codegen_typescript PUBLIC sourcemeta::codegen::ir)
