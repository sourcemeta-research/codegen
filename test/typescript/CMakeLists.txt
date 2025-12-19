sourcemeta_googletest(NAMESPACE sourcemeta PROJECT codegen NAME typescript
  FOLDER "Codegen/TypeScript"
  SOURCES typescript_test.cc)

target_link_libraries(sourcemeta_codegen_typescript_unit
  PRIVATE sourcemeta::codegen::typescript)

sourcemeta_googletest(NAMESPACE sourcemeta PROJECT codegen NAME typescript_e2e
  FOLDER "Codegen/TypeScript"
  SOURCES e2e.cc)

target_link_libraries(sourcemeta_codegen_typescript_e2e_unit
  PRIVATE sourcemeta::codegen::ir)
target_link_libraries(sourcemeta_codegen_typescript_e2e_unit
  PRIVATE sourcemeta::codegen::typescript)
target_compile_definitions(sourcemeta_codegen_typescript_e2e_unit
  PRIVATE TYPESCRIPT_CASES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/cases")
