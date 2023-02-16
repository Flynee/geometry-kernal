#include<iostream>

#include<TopoDS.hxx>
#include<BRepBuilderAPI_Copy.hxx>
#include<BRepAlgoAPI_Fuse.hxx>
#include<BRepAlgoAPI_Common.hxx>
#include<BRepAlgoAPI_Cut.hxx>
#include<BRepAlgoAPI_BuilderAlgo.hxx>
#include<TopTools_ListOfShape.hxx>
#include<BRepAlgoAPI_Splitter.hxx>
#include<Bnd_Box.hxx>
#include<BRepBndLib.hxx>
#include<gp_Dir.hxx>
#include<BRepPrimAPI_MakePrism.hxx>
#include<BRepPrimAPI_MakeRevol.hxx>
#include<BRepOffsetAPI_MakePipe.hxx>
#include<GeomFill_Trihedron.hxx>



namespace tool {

	// shape 克隆
	TopoDS_Shape copy_shape(const TopoDS_Shape& shape) {
		TopoDS_Shape copy_shape;
		copy_shape = BRepBuilderAPI_Copy(shape);
		return copy_shape;
	}

	// 获取shape BBOX
	Bnd_Box get_shape_bbox(const TopoDS_Shape& shape) {
		Bnd_Box bbox;
		BRepBndLib bbl;

		bbl.Add(shape, bbox);

		return bbox;
		
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

	// shape 分离（将一个shape 分离成两个）
	TopoDS_Shape shape_split(const TopTools_ListOfShape& shapes, const TopTools_ListOfShape& tools) {
		BRepAlgoAPI_Splitter spliter;
		spliter.SetArguments(shapes);
		spliter.SetTools(tools);
		spliter.Build();
		TopoDS_Shape shape = spliter.Shape();

		return shape;

	
	}

	// 向量扫率
	TopoDS_Shape linear_sweep(TopoDS_Shape& s, const gp_Vec& v) {
		BRepPrimAPI_MakePrism prism(s, v);
		prism.Build();
		TopoDS_Shape shape = prism.Shape();

		return shape;
	}

	// 旋转扫率
	TopoDS_Shape rotate_sweep(const TopoDS_Shape& s, const gp_Ax1& ax1, const Standard_Real angle) {
		BRepPrimAPI_MakeRevol revol(s, ax1, angle);
		revol.Build();
		TopoDS_Shape shape = revol.Shape();

		return shape;
	}

	// 路径扫率（将一个面沿一个路径扫率成一个管道）
	TopoDS_Shape path_sweep(const TopoDS_Wire& w, const TopoDS_Shape& s, const GeomFill_Trihedron m) {
		BRepOffsetAPI_MakePipe mp(w, s, m);
		mp.Build();
		TopoDS_Shape shape = mp.Shape();

		return shape;
	}


}