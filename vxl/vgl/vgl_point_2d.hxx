// This is core/vgl/vgl_point_2d.hxx
#ifndef vgl_point_2d_hxx_
#define vgl_point_2d_hxx_
//:
// \file

#include <iostream>
#include <iomanip>
#include <string>
#include "vgl_point_2d.h"
//#include <vgl/vgl_homg_point_2d.h>
//#include <vgl/vgl_line_2d.h>
//#include <vgl/vgl_homg_line_2d.h>

/*
//: Construct from homogeneous point
template <class Type>
vgl_point_2d<Type>::vgl_point_2d(vgl_homg_point_2d<Type> const& p)
  : x_(p.x()/p.w()), y_(p.y()/p.w()) // could be infinite!
{
}

//: Construct from 2 lines (intersection).
template <class Type>
vgl_point_2d<Type>::vgl_point_2d(vgl_line_2d<Type> const& l1,
                                 vgl_line_2d<Type> const& l2)
{
  vgl_homg_line_2d<Type> h1(l1.a(), l1.b(), l1.c());
  vgl_homg_line_2d<Type> h2(l2.a(), l2.b(), l2.c());
  vgl_homg_point_2d<Type> p(h1, h2); // do homogeneous intersection
  set(p.x()/p.w(), p.y()/p.w()); // could be infinite!
}
*/







/*

#undef VGL_POINT_2D_INSTANTIATE
#define VGL_POINT_2D_INSTANTIATE(T) \
template class vgl_point_2d<T >; \
template double cross_ratio(vgl_point_2d<T >const&, vgl_point_2d<T >const&, \
                            vgl_point_2d<T >const&, vgl_point_2d<T >const&); \
template std::ostream& operator<<(std::ostream&, const vgl_point_2d<T >&); \
template std::istream& operator>>(std::istream&, vgl_point_2d<T >&)
*/
#endif // vgl_point_2d_hxx_
