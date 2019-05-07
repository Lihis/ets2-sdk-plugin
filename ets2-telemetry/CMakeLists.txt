project(plugin)

add_definitions(-DUNICODE)

add_library(plugin_defs INTERFACE)
add_library(ets2telemetry::plugindefs ALIAS plugin_defs)
target_include_directories(plugin_defs
                           INTERFACE
                           "${CMAKE_CURRENT_LIST_DIR}/inc"
                           )

add_library(${PROJECT_NAME}
            SHARED
            inc/ets2-telemetry-common.hpp
            inc/scs_config_handlers.hpp
            inc/sharedmemory.hpp
            src/ets2-telemetry.cpp
            src/scs_config_handlers.cpp
            src/sharedmemory.cpp
            )
add_library(ets2telemetry::plugin ALIAS ${PROJECT_NAME})

set_target_properties(${PROJECT_NAME}
                      PROPERTIES
                      OUTPUT_NAME "ets2-telemetry-server"
                      PREFIX ""
                      )

target_link_libraries(${PROJECT_NAME}
                      PUBLIC
                      scs::sdk
                      ets2telemetry::plugindefs
                      )

if(MINGW)
    target_link_libraries(${PROJECT_NAME}
                          PRIVATE
                          -static-libgcc
                          -static-libstdc++
                          -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
                          )
endif()
