#ifndef vil2_resample_bicub_h_
#define vil2_resample_bicub_h_
//:
//  \file
//  \brief Sample grid of points with bicubic interpolation in one image and place in another

// The vil2 bicub source files were derived from the corresponding
// vil2 bilin files, thus the vil2 bilin/bicub source files are very
// similar.  If you modify something in this file, there is a
// corresponding bilin/bicub file that would likely also benefit from
// the same change.

#include <vil2/vil2_image_view.h>

//: Sample grid of points in one image and place in another, using bicubic interpolation.
//  dest_image(i,j,p) is sampled from the src_image at
//  (x0+i.dx1+j.dx2,y0+i.dy1+j.dy2), where i=[0..n1-1], j=[0..n2-1]
//  dest_image resized to (n1,n2,src_image.nplanes())
//  Points outside image return zero.
// \relates vil2_image_view
template <class sType, class dType>
void vil2_resample_bicub(const vil2_image_view<sType>& src_image,
                         vil2_image_view<dType>& dest_image,
                         double x0, double y0, double dx1, double dy1,
                         double dx2, double dy2, int n1, int n2);

#endif // vil2_resample_bicub_h_
