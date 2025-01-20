cmake_minimum_required(VERSION 3.31)

project(network_programming)

set(CMAKE_CXX_STANDARD 23)

# 获取编译器信息
get_filename_component(COMPILER_DIR ${CMAKE_CXX_COMPILER} DIRECTORY)
get_filename_component(COMPILER_ROOT ${COMPILER_DIR} DIRECTORY)

# 自动设置包含路径
include_directories(${COMPILER_ROOT}/include)

# 添加项目根目录到包含路径
include_directories(${PROJECT_SOURCE_DIR})

# Npcap 相关设置
set(NPCAP_DIR ${PROJECT_SOURCE_DIR}/npcap-sdk-1.13)

include_directories(${NPCAP_DIR}/Include)
link_directories(${NPCAP_DIR}/Lib/x64) # ?may need to add 'x64' to the end of the path

# 设置可执行文件输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 添加源文件
set(SOURCES
    main.cpp
    src/device.cpp
)

# 添加头文件目录
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

add_executable(network_programming ${SOURCES})

target_link_libraries(network_programming Packet.lib wpcap.lib ws2_32.lib)
