# EVerest helper functions

add_library(everest_helpers STATIC)
add_library(everest::helpers ALIAS everest_helpers)
ev_register_library_target(everest_helpers)

target_sources(everest_helpers
    PRIVATE
        src/helpers.cpp
)

if (EVEREST_CORE_BUILD_TESTING)
    target_compile_definitions(everest_helpers PUBLIC EVEREST_COVERAGE_ENABLED)

    target_sources(everest_helpers
        PRIVATE
            src/coverage.cpp
    )
endif()

target_include_directories(everest_helpers
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        "$<TARGET_PROPERTY:generate_cpp_files,EVEREST_GENERATED_INCLUDE_DIR>"
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(everest_helpers
    PRIVATE
        Boost::headers
        fmt::fmt
        nlohmann_json::nlohmann_json
        everest::tls
)

set_target_properties(everest_helpers
    PROPERTIES
        POSITION_INDEPENDENT_CODE ON
)

add_dependencies(everest_helpers generate_cpp_files)

if (BUILD_TESTING)
    add_subdirectory(tests)
endif()

if(DISABLE_EDM)
    # Do not use evc_setup_package() here: it unconditionally installs an
    # export file for the package, which would export everest_helpers a second
    # time alongside everest-core-targets and break non-EDM consumers.
    set(EVEREST_HELPERS_CMAKE_INSTALL_DIR "${CMAKE_INSTALL_LIBDIR}/cmake/everest-helpers")

    configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/everest-helpers-config.cmake
        INSTALL_DESTINATION ${EVEREST_HELPERS_CMAKE_INSTALL_DIR}
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR
    )

    write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/everest-helpers-config-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY ExactVersion
    )

    install(
        FILES
            ${CMAKE_CURRENT_BINARY_DIR}/everest-helpers-config.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/everest-helpers-config-version.cmake
        DESTINATION ${EVEREST_HELPERS_CMAKE_INSTALL_DIR}
    )
endif()