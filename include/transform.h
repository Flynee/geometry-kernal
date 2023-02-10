#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include<Standard.hxx>
#include<TopoDS.hxx>
#include<gp_Vec.hxx>
#include<gp_Pnt.hxx>
#include<gp_Vec.hxx>
#include<gp_Ax1.hxx>
#include<gp_Ax2.hxx>

namespace transf {
	TopoDS_Shape translate_shape(TopoDS_Shape& shape, const gp_Vec& v);
	TopoDS_Shape rotate_shape(TopoDS_Shape& shape, const gp_Ax1& a1, Standard_Real angel);
	TopoDS_Shape scale_shape(TopoDS_Shape& shape, const gp_Pnt& p, Standard_Real scale);
	TopoDS_Shape mirror_shape(TopoDS_Shape& shape, const gp_Ax2& a2);
}

#endif // !__TRANSFORM_H__
