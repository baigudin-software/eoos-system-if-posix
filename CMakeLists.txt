# EOOS SYSTEM.
#
# @author    Sergey Baigudin, sergey@baigudin.software
# @copyright 2019-2022, Sergey Baigudin, Baigudin Software

target_include_directories(target-eoos
PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/public>"
PRIVATE
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/private>"
)

if(EOOS_ENABLE_TESTS)

target_include_directories(target-eoos
PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/include/private>"
)

endif()

target_sources(target-eoos
PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/source/sys.Call.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/sys.Main.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/sys.Scheduler.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/source/sys.System.cpp"
)
