// This is core/vil2/vil2_sample_profile_bicub.txx
#ifndef vil2_sample_profile_bicub_txx_
#define vil2_sample_profile_bicub_txx_
//:
// \file
// \brief Bicubic profile sampling functions for 2D images

// The vil2 bicub source files were derived from the corresponding
// vil2 bilin files, thus the vil2 bilin/bicub source files are very
// similar.  If you modify something in this file, there is a
// corresponding bilin/bicub file that would likely also benefit from
// the same change.

#include "vil2_sample_profile_bicub.h"
#include <vil2/vil2_bicub_interp.h>

inline bool vil2_profile_in_image(double x0, double y0,
                                  double x1, double y1,
                                  const vil2_image_view_base& image)
{
  if (x0<2) return false;
  if (y0<2) return false;
  if (x0+3>image.ni()) return false;
  if (y0+3>image.nj()) return false;
  if (x1<2) return false;
  if (y1<2) return false;
  if (x1+3>image.ni()) return false;
  if (y1+3>image.nj()) return false;

  return true;
}

//: Sample along profile, using safe bicubic interpolation
//  Profile points are along the line between p0 and p1 (in image co-ordinates).
//  Vector v is resized to n*np elements, where np=image.n_planes().
//  v[0]..v[np-1] are the values from point p
//  Points outside image return zero.
template <class imType, class vecType>
void vil2_sample_profile_bicub(vecType* v,
                               const vil2_image_view<imType>& image,
                               double x0, double y0, double dx, double dy,
                               int n)
{
  bool all_in_image = vil2_profile_in_image(x0,y0,x0+(n-1)*dx,y0+(n-1)*dy,image);

  const unsigned ni = image.ni();
  const unsigned nj = image.nj();
  const unsigned np = image.nplanes();
  const vcl_ptrdiff_t istep = image.istep();
  const vcl_ptrdiff_t jstep = image.jstep();
  const vcl_ptrdiff_t pstep = image.planestep();
  double x=x0;
  double y=y0;
  const imType* plane0 = image.top_left_ptr();

  if (all_in_image)
  {
    if (np==1)
    {
      for (int k=0;k<n;++k,x+=dx,y+=dy)
      v[k] = vil2_bicub_interp(x,y,plane0,ni,nj,istep,jstep);
    }
    else
    {
      for (int k=0;k<n;++k,x+=dx,y+=dy)
      {
        for (unsigned int p=0;p<np;++p,++v)
          *v = vil2_bicub_interp(x,y,plane0+p*pstep,ni,nj,istep,jstep);
      }
    }
  }
  else
  {
    // Use safe interpolation
    if (np==1)
    {
      for (int k=0;k<n;++k,x+=dx,y+=dy)
      v[k] = vil2_bicub_interp_safe(x,y,plane0,ni,nj,istep,jstep);
    }
    else
    {
      for (int k=0;k<n;++k,x+=dx,y+=dy)
      {
        for (unsigned int p=0;p<np;++p,++v)
          *v = vil2_bicub_interp_safe(x,y,plane0+p*pstep,ni,nj,istep,jstep);
      }
    }
  }
}

#define VIL2_SAMPLE_PROFILE_BICUB_INSTANTIATE( imType, vecType ) \
template void vil2_sample_profile_bicub(vecType* v, \
                                        const vil2_image_view<imType >& image, \
                                        double x0, double y0, \
                                        double dx, double dy, \
                                        int n)

#endif // vil2_sample_profile_bicub
