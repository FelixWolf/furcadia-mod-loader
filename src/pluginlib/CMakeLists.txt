# Add the executable target for the main module
project(pluginlib)

set(pluginlib_SOURCE_FILES
    pluginlib.cpp
)

set(pluginlib_HEADER_FILES
    pluginlib.h
)


set_source_files_properties(${pluginlib_HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

list(APPEND pluginlib_SOURCE_FILES ${pluginlib_HEADER_FILES})

add_library(${PROJECT_NAME} STATIC
    ${pluginlib_SOURCE_FILES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    PREFIX ""
)


target_include_directories(pluginlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})