// This is brl/bpro/core/vpgl_pro/processes/vpgl_generate_3d_point_from_cams_process.cxx
#include <iostream>
#include <fstream>
#include <bprb/bprb_func_process.h>
//:
// \file
#include <brdb/brdb_value.h>
#include <brdb/brdb_selection.h>
#include <bprb/bprb_batch_process_manager.h>
#include <bprb/bprb_parameters.h>
#include <bprb/bprb_macros.h>

#include <vcl_compiler.h>
#include <vpgl/vpgl_camera.h>
#include <vpgl/vpgl_perspective_camera.h>
#include <vpgl/algo/vpgl_triangulate_points.h>
#include <vsl/vsl_binary_io.h>
#include <bpro/core/bbas_pro/bbas_1d_array_int.h>
#include <bpro/core/bbas_pro/bbas_1d_array_unsigned.h>

namespace vpgl_generate_3d_point_from_cams_process_globals
{
    const unsigned n_inputs_ = 2;
    const unsigned n_outputs_ = 3;
}

//: Init function
bool vpgl_generate_3d_point_from_cams_process_cons(bprb_func_process& pro)
{
  using namespace vpgl_generate_3d_point_from_cams_process_globals;

  //process takes 2 inputs
  std::vector<std::string> input_types_(n_inputs_);
  input_types_[0] = "bbas_1d_array_unsigned_sptr";
  input_types_[1] = "bbas_1d_array_int_sptr"; // points

  // process has 3 outputs
  std::vector<std::string>  output_types_(n_outputs_);
  output_types_[0] = "float"; //X
  output_types_[1] = "float"; //Y
  output_types_[2] = "float"; //Z

  bool good = pro.set_input_types(input_types_) &&
              pro.set_output_types(output_types_);
  return good;
}

//: Execute the process
bool vpgl_generate_3d_point_from_cams_process(bprb_func_process& pro)
{
  // Sanity check
  if (!pro.verify_inputs()) {
    std::cerr << "vpgl_generate_3d_point_from_cams_process: Invalid inputs\n";
    return false;
  }

  // get the inputs
  unsigned i=0;
  bbas_1d_array_unsigned_sptr cam_ids_ptr = pro.get_input<bbas_1d_array_unsigned_sptr>(i++);
  bbas_1d_array_int_sptr      imgPoints   = pro.get_input<bbas_1d_array_int_sptr>(i++);

  //vector of cams, vector of points
  std::vector<vpgl_perspective_camera<double> > cams;
  vbl_array_1d<unsigned>& cam_ids = cam_ids_ptr->data_array;
  for (unsigned int i=0; i<cam_ids.size(); ++i) {
    unsigned cam_id = cam_ids[i];
    brdb_query_aptr Q = brdb_query_comp_new("id", brdb_query::EQ, cam_id);
    brdb_selection_sptr S = DATABASE->select("vpgl_camera_double_sptr_data", Q);
    if (S->size()!=1) {
      std::cout << "in vpgl_generate_3d_point_from_cams_process - bad input value\n";
      return false;
    }
    brdb_value_sptr value;
    if (!S->get_value(std::string("value"), value)) {
      std::cout << "in vpgl_generate_3d_from_cams- bad input value\n";
      return false;
    }
    vpgl_camera_double_sptr          cam_sptr = value->val<vpgl_camera_double_sptr>();
    vpgl_perspective_camera<double>* cam_ptr  = (vpgl_perspective_camera<double>*) cam_sptr.ptr();
    cams.push_back(*cam_ptr);
  }

  //gather image points
  std::vector<vgl_point_2d<double> > points;
  vbl_array_1d<int>& pts = imgPoints->data_array;
  for (unsigned int i=0; i<pts.size(); i+=2)
    points.push_back( vgl_point_2d<double>(pts[i], pts[i+1]) );

  //: Calculates the best 3D point corresponding to a set of 2D camera points.
  // Takes in a list of points and cameras, and finds the
  // least-squared solution to the intersection of the rays
  // generated by the points. Assumes that point i is viewed
  // by camera i. The result is placed into point_3d. Returns
  // the sum of squared errors.
  vgl_point_3d<double> point_3d;
  double error = vpgl_triangulate_points::triangulate( points, cams, point_3d );
  std::cout<<"RAYS INTERSECT AT POINT: "<<point_3d<< " with error "<<error<<std::endl;

  pro.set_output_val<float>(0, (float)point_3d.x());
  pro.set_output_val<float>(1, (float)point_3d.y());
  pro.set_output_val<float>(2, (float)point_3d.z());
  return true;
}