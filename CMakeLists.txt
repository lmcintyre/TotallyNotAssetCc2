cmake_minimum_required(VERSION 3.10)
project(notassetcc)

set(
        PROJ_LIBRARIES
        hkCompat.lib
        hkBase.lib
        hkSerialize.lib
        hkSceneData.lib
        hkVisualize.lib
        hkInternal.lib
        hkImageUtilities.lib
        hkaAnimation.lib
        hkaInternal.lib
        hkaPhysics2012Bridge.lib
        hkcdCollide.lib
        hkcdInternal.lib
        hkGeometryUtilities.lib
)

include_directories(
        "${HAVOK_SDK_ROOT}/Source/"
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    link_directories("${HAVOK_SDK_ROOT}/Lib/win32_vs2012_win7_noSimd/debug/")
else()
    link_directories("${HAVOK_SDK_ROOT}/Lib/win32_vs2012_win7_noSimd/release/")
endif()

add_executable(NotAssetCc main.cpp)
target_link_libraries(NotAssetCc ${PROJ_LIBRARIES})

set(CMAKE_CXX_STANDARD 14)



