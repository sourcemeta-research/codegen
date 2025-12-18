sourcemeta_googletest(NAMESPACE sourcemeta PROJECT codegen NAME typescript
  FOLDER "Codegen/TypeScript"
  SOURCES typescript_test.cc)

target_link_libraries(sourcemeta_codegen_typescript_unit
  PRIVATE sourcemeta::codegen::typescript)
