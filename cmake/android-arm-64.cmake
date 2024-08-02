set(COMPILER_DIR ${ANDROID_NDK_HOME}/toolchains/llvm/prebuilt/linux-x86_64/bin)
set(CMAKE_C_COMPILER ${COMPILER_DIR}/aarch64-linux-android34-clang)
set(CMAKE_CXX_COMPILER ${COMPILER_DIR}/aarch64-linux-android34-clang++)
# prefix aarch64-linux-android...

include(${CMAKE_CURRENT_LIST_DIR}/static_link_libstdcxx.cmake)