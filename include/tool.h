#ifndef __TOOL_H__
#define __TOOL_H__
#include<TopoDS.hxx>
#include<BndLib.hxx>
#include<TopTools_ListOfShape.hxx>
#include<gp_Dir.hxx>
#include<GeomFill_Trihedron.hxx>

namespace tool {

	TopoDS_Shape copy_shape(const TopoDS_Shape& shape);
	Bnd_Box get_shape_bbox(const TopoDS_Shape& shape);
	TopoDS_Shape boolean_union_shape(const TopoDS_Shape& shape, const TopoDS_Shape& shape2);
	TopoDS_Shape boolean_intersection_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2);
	TopoDS_Shape boolean_cut_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2);
	TopoDS_Shape shape_add(const TopTools_ListOfShape& shpaeList);
	TopoDS_Shape shape_split(const TopTools_ListOfShape& shapes, const TopTools_ListOfShape& tools);
	TopoDS_Shape linear_sweep(TopoDS_Shape& shape, const gp_Vec& v);
	TopoDS_Shape rotate_sweep(const TopoDS_Shape& s, const gp_Ax1& ax1, const Standard_Real angle);
	TopoDS_Shape path_sweep(const TopoDS_Wire& w, const TopoDS_Shape& s, const GeomFill_Trihedron m = GeomFill_Trihedron::GeomFill_IsDiscreteTrihedron);

}

#endif // !__TOOL_H__
