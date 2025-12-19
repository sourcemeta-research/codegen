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
  PRIVATE TYPESCRIPT_E2E_PATH="${CMAKE_CURRENT_SOURCE_DIR}/e2e")

file(GLOB TYPESCRIPT_CASE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/e2e/*")
foreach(CASE_DIRECTORY ${TYPESCRIPT_CASE_DIRECTORIES})
  if(IS_DIRECTORY ${CASE_DIRECTORY})
    get_filename_component(CASE_NAME ${CASE_DIRECTORY} NAME)
    add_test(NAME "tsc.${CASE_NAME}/expected.d.ts"
      COMMAND "${PROJECT_SOURCE_DIR}/node_modules/.bin/tsc" --noEmit
        "${CASE_DIRECTORY}/expected.d.ts")
  endif()
endforeach()
