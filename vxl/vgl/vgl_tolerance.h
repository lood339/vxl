#ifndef vgl_tolerance_h_
#define vgl_tolerance_h_

//! \file
//  \author Kieran O'Mahony
//  \date 21 August 2007
//  \brief Tolerances used throughout vgl when performing comparisons
//#include <vgl/vgl_export.h>
#include <cmath>
#include <limits>

template <typename T>
class vgl_tolerance
{
  public:
    //! Tolerance for judging 4 points to be coplanar
    static const T point_3d_coplanarity;

    //! Tolerance for judging positions to be equal
    static const T position;
};

template <typename T>
const T vgl_tolerance<T>::point_3d_coplanarity = (T)std::sqrt(1.0f*std::numeric_limits<T>::epsilon());

template <typename T>
const T vgl_tolerance<T>::position = std::numeric_limits<T>::epsilon();

template class vgl_tolerance<double>;
template class vgl_tolerance<float>;
template class vgl_tolerance<int>;
template class vgl_tolerance<unsigned int>;



#endif
