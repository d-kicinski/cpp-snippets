cmake_minimum_required(VERSION 3.10)
project(libstlrecipes VERSION 1.0.0 LANGUAGES CXX)

list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

# library build with c++17 enabled
#set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
#set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_CXX_EXTENSIONS OFF)


## Creating library

# Create target and set properties
add_library(snippets
    #include/snippets/rpn_calculator.hpp
    src/rpn_calculator.cpp
    src/vector_utils.cpp
)

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(snippets::snippets ALIAS snippets)

#Set target properties
target_include_directories(snippets
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(snippets PRIVATE cxx_auto_type)
target_compile_options(snippets PRIVATE -Werror)


##############################################
# Installation instructions
include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/snippets)

install(TARGETS snippets
    EXPORT snippets-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#This is required so that the exported target has the name JSONUtils and not jsonutils
set_target_properties(snippets PROPERTIES EXPORT_NAME snippets)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT snippets-targets
  FILE
    SnippetsTargets.cmake
  NAMESPACE
    snippets::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/SnippetsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/SnippetsConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/SnippetsConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    #${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SnippetsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/SnippetsConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)


##############################################
## Exporting from the build tree
#configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/FindRapidJSON.cmake
#    COPYONLY)

export(EXPORT snippets-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/SnippetsTargets.cmake NAMESPACE snippets::)

#Register package in user's package registry
export(PACKAGE snippets)

add_subdirectory(test)


