# Add the executable target for the main module
project(modloader)

set(modloader_SOURCE_FILES
    dllmain.cpp
    wsock32_impl.cpp
    wsock32_impl.def
    sha256.c
    path.cpp
    hooking.cpp
)

set(modloader_HEADER_FILES
    wsock32_impl.hpp
    sha256.h
    path.h
    hooking.h
)


set_source_files_properties(${modloader_HEADER_FILES} PROPERTIES HEADER_FILE_ONLY TRUE)

list(APPEND modloader_SOURCE_FILES ${modloader_HEADER_FILES})

add_library(${PROJECT_NAME} SHARED
    ${modloader_SOURCE_FILES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "wsock32"
    PREFIX ""  # This removes the 'lib' prefix for DLLs
    SUFFIX ".dll"
)

target_link_libraries(${PROJECT_NAME} PRIVATE pluginlib wsock32 shlwapi)

target_link_options(${PROJECT_NAME} PRIVATE 
    -Wl,--enable-stdcall-fixup
    -Wl,--output-def,wsock32_proxy.def
    -static-libgcc
    -static-libstdc++
    -s
    -fvisibility=hidden
)

package_files($<TARGET_FILE:modloader> "")