cmake_minimum_required(VERSION 3.0)
project(EpidemicModelling)

add_executable(main main.c sir.c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=address")
target_compile_options(main PRIVATE -g)
target_link_libraries(main PRIVATE m)