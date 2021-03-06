project(gstreamer++)

include(setup_target_properties_library)
include(show_target_properties)

message("Setting up gstreamer++")

set(COMPONENTS_GSTREAMERPP_DEFINITIONS
    COMPONENTS_GSTREAMER
    "VERSION_MAJOR=${GSTREAMERPP_VERSION_MAJOR}"
    "VERSION_MINOR=${GSTREAMERPP_VERSION_MINOR}"
    "VERSION_MICRO=${GSTREAMERPP_VERSION_MICRO}"
    "VERSION_NANO=${GSTREAMERPP_VERSION_NANO}")

set(COMPONENTS_GSTREAMERPP_DEPENDENCIES
    core)

set(COMPONENTS_GSTREAMERPP_INCLUDE
    export
    include)

set(COMPONENTS_GSTREAMERPP_LIBS
    ${CMAKE_THREAD_LIBS_INIT}
    ${COMPONENTS_GSTREAMERPP_DEPENDENCIES})

file(GLOB_RECURSE COMPONENTS_GSTREAMERPP_INCLUDES_EXTERNAL export/*.h)
file(GLOB_RECURSE COMPONENTS_GSTREAMERPP_INCLUDES_LOCAL include/*.h)
file(GLOB COMPONENTS_GSTREAMERPP_SOURCES src/*.cpp)

#if (INSTALL_HEADERS_TO_TARGET)
#    install(FILES ${COMPONENTS_GSTREAMERPP_INCLUDES} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/cppsdk/generics)
#else()
#    foreach(path ${CMAKE_FIND_ROOT_PATH})
#        file(COPY ${COMPONENTS_GSTREAMERPP_INCLUDES} DESTINATION ${path}/usr/include/cppsdk/generics)
#    endforeach()
#endif()

set(COMPONENTS_GSTREAMERPP_INPUT
    ${COMPONENTS_GSTREAMERPP_SOURCES}
    ${COMPONENTS_GSTREAMERPP_INCLUDES_EXTERNAL}
    ${COMPONENTS_GSTREAMERPP_INCLUDES_LOCAL})

add_library(${PROJECT_NAME} ${COMPONENTS_GSTREAMERPP_INPUT})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${COMPONENTS_GSTREAMERPP_DEFINITIONS})
target_include_directories(${PROJECT_NAME} PUBLIC ${COMPONENTS_GSTREAMERPP_INCLUDE})
target_link_libraries(${PROJECT_NAME} PUBLIC ${COMPONENTS_GSTREAMERPP_LIBS})
#add_dependencies(${PROJECT_NAME} ${COMPONENTS_GSTREAMERPP_DEPENDENCIES})
set_target_properties(${PROJECT_NAME} PROPERTIES DEFINE_SYMBOL ${COMPONENTS_GSTREAMERPP_DEFINITIONS})
#set_target_properties(${PROJECT_NAME} PROPERTIES SOVERSION ${GSTREAMER_TEST_VERSION})

setup_target_properties_library(${PROJECT_NAME})

show_target_properties(${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

