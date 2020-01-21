# EOOS SYSTEM.
#
# @author    Sergey Baigudin, sergey@baigudin.software
# @copyright 2019-2020, Sergey Baigudin, Baigudin Software
# @license   http://embedded.team/license/

target_include_directories(target-eoos
PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include>
)

target_sources(target-eoos
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Allocator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Heap.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Interrupt.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.Scheduler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/source/system.System.cpp
)
