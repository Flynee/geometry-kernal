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

namespace tool {

	// shape ��¡
	TopoDS_Shape copy_shape(const TopoDS_Shape& shape) {
		TopoDS_Shape copy_shape;
		copy_shape = BRepBuilderAPI_Copy(shape);
		return copy_shape;
	}

	// ��ȡshape BBOX
	Bnd_Box get_shape_bbox(const TopoDS_Shape& shape) {
		Bnd_Box bbox;
		BRepBndLib bbl;

		bbl.Add(shape, bbox);

		return bbox;
		
	}

	// �����ಢ (ȡ����)
	TopoDS_Shape boolean_union_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2) {
		BRepAlgoAPI_Fuse fuse(shape1, shape2);
		TopoDS_Shape shape = fuse.Shape();

		return  shape;
	}
	
	// �����ཻ��ȡ������
	TopoDS_Shape boolean_intersection_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2) {
		BRepAlgoAPI_Common common(shape1, shape2);

		TopoDS_Shape shape = common.Shape();

		return  shape;
	}


	// ������� ��shape1 - shape2��
	TopoDS_Shape boolean_cut_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2) {
		BRepAlgoAPI_Cut cut(shape1, shape2);

		TopoDS_Shape shape = cut.Shape();

		return  shape;
	}

	// shape ���
	TopoDS_Shape shape_add(const TopTools_ListOfShape& shpaeList) {
		BRepAlgoAPI_BuilderAlgo builder;

		builder.SetArguments(shpaeList);
		builder.Build();

		TopoDS_Shape shape = builder.Shape();

		return  shape;
	}

	// shape ���루��һ��shape �����������
	TopoDS_Shape shape_split(const TopTools_ListOfShape& shapes, const TopTools_ListOfShape& tools) {
		BRepAlgoAPI_Splitter spliter;
		spliter.SetArguments(shapes);
		spliter.SetTools(tools);
		spliter.Build();
		TopoDS_Shape shape = spliter.Shape();

		return shape;

	
	}
}