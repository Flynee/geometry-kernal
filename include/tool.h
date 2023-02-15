#ifndef __TOOL_H__
#define __TOOL_H__
#include<TopoDS.hxx>
#include<BndLib.hxx>
#include<TopTools_ListOfShape.hxx>

namespace tool {

	TopoDS_Shape copy_shape(const TopoDS_Shape& shape);
	Bnd_Box get_shape_bbox(const TopoDS_Shape& shape);
	TopoDS_Shape boolean_union_shape(const TopoDS_Shape& shape, const TopoDS_Shape& shape2);
	TopoDS_Shape boolean_intersection_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2);
	TopoDS_Shape boolean_cut_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2);
	TopoDS_Shape shape_add(const TopTools_ListOfShape& shpaeList);
	TopoDS_Shape shape_split(const TopTools_ListOfShape& shapes, const TopTools_ListOfShape& tools);

}

#endif // !__TOOL_H__
