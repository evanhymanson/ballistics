# Propogation library
add_library(prop
            propagate_euler.cpp
            propagate_rk.cpp)

target_include_directories(prop PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test executable for prop functions
add_executable(prop_test tests.cpp)
target_link_libraries(prop_test PRIVATE prop)