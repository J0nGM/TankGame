add_executable(test_tank test_tank.cpp)

target_link_libraries(test_tank PRIVATE threepp::threepp Catch2::Catch2WithMain)
target_include_directories(test_tank PRIVATE "${CMAKE_SOURCE_DIR}/include")
add_test(NAME test_tank COMMAND test_tank)
