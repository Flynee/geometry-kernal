#include<iostream>

#include<TopoDS.hxx>
#include<BRepBuilderAPI_Copy.hxx>
#include<BRepAlgoAPI_Fuse.hxx>
#include<BRepAlgoAPI_Common.hxx>
#include<BRepAlgoAPI_Cut.hxx>
#include<BRepAlgoAPI_BuilderAlgo.hxx>
#include<TopTools_ListOfShape.hxx>

namespace tool {

	// shape 克隆
	TopoDS_Shape copy_shape(const TopoDS_Shape& shape) {
		TopoDS_Shape copy_shape;
		copy_shape = BRepBuilderAPI_Copy(shape);
		return copy_shape;
	}

	// 布尔相并 (取并集)
	TopoDS_Shape boolean_union_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2) {
		BRepAlgoAPI_Fuse fuse(shape1, shape2);
		TopoDS_Shape shape = fuse.Shape();

		return  shape;
	}
	
	// 布尔相交（取交集）
	TopoDS_Shape boolean_intersection_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2) {
		BRepAlgoAPI_Common common(shape1, shape2);

		TopoDS_Shape shape = common.Shape();

		return  shape;
	}


	// 布尔相减 （shape1 - shape2）
	TopoDS_Shape boolean_cut_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2) {
		BRepAlgoAPI_Cut cut(shape1, shape2);

		TopoDS_Shape shape = cut.Shape();

		return  shape;
	}

	// shape 相加
	TopoDS_Shape shape_add(const TopTools_ListOfShape& shpaeList) {
		BRepAlgoAPI_BuilderAlgo builder;

		builder.SetArguments(shpaeList);
		builder.Build();

		TopoDS_Shape shape = builder.Shape();

		return  shape;
	}

}