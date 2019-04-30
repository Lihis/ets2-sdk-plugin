cmake_minimum_required(VERSION 3.13)
project(ets2_sdk_plugin)

set(CMAKE_CXX_STANDARD 11)

include_directories(ets2-telemetry/inc)

add_subdirectory(scs-sdk)

add_definitions(-DUNICODE)

add_library(ets2_sdk_plugin
            ets2-telemetry/inc/ets2-telemetry-common.hpp
            ets2-telemetry/inc/scs_config_handlers.hpp
            ets2-telemetry/inc/sharedmemory.hpp
            ets2-telemetry/src/ets2-telemetry.cpp
            ets2-telemetry/src/scs_config_handlers.cpp
            ets2-telemetry/src/sharedmemory.cpp
            )

set_target_properties(ets2_sdk_plugin
                      PROPERTIES
                      OUTPUT_NAME "ets2-telemetry-server"
                      PREFIX ""
                      )

target_link_libraries(ets2_sdk_plugin
                      PRIVATE
                      scs::sdk
                      -static-libgcc
                      -static-libstdc++
                      -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
                      )
