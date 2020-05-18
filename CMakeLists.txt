# cmake file for vxl (head file only version)

cmake_minimum_required(VERSION 3.8)


project(vxl LANGUAGES CXX) #

set(VXL_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/vxl)

add_library(vxl MODULE ${VXL_SRC_DIR}/vgl.hpp)
target_include_directories(vxl PUBLIC include)
target_compile_features(vxl PUBLIC cxx_std_11)
set_target_properties(vxl PROPERTIES LINKER_LANGUAGE CXX)

