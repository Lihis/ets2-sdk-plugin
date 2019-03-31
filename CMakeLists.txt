cmake_minimum_required(VERSION 3.13)
project(ets2_sdk_plugin)

set(CMAKE_CXX_STANDARD 11)

include_directories(ets2-telemetry/inc)
include_directories(scs_sdk_1_5/include)
include_directories(scs_sdk_1_5/include/common)
include_directories(scs_sdk_1_5/include/eurotrucks2)

add_definitions(-DUNICODE)

add_library(ets2_sdk_plugin
            ets2-telemetry/inc/ets2-telemetry-common.hpp
            ets2-telemetry/inc/scs_config_handlers.hpp
            ets2-telemetry/inc/sharedmemory.hpp
            ets2-telemetry/src/ets2-telemetry.cpp
            ets2-telemetry/src/scs_config_handlers.cpp
            ets2-telemetry/src/sharedmemory.cpp
            scs_sdk_1_5/include/common/scssdk_telemetry_common_channels.h
            scs_sdk_1_5/include/common/scssdk_telemetry_common_configs.h
            scs_sdk_1_5/include/common/scssdk_telemetry_trailer_common_channels.h
            scs_sdk_1_5/include/common/scssdk_telemetry_truck_common_channels.h
            scs_sdk_1_5/include/eurotrucks2/scssdk_eut2.h
            scs_sdk_1_5/include/eurotrucks2/scssdk_telemetry_eut2.h
            scs_sdk_1_5/include/scssdk.h
            scs_sdk_1_5/include/scssdk_telemetry.h
            scs_sdk_1_5/include/scssdk_telemetry_channel.h
            scs_sdk_1_5/include/scssdk_telemetry_event.h
            scs_sdk_1_5/include/scssdk_value.h
            )

set_target_properties(ets2_sdk_plugin
                      PROPERTIES
                      OUTPUT_NAME "ets2-telemetry-server"
                      PREFIX ""
                      )

target_link_libraries(ets2_sdk_plugin
                      -static-libgcc
                      -static-libstdc++
                      -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic
                      )
