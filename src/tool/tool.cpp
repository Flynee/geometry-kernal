#include<iostream>
#include<chrono>
#include<string>

#include<BRepTools.hxx>
#include<BRep_Builder.hxx>

#include<Standard_Real.hxx>
#include<TopoDS.hxx>
#include<TopoDS_Edge.hxx>
#include<TopoDS_Vertex.hxx>
#include<BRep_Tool.hxx>
#include<BRepBuilderAPI_Copy.hxx>
#include<BRepAlgoAPI_Fuse.hxx>
#include<BRepAlgoAPI_Common.hxx>
#include<BRepAlgoAPI_Cut.hxx>
#include<BRepAlgoAPI_BuilderAlgo.hxx>
#include<BRepAlgoAPI_Splitter.hxx>
#include<BRepPrimAPI_MakePrism.hxx>
#include<BRepPrimAPI_MakeRevol.hxx>
#include<BRepBuilderAPI_MakePolygon.hxx>
#include<BRepBuilderAPI_MakeFace.hxx>
#include<BRepBuilderAPI_MakeWire.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<BRepOffsetAPI_MakePipe.hxx>
#include<GeomFill_Trihedron.hxx>
#include<TopTools_ListOfShape.hxx>
#include<TopTools_ListIteratorOfListOfShape.hxx>
#include<Bnd_Box.hxx>
#include<BRepBndLib.hxx>
#include<gp_Dir.hxx>
#include<gp_Pnt.hxx>
#include<gp_Vec.hxx>
#include<gp_Ax1.hxx>
#include<TopExp_Explorer.hxx>
#include<TopAbs_ShapeEnum.hxx>
#include<BRepOffsetAPI_MakeFilling.hxx>
#include<GeomAbs_Shape.hxx>
#include<ShapeAnalysis_Edge.hxx>

#include"transform.h"

namespace tool {

