set(core_SRCS main.cpp)
add_library(core ${core_SRCS})
add_executable(main main.cpp lab3.cpp constructors.cpp lab3.h)

target_link_libraries(main core)
