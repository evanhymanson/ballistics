add_library(pnav
            pnav_2d.cpp)

target_include_directories(pnav PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Test executable for pnav (proportional navigation) functions
add_executable(test tests.cpp)
target_link_libraries(test PRIVATE pnav)