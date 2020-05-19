# This is core/vgl/tests/CMakeLists.txt

project(vgl_test_all)

set(VGL_TEST_DIR ${VXL_SRC_DIR}/vgl/test)

add_executable( vgl_test_all
  ${VGL_TEST_DIR}/test_point.cxx
  ${VGL_TEST_DIR}/test_line_segment_3d.cxx
)

target_include_directories(vgl_test_all PRIVATE ${VXL_SRC_DIR} ${CMAKE_CURRENT_LIST_DIR})


#target_include_directories(vgl_test_all PRIVATE ${VXL_SRC_DIR})