	// shape 克隆
	TopoDS_Shape copy_shape(const TopoDS_Shape& shape, const bool copyGeom = true, const bool copyMesh = false) {
		TopoDS_Shape copy_shape;
		BRepBuilderAPI_Copy c;
		c.Perform(shape, copyGeom, copyMesh);
		c.Build();
		if (!c.IsDone()) {
			std::cout << "模型复制失败！" << std::endl;
		}
		copy_shape = c.Shape();
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
		if (!builder.IsDone()) {
			std::cout << "布尔相加运算失败！" << std::endl;
		}
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

	// 对连功能
	TopoDS_Shape line_connect2face( const TopoDS_Edge& e1, TopoDS_Edge& e2) {
		ShapeAnalysis_Edge anl;

		TopoDS_Vertex tv1_s = anl.FirstVertex(e1);
		TopoDS_Vertex tv1_e = anl.LastVertex(e1);
		TopoDS_Vertex tv2_s = anl.FirstVertex(e2);
		TopoDS_Vertex tv2_e = anl.LastVertex(e2);

		gp_Pnt v1s = BRep_Tool::Pnt(tv1_s);
		gp_Pnt v1e = BRep_Tool::Pnt(tv1_e);
		gp_Pnt v2s = BRep_Tool::Pnt(tv2_s);
		gp_Pnt v2e = BRep_Tool::Pnt(tv2_e);

		gp_Vec v1s_v1e(v1s, v1e);
		gp_Vec v1s_v2s(v1s, v2s);
		gp_Vec v2s_v2e(v1s, v2e);

		v1s_v1e.Normalize();
		v1s_v2s.Normalize();
		v2s_v2e.Normalize();


		double v1 = v1s_v1e * v1s_v2s;
		double v2 = v1s_v1e * v2s_v2e;

		TopoDS_Edge e3;
		TopoDS_Edge e4;
		BRepBuilderAPI_MakeWire mw;

		if (v1 > v2) { // e1 和 e2 的Orientation 相反
			e3 = BRepBuilderAPI_MakeEdge(v1e, v2s).Edge();
			e4 = BRepBuilderAPI_MakeEdge(v2e, v1s).Edge();
		}
		else {
			e3 = BRepBuilderAPI_MakeEdge(v1e, v2e).Edge();
			e4 = BRepBuilderAPI_MakeEdge(v2s, v1s).Edge();

		}
		
	
		mw.Add(e1);
		mw.Add(e3);
		mw.Add(e2);
		mw.Add(e4);
		TopoDS_Wire w = mw.Wire();
		TopoDS_Face face = BRepBuilderAPI_MakeFace(w);
		TopoDS_Shape shape = TopoDS_Shape(face);
		return shape;
	}

	// 边界填充
	TopoDS_Shape fill_closure_edge2face(const TopoDS_Edge list[], int size) {
		BRepBuilderAPI_MakeWire mw;

		for (int i = 0; i < size; i++) {
			TopoDS_Edge e = list[i];
			mw.Add(e);
		}
		BRepBuilderAPI_MakeFace f(mw);
		TopoDS_Shape shape = f.Shape();

		return shape;
	}

	// 线性阵列
	TopoDS_Shape shape_line_array(TopoDS_Shape& shape,
		int x_num = 1, int y_num = 1, int z_num = 1, 
		const Standard_Real dx = 0, const Standard_Real dy = 0, const Standard_Real dz = 0, bool link = true) {
		
		// 获取当前时间
		auto tps = std::chrono::system_clock::now();
		
		x_num = x_num > 1 ? x_num : 1;
		y_num = y_num > 1 ? y_num : 1;
		z_num = z_num > 1 ? z_num : 1;

		TopTools_ListOfShape allshpaeList;
		TopTools_ListIteratorOfListOfShape it(allshpaeList);

		// 先阵列 x 轴方向
		for (int i = 0; i < x_num; i+=1) {
			TopoDS_Shape s = tool::copy_shape(shape, link);
			double d = i * dx;
			gp_Vec v(1, 0, 0);
			transf::translate_shape(s, v*d);
			allshpaeList.Append(s);
		}

		// 在阵列 y 轴方向
		for (int i = 0; i < y_num; i += 1) {
			
			for (int j = 0; j < x_num; j+=1) {
				TopoDS_Shape s = tool::copy_shape(shape, link);
				double d = j * dx;
				gp_Vec v(1, 0, 0);

				double d2 = i * dy;
				gp_Vec v2(0, 1, 0);

				transf::translate_shape(s, v * d + v2*d2);
				allshpaeList.Append(s);
			}
		}

		// 在阵列 z 轴方向
		for (int i = 0; i < z_num; i += 1) {

			for (int j = 0; j < y_num; j += 1) {

				for (int k = 0; k < x_num; k += 1) {

					TopoDS_Shape s = tool::copy_shape(shape, link);
					double d = k * dx;
					gp_Vec v(1, 0, 0);

					double d2 = j * dy;
					gp_Vec v2(0, 1, 0);

					double d3 = i * dz;
					gp_Vec v3(0, 0, 1);


					transf::translate_shape(s, v * d + v2 * d2 + v3 * d3);
					allshpaeList.Append(s);
				}
			}
		}

		for (it.Initialize(allshpaeList); it.More(); it.Next()) {
			double x = it.Value().Location().Transformation().TranslationPart().X();
			double y = it.Value().Location().Transformation().TranslationPart().Y();
			double z = it.Value().Location().Transformation().TranslationPart().Z();

			printf("%lf \t %lf \t %lf \n", x, y, z);

		}

		auto tpe = std::chrono::system_clock::now();
		auto t = std::chrono::duration_cast<std::chrono::milliseconds>(tpe - tps);
		std::cout << "阵列时间: " << t.count() << std::endl;

		// 将所有shape 进行布尔相加
		tps = std::chrono::system_clock::now();

		BRep_Builder b;
		TopoDS_Compound c;
		b.MakeCompound(c);

		for (it.Initialize(allshpaeList); it.More(); it.Next()) {
			b.Add(c, it.Value());
		}

		tpe = std::chrono::system_clock::now();
		t = std::chrono::duration_cast<std::chrono::milliseconds>(tpe - tps);
		std::cout <<"合并体时间: " << t.count() << std::endl;
		
		return c;
	}

}