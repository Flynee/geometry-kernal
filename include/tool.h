#ifndef __TOOL_H__
#define __TOOL_H__
#include<TopoDS.hxx>

namespace tool {

	TopoDS_Shape copy_shape(const TopoDS_Shape& shape);
	TopoDS_Shape boolean_union_shape(const TopoDS_Shape& shape, const TopoDS_Shape& shape2);
	TopoDS_Shape boolean_intersection_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2);
	TopoDS_Shape boolean_cut_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2);
	TopoDS_Shape shape_add(const TopTools_ListOfShape& shpaeList);
}

#endif // !__TOOL_H__
