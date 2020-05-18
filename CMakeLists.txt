# cmake file for vxl (head file only version)

cmake_minimum_required(VERSION 3.8)


project(vxl LANGUAGES CXX) #

# c++ standard
if(NOT CMAKE_CXX_STANDARD)
   set(CMAKE_CXX_STANDARD "11")
endif()
if(NOT CMAKE_CXX_STANDARD_REQUIRED)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
endif()
if(NOT CMAKE_CXX_EXTENSIONS)
  set(CMAKE_CXX_EXTENSIONS OFF)
endif()
set(VALID_CXX_STANDARDS "11" "14" "17")
if(NOT CMAKE_CXX_STANDARD IN_LIST VALID_CXX_STANDARDS )
   MESSAGE(FATAL_ERROR "CMAKE_CXX_STANDARD:STRING=${CMAKE_CXX_STANDARD} not in know standards list\n ${VALID_CXX_STANDARDS}.")
endif()

# c standard
if(NOT CMAKE_C_STANDARD)
   set(CMAKE_C_STANDARD "11")
endif()
if(NOT CMAKE_C_STANDARD_REQUIRED)
  set(CMAKE_C_STANDARD_REQUIRED ON)
endif()
if(NOT CMAKE_C_EXTENSIONS)
  set(CMAKE_C_EXTENSIONS OFF)
endif()
set(VALID_C_STANDARDS "90" "99" "11")
if(NOT CMAKE_C_STANDARD IN_LIST VALID_C_STANDARDS )
   MESSAGE(FATAL_ERROR "CMAKE_C_STANDARD:STRING=${CMAKE_C_STANDARD} not in know standards list\n ${VALID_C_STANDARDS}.")
endif()


set(VXL_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/vxl)

#add_library(vxl MODULE ${VXL_SRC_DIR}/vgl.hpp)
#target_include_directories(vxl PUBLIC include)
#target_compile_features(vxl PUBLIC cxx_std_11)
#set_target_properties(vxl PROPERTIES LINKER_LANGUAGE CXX)


# test
option(BUILD_TESTING "Enable creation of Eigen tests." ON)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()