cmake_minimum_required(VERSION 3.10)
project(compiler)

# compile flags
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS   "-g")                     # 调试信息
set(CMAKE_CXX_FLAGS   "-Wall")                  # 开启所有警告
set(CMAKE_C_COMPILER    "/usr/bin/x86_64-linux-gnu-gcc-7")
set(CMAKE_CXX_COMPILER  "/usr/bin/x86_64-linux-gnu-g++-7")
# debug flags
# add_definitions(-DDEBUG_DFA)
# add_definitions(-DDEBUG_SCANNER)
# add_definitions(-DDEBUG_PARSER)

# output settings
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)


# include
include_directories(./include)

# third party libs
add_library(jsoncpp ./src/third_party/jsoncpp/jsoncpp.cpp)

# --------------------- from lib ---------------------
# link libxx.a
# u should rename libxx-x86-win.a or libxx-x86-linux.a to libxx.a according to ur own platform
# link_directories(./lib)
# --------------------- from lib ---------------------

# build library
# every src file directory should be compile into a lib

aux_source_directory(./src/front FRONT_SRC)
add_library(Front ${FRONT_SRC})

# 为了 debug 方便，你可以选择通过源文件来构建 IR 测评机，但是请以链接静态库文件的方式去跑分（为了防止你们修改测评机，在OJ上我们会采取此方式）
# --------------------- from src ---------------------
aux_source_directory(./src/ir IR_SRC)
add_library(IR ${IR_SRC})
aux_source_directory(./src/tools TOOLS_SRC)
add_library(Tools ${TOOLS_SRC})
# --------------------- from src ---------------------


# executable
add_executable(compiler main.cpp)

# link
# every lib should be linked with [compiler]
target_link_libraries(compiler Tools Front IR jsoncpp)