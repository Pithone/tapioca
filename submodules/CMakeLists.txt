set(JSON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/json/src PARENT_SCOPE)
set(TOML_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/toml11 PARENT_SCOPE)
set(RGB_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/rpi-rgb-led-matrix/include PARENT_SCOPE)
set(RGB_LIB_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/rpi-rgb-led-matrix/lib PARENT_SCOPE)

# Don't build external libraries tests
set(JSON_BuildTests OFF CACHE INTERNAL "")
set(BUILD_CPR_TESTS OFF CACHE BOOL "Don't build cpr tests")

# Do not install json library to system
set(JSON_Install OFF CACHE INTERNAL "")

find_package(CURL)
if(CURL_FOUND)
    set(USE_SYSTEM_CURL ON CACHE BOOL "Use the system curl for faster builds")
endif()
add_subdirectory(cpr)
add_subdirectory(json)

ProcessorCount(NCPU)

ExternalProject_Add(rgbmatrix_build
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/rpi-rgb-led-matrix
    BUILD_COMMAND make
    PREFIX rpi-rgb-led-matrix
    CONFIGURE_COMMAND ""
    BUILD_COMMAND -j${NCPU}
    BUILD_IN_SOURCE 1
    INSTALL_COMMAND "" # The library does not provide any install facility
)

add_library(rgbmatrix STATIC IMPORTED)
set_target_properties(rgbmatrix PROPERTIES IMPORTED_LOCATION ${RGB_LIB_DIRS}/librgbmatrix.a)
