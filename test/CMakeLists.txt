# This is core/vgl/tests/CMakeLists.txt

project(vgl_test_all)

add_executable( vgl_test_all
  ${VXL_SRC_DIR}/vgl/test/test_point.cxx
)
target_include_directories(vgl_test_all PRIVATE ${VXL_SRC_DIR})


#target_include_directories(vgl_test_all PRIVATE ${VXL_SRC_DIR})

