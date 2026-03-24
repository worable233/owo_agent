cmake_minimum_required(VERSION 3.10)
project(owo-agent)

# ==========================================
# 1. 基础设置
# ==========================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ==========================================
# 2. 编译优化与多线程设置
# ==========================================

# 【优化】发布模式优化级别 (-O3)
# 如果未指定构建类型，默认为 Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# 【优化】添加优化标志
# -O3: 最高级速度优化
# -flto: 链接时优化 (进一步减小体积提升速度，但会增加编译时间)
# -s: 剥离符号表 (减小文件体积，相当于运行 strip 命令)
set(CMAKE_CXX_FLAGS_RELEASE "-O3  -flto -s")
set(CMAKE_C_FLAGS_RELEASE "-O3 -flto -s")

# 【多线程编译】让 make 默认使用所有可用核心
# 这样你运行 'make' 时自动等同于 'make -j$(nproc)'
include(ProcessorCount)
ProcessorCount(N)
if(NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif()

# ==========================================
# 3. 头文件与依赖查找
# ==========================================
include_directories(${CMAKE_SOURCE_DIR}/include)


find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
# 【新增】尝试查找 Zstd (如果系统没装 pkg-config 可能找不到，直接写名字也行)
# 如果 find_package 失败，我们直接在 link_libraries 里写 zstd 也能工作
find_package(PkgConfig QUIET)
if(PkgConfig_FOUND)
    pkg_check_modules(ZSTD QUIET libzstd)
endif()

# 打印找到的库路径，方便调试 (可选)
message(STATUS "OpenSSL include dir: ${OPENSSL_INCLUDE_DIR}")
message(STATUS "OpenSSL libraries: ${OPENSSL_LIBRARIES}")
message(STATUS "ZLIB include dir: ${ZLIB_INCLUDE_DIRS}")
message(STATUS "ZLIB libraries: ${ZLIB_LIBRARIES}")

# ==========================================
# 4. 创建可执行文件
# ==========================================
file(GLOB SOURCES "*.cpp")
add_executable(app ${SOURCES})

# 忽略弃用警告 (保持输出干净)
target_compile_options(app PRIVATE -Wno-deprecated-declarations)

# ==========================================
# 5. 【核心】部分静态链接配置
# ==========================================
# 逻辑：
# 1. -Wl,-Bstatic : 告诉链接器，接下来的库尽量找静态库 (.a)
# 2. ssl, crypto, z : 这些库将被静态链接
# 3. -Wl,-Bdynamic : 告诉链接器，接下来的库找动态库 (.so)
# 4. pthread, stdc++ : 这些保持动态链接 (兼容性更好)

target_link_libraries(app 
    -Wl,-Bstatic
    ssl
    crypto
    zstd 
    z
    -Wl,-Bdynamic
    pthread
    stdc++
)

# 如果使用 GCC/Clang 且开启了 LTO，可能需要链接插件 (通常 CMake 会自动处理，这里作为保险)
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_link_libraries(app 
        -Wl,--start-group
        dl
        -Wl,--end-group
    )
endif()