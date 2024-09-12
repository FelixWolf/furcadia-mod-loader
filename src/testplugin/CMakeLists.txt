# Add the executable target for the main module
project(testplugin)

set(testplugin_SOURCE_FILES
    dllmain.cpp
)

set(testplugin_HEADER_FILES
    dllmain.h
)


set_source_files_properties(${testplugin_HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

list(APPEND testplugin_SOURCE_FILES ${testplugin_HEADER_FILES})

add_library(${PROJECT_NAME} SHARED
    ${testplugin_SOURCE_FILES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "testplugin"
    PREFIX ""  # This removes the 'lib' prefix for DLLs
    SUFFIX ".dll"
)

target_link_libraries(${PROJECT_NAME} PRIVATE pluginlib)

target_link_options(${PROJECT_NAME} PRIVATE
    -static-libgcc
    -static-libstdc++
    -s
    -fvisibility=hidden
)

package_files($<TARGET_FILE:testplugin> "plugins/")