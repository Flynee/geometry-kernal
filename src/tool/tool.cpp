#include<iostream>
#include<chrono>
#include<string>
#include<map>
#include<vector>

#include<BRepTools.hxx>
#include<BRep_Builder.hxx>
#include<TopoDS.hxx>
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
#include<TopTools_DataMapOfShapeInteger.hxx>
#include<TopAbs_ShapeEnum.hxx>
#include<XCAFApp_Application.hxx>
#include<XmlXCAFDrivers.hxx>
#include<XCAFDoc_DocumentTool.hxx>
#include<TDataStd_Integer.hxx>
#include<XCAFDoc_ShapeTool.hxx>
#include<gp_XYZ.hxx>

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

	/*
	* description 数据交换过程
	* 1. 分析整体shape ，计算每个子shape( 体，面，线，点 ) 的 hashcode, 并同时给子shape 绑定一个 id
	* 2. 计算出整体shape 的topo 关系
	* 3. 将shape的信息写入到 一个xml 文件中
	*/
	std::map<int, std::map<int, std::vector<int>>> analyze_topo(const TopoDS_Shape& shape) {
		std::map<int, std::vector<int>> topo_data_solid; // 储存体拓扑信息
		std::map<int, std::vector<int>> topo_data_face; // 储存面拓扑信息
		std::map<int, std::vector<int>> topo_data_edge; // 储存边拓扑信息
		std::map<int, std::vector<int>> topo_data_vertex; // 储存顶点拓扑信息

	///////////////////////////////////////////////////// 第一步绑定标签
		int vertex_id	= 1;
		int edge_id		= 1;
		int face_id		= 1;
		int solid_id	= 1;

		// <shape, id, hashcode>
		TopTools_DataMapOfShapeInteger vertex_shape2tag, edge_shape2tag, face_shape2tag,
										solid_shape2tag, wire_shape2tag, shell_shape2tag;
		TopExp_Explorer explorer;

		// 给所有的体绑定标签
		for (explorer.Init(shape, TopAbs_SOLID); explorer.More(); explorer.Next()) {
			const TopoDS_Shape& s = explorer.Current();
			if (!solid_shape2tag.IsBound(s)) { // 对于未绑定信息的shape 进行信息绑定
				solid_shape2tag.Bound(s, solid_id++);
			}
		}

		explorer.Clear();
		// 给所有的面绑定标签
		for (explorer.Init(shape, TopAbs_FACE); explorer.More(); explorer.Next()) {
			const TopoDS_Shape& s = explorer.Current();
			if (!face_shape2tag.IsBound(s)) { // 对于未绑定信息的shape 进行信息绑定
				face_shape2tag.Bound(s, face_id++);
			}
		}

		explorer.Clear();
		// 给所有的边绑定标签
		for (explorer.Init(shape, TopAbs_EDGE); explorer.More(); explorer.Next()) {
			const TopoDS_Shape& s = explorer.Current();
			if (!edge_shape2tag.IsBound(s)) { // 对于未绑定信息的shape 进行信息绑定
				edge_shape2tag.Bound(s, edge_id++);
			}
		}

		explorer.Clear();
		// 给所有的顶点绑定标签
		for (explorer.Init(shape, TopAbs_VERTEX); explorer.More(); explorer.Next()) {
			const TopoDS_Shape& s = explorer.Current();
			if (!vertex_shape2tag.IsBound(s)) { // 对于未绑定信息的shape 进行信息绑定
				vertex_shape2tag.Bound(s, vertex_id++);
			}
		}
		explorer.Clear();

	///////////////////////////////////////////////////// 第二步计算拓扑信息
		TopTools_DataMapIteratorOfDataMapOfShapeInteger tagIterator0;
		TopExp_Explorer explorer0;

		// 计算体的拓扑信息
		for (tagIterator0.Initialize(solid_shape2tag); tagIterator0.More(); tagIterator0.Next()) {
			TopoDS_Shape shape = tagIterator0.Key();
			int id = tagIterator0.Value();
			std::vector<int> vec;

			explorer0.Clear();
			// 找出该体下所有面
			for (explorer0.Init(shape, TopAbs_FACE); explorer0.More(); explorer0.Next()) {
				const TopoDS_Shape& s = explorer0.Current();
				int i = face_shape2tag.Find(s);
				vec.push_back(i);
			}

			topo_data_solid[id]= vec;
		}

		tagIterator0.Reset();
		// 计算面的拓扑信息
		for (tagIterator0.Initialize(face_shape2tag); tagIterator0.More(); tagIterator0.Next()) {
			TopoDS_Shape shape = tagIterator0.Key();
			int id = tagIterator0.Value();
			std::vector<int> vec;

			explorer0.Clear();
			// 找出该面下所有边
			for (explorer0.Init(shape, TopAbs_EDGE); explorer0.More(); explorer0.Next()) {
				const TopoDS_Shape& s = explorer0.Current();
				int i = edge_shape2tag.Find(s);
				vec.push_back(i);
			}

			topo_data_face[id] = vec;
		}

		tagIterator0.Reset();
		// 计算线的拓扑信息
		for (tagIterator0.Initialize(edge_shape2tag); tagIterator0.More(); tagIterator0.Next()) {
			TopoDS_Shape shape = tagIterator0.Key();
			int id = tagIterator0.Value();
			std::vector<int> vec;

			explorer0.Clear();
			// 找出该线下所有点
			for (explorer0.Init(shape, TopAbs_VERTEX); explorer0.More(); explorer0.Next()) {
				const TopoDS_Shape& s = explorer0.Current();
				int i = vertex_shape2tag.Find(s);
				vec.push_back(i);
			}

			topo_data_edge[id] =  vec;
		}

		tagIterator0.Reset();

		// 计算线的拓扑信息
		for (tagIterator0.Initialize(vertex_shape2tag); tagIterator0.More(); tagIterator0.Next()) {
			TopoDS_Shape shape = tagIterator0.Key();
			int id = tagIterator0.Value();

			topo_data_vertex[id] = {id};
		}

		tagIterator0.Reset();


	///////////////////////////////////////////////////// 第三步写文件
		enum OBJ_TYPE {
			SOLID = 3,	// 体
			FACE = 2,	// 面
			EDGE = 1,	// 边
			VERTEX = 0	// 点

		};
		Handle(XCAFApp_Application) dummy_app = XCAFApp_Application::GetApplication();
		XmlXCAFDrivers::DefineFormat(dummy_app); // 注册读写驱动器
		Handle(TDocStd_Document) doc; // 定义一个文档类型
		dummy_app->NewDocument(TCollection_ExtendedString("XmlXCAF"), doc); // 生成一个文档
		static Handle(XCAFDoc_ShapeTool) docTool = XCAFDoc_DocumentTool::ShapeTool(doc->Main());

		TopTools_DataMapIteratorOfDataMapOfShapeInteger tagIterator;

		// 构建体标签
		for (tagIterator.Initialize(solid_shape2tag); tagIterator.More(); tagIterator.Next()) {
			TopoDS_Shape shape = tagIterator.Key();
			int id = tagIterator.Value();
			TDF_Label blankLable = docTool->NewShape();
			docTool->SetShape(blankLable, shape);
			TDataStd_Integer::Set(blankLable, id);
			TDataStd_Integer::Set(blankLable, "00000000-0000-0000-0000-000000000001", OBJ_TYPE::SOLID);
			solid_shape2tag.UnBind(shape);

		}

		tagIterator.Reset();
		// 构建面标签
		for (tagIterator.Initialize(face_shape2tag); tagIterator.More(); tagIterator.Next()) {
			TopoDS_Shape shape = tagIterator.Key();
			int id = tagIterator.Value();
			TDF_Label blankLable = docTool->NewShape();
			docTool->SetShape(blankLable, shape);
			TDataStd_Integer::Set(blankLable, id);
			TDataStd_Integer::Set(blankLable, "00000000-0000-0000-0000-000000000001", OBJ_TYPE::FACE);
			face_shape2tag.UnBind(shape);

		}

		tagIterator.Reset();
		// 构建边标签
		for (tagIterator.Initialize(edge_shape2tag); tagIterator.More(); tagIterator.Next()) {
			TopoDS_Shape shape = tagIterator.Key();
			int id = tagIterator.Value();
			TDF_Label blankLable = docTool->NewShape();
			docTool->SetShape(blankLable, shape);
			TDataStd_Integer::Set(blankLable, id);
			TDataStd_Integer::Set(blankLable, "00000000-0000-0000-0000-000000000001", OBJ_TYPE::EDGE);
			edge_shape2tag.UnBind(shape);

		}

		tagIterator.Reset();
		// 构建点标签
		for (tagIterator.Initialize(vertex_shape2tag); tagIterator.More(); tagIterator.Next()) {
			TopoDS_Shape shape = tagIterator.Key();
			int id = tagIterator.Value();
			TDF_Label blankLable = docTool->NewShape();
			docTool->SetShape(blankLable, shape);
			TDataStd_Integer::Set(blankLable, id);
			TDataStd_Integer::Set(blankLable, "00000000-0000-0000-0000-000000000001", OBJ_TYPE::VERTEX);
			vertex_shape2tag.UnBind(shape);

		}

		tagIterator.Reset();

		dummy_app->SaveAs(doc, "../shape.xml");
		dummy_app->Close(doc);

		/*
		* 返回的数据结构如下
			{
				SOLID_OBJ_TYPE: {
					solidId_1: [faceId_1, faceId_2...],
					solidId_2: [faceId_1, faceId_2...]
				},
				FACE_OBJ_TYPE: {
					faceId_1: [edgeId_1, edgeId_2...],
					faceId_2: [edgeId_1, edgeId_2...]
				},
				EDGE_OBJ_TYPE: {
					edgeId_1: [vertexId_1, vertexId_2...],
					edgeId_2: [vertexId_1, vertexId_2...]
				},
				VERTEX_OBJ_TYPE: {
					vertexId_1: [vertexId_1],
					vertexId_2: [vertexId_2],
					...
				},

			}
		*/
		std::map<int, std::map<int, std::vector<int>>> topo_res;

		topo_res[OBJ_TYPE::SOLID] = topo_data_solid;
		topo_res[OBJ_TYPE::FACE] = topo_data_face;
		topo_res[OBJ_TYPE::EDGE] = topo_data_edge;
		topo_res[OBJ_TYPE::VERTEX] = topo_data_vertex;


		return topo_res;
	}
 
	// 球行阵列（模型中心在圆外都删除掉）
	TopoDS_Shape shape_sphere_array(TopoDS_Shape& shape, 
		Standard_Real x, Standard_Real y, Standard_Real z, Standard_Real r,
		Standard_Real x_num, Standard_Real y_num, Standard_Real z_num,
		Standard_Real dx, Standard_Real dy, Standard_Real dz) {


		x_num = x_num > 1 ? x_num : 1;
		y_num = y_num > 1 ? y_num : 1;
		z_num = z_num > 1 ? z_num : 1;

		TopTools_ListOfShape allshpaeList;

		// 先阵列 x 轴方向
		for (int i = 0; i < x_num; i += 1) {
			TopoDS_Shape s = tool::copy_shape(shape, true);
			double d = i * dx;
			gp_Vec v(1, 0, 0);
			transf::translate_shape(s, v * d);
			allshpaeList.Append(s);
		}

		// 在阵列 y 轴方向
		for (int i = 0; i < y_num; i += 1) {

			for (int j = 0; j < x_num; j += 1) {
				TopoDS_Shape s = tool::copy_shape(shape, true);
				double d = j * dx;
				gp_Vec v(1, 0, 0);

				double d2 = i * dy;
				gp_Vec v2(0, 1, 0);

				transf::translate_shape(s, v * d + v2 * d2);
				allshpaeList.Append(s);
			}
		}

		// 在阵列 z 轴方向
		for (int i = 0; i < z_num; i += 1) {

			for (int j = 0; j < y_num; j += 1) {

				for (int k = 0; k < x_num; k += 1) {

					TopoDS_Shape s = tool::copy_shape(shape, true);
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


		TopTools_ListIteratorOfListOfShape it(allshpaeList);
		BRep_Builder b;
		TopoDS_Compound c;
		b.MakeCompound(c);
		for (it.Initialize(allshpaeList); it.More(); it.Next()) {
			b.Add(c, it.Value());
		}
		Bnd_Box bbox = get_shape_bbox(c);
		gp_XYZ minPoint = bbox.CornerMin().XYZ();
		gp_XYZ maxPoint = bbox.CornerMax().XYZ();
		gp_XYZ centerPoint = (minPoint + maxPoint) / 2;

		for (it.Initialize(allshpaeList); it.More(); it.Next()) {
			Bnd_Box tempbbox = get_shape_bbox(it.Value());
			gp_XYZ tempMinPoint = tempbbox.CornerMin().XYZ();
			gp_XYZ tempMaxPoint = tempbbox.CornerMax().XYZ();
			gp_XYZ tempCenterPoint = (tempMinPoint + tempMaxPoint) / 2;

			//std::cout << tempCenterPoint.X() <<","<< tempCenterPoint.Y() << "," << tempCenterPoint.Z() << std::endl;
			if (gp_Pnt(tempCenterPoint).Distance(gp_Pnt(centerPoint)) > r) {
				b.Remove(c, it.Value());
				std::cout << "shape REMOVE" << std::endl;
			}

		}

		if (c.IsNull()) { // 半径太小被删空了
			std::cout << "半径太小，无法生成阵列！" << std::endl;
			return shape;
		}

		return c;
	}


}