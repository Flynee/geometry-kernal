#include<iostream>

#include<TopoDS.hxx>
#include<BRepBuilderAPI_Copy.hxx>

namespace tool {

	// ¿½±´
	TopoDS_Shape copy_shape(const TopoDS_Shape& shape) {
		TopoDS_Shape copy_shape;
		copy_shape = BRepBuilderAPI_Copy(shape);
		return copy_shape;
	}

	// 

}