cmake_minimum_required(VERSION 3.21)
project(SmartCardManager)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_SHARED_LINKER_FLAGS "-static-libgcc -static-libstdc++")
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_library(SmartCardManager SHARED libMain.cpp CardManage/CardManager.cpp CardManage/CardManager.h CardManage/CardManageLogger.cpp CardManage/CardManageLogger.h PosManage/PosManager.cpp PosManage/PosManager.h PosManage/PosDevice.cpp PosManage/PosDevice.h BatchManage/BatchManager.cpp BatchManage/BatchManager.h Analyzer/Analyzer.cpp Analyzer/Analyzer.h)
