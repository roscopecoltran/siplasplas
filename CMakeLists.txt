project(siplasplas)
cmake_minimum_required(VERSION 2.8)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/3rdParty ${CMAKE_SOURCE_DIR}/cmake)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(SIPLASPLAS_VERSION_MAJOR 0)
set(SIPLASPLAS_VERSION_MINOR 0)
set(SIPLASPLAS_VERSION_PATCH 1)

set(SIPLASPLAS_DRLPARSER_PYTHON_VERSION 2.7)
set(SIPLASPLAS_BUILDING_FROM_SOURCES TRUE CACHE INTERNAL "")
set(SIPLASPLAS_ROOT "${CMAKE_SOURCE_DIR}")

include(cmake/deftargets.cmake)
include(cmake/install.cmake)
include(cmake/git.cmake)

option(SIPLASPLAS_VERBOSE_CONFIG "Run siplasplas configuration with detailed output" OFF)
option(SIPLASPLAS_BUILD_TESTS    "Build tests"    ON)
option(SIPLASPLAS_BUILD_EXAMPLES "Build examples" ON)
option(SIPLASPLAS_BUILD_DOCS     "Build doxygen documentation" OFF)
option(SIPLASPLAS_DEPLOY_DOCS    "Generate target to deploy branch docs to website" OFF)
option(SIPLASPLAS_CI_BUILD                        "siplasplas running on continuous integration build" FALSE)
option(SIPLASPLAS_INSTALL_DRLPARSER_DEPENDENCIES  "Automatically install DRLParser dependencies" ON)
option(SIPLASPLAS_DOWNLOAD_LIBCLANG               "Download libclang from llvm mirror instead of using system LLVM installation" OFF)
option(SIPLASPLAS_COPY_DLL_DEPENDENCIES "Copy dll dependencies to the dependant target binary dir" ON)
option(SIPLASPLAS_USE_SYSTEM_SFML       "Use SFML system distribution instead of build from sources" OFF)
option(SIPLASPLAS_ENABLE_VALGRIND "Enable memory check of executable targets" OFF)
option(SIPLASPLAS_ENABLE_ASSERTS "Force assertions, which are disabled by default on Release build" OFF)
option(SIPLASPLAS_DUMP_ERRORS "Dump error logs after running an executable. Implies SIPLASPLAS_CLEAR_LOGS" ON)
option(SIPLASPLAS_IMGUI_SFML_EXAMPLES_ENABLED "Enable examples using imgui and SFML" OFF)
option(SIPLASPLAS_VERBOSE_DRLPARSER "Run reflection parser with detailed diagnostics" OFF)

include(cmake/siplasplas.cmake)
include(3rdParty/conan.cmake)

add_subdirectory(cmake)
add_subdirectory(3rdParty)
add_subdirectory(src)

if(SIPLASPLAS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
if(SIPLASPLAS_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
if(SIPLASPLAS_BUILD_DOCS)
    add_subdirectory(doc)
else()
    message(STATUS "Docs build disabled")
endif()
include(cmake/cpacksettings.cmake)

configure_file(
    ${CMAKE_SOURCE_DIR}/.ycm_extra_conf.py.in
    ${CMAKE_SOURCE_DIR}/.ycm_extra_conf.py
)
