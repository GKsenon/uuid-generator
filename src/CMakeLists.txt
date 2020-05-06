add_library(${PROJECT_NAME}
    uuid_generator.c
    random_number_generator.c)
target_link_libraries(${PROJECT_NAME} BCrypt)
target_include_directories(${PROJECT_NAME} PUBLIC include)

add_executable(uuid_generator_test
    uuid_generator_test.c)
target_link_libraries(uuid_generator_test
    ${PROJECT_NAME})
add_test(uuid_generator_test
    uuid_generator_test)
