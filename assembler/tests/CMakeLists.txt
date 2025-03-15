include_directories(../)
add_executable(TASM_EXE test.cpp)
target_link_libraries(TASM_EXE prasm)
add_test(TEST_TASM TASM_EXE)