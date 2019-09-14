set(JSON_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/json/src PARENT_SCOPE)

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

#add_library(json SHARED ${CMAKE_CURRENT_SOURCE_DIR}/json/src)
