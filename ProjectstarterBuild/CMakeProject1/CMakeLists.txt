# CMakeList.txt: CMakeProject1 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#

# 将源代码添加到此项目的可执行文件。
file(GLOB SOURCES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")
add_executable(CMakeProject1 ${SOURCES} "k2.hpp")


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 23)
endif()

target_link_libraries(CMakeProject1 PRIVATE  spdlog)
