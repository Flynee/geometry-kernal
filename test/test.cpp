#include<iostream>
#include<TopoDS.hxx>
#include<BRepTools.hxx>
#include<gp_Pnt.hxx>

#include"primitive.h"
#include<BRepAlgoAPI_BooleanOperation.hxx>
#include<BRep_Builder.hxx>
#include<TopTools_ListOfShape.hxx>

namespace test {
	// 测试创建方体
	void make_box() {
		const TopoDS_Shape& shape = prim::make_box(1.0, 1.0, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}
	// 测试创建圆锥/圆台 体
	void make_cone() {
		const TopoDS_Shape& shape = prim::make_cone(1.0, .3, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}
	// 测试创建圆柱体
	void make_cylinder() {
		const TopoDS_Shape& shape = prim::make_cylinder(1.0, 2.0);
		BRepTools::Write(shape, "../shape.brep");
	}
	// 测试创建球体
	void make_sphere() {
		const TopoDS_Shape& shape = prim::make_sphere(1.0);
		BRepTools::Write(shape, "../shape.brep");
	}
	// 测试创建圆环体
	void make_torus() {
		const TopoDS_Shape& shape = prim::make_torus(1.0, .3);
		BRepTools::Write(shape, "../shape.brep");
	}
	// 测试创建楔子（棱锥体或棱柱体）
	void make_prism() {
		const TopoDS_Shape& shape = prim::make_prism(1.0, 2.0, 1.0, 0.3, 0.3, 0.7, 0.7);
		BRepTools::Write(shape, "../shape.brep");
	}



	// 测试创建圆面
	void make_circle_panel() {
		const TopoDS_Shape& shape = prim::make_circle_panel(1.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试创建椭圆面
	void make_ellipse_panel() {
		const TopoDS_Shape& shape = prim::make_ellipse_panel(2.0, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试创建三角形面
	void make_triangle_panel() {
		gp_Pnt p1(0., 0., 0.);
		gp_Pnt p2(2., 0., 0.);
		gp_Pnt p3(3., 1., 0.);
		const TopoDS_Shape& shape = prim::make_triangle_panel(p1, p2, p3);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试创建四边形面
	void make_rectangle_panel() {
		gp_Pnt p1(0., 0., 0.);
		gp_Pnt p2(2., 0., 0.);
		gp_Pnt p3(2., 4., 0.);
		gp_Pnt p4(0., 4., 0.);
		const TopoDS_Shape& shape = prim::make_rectangle_panel(p1, p2, p3, p4);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试创建多边形
	void make_polygon_panel() {
		gp_Pnt p1(0., 0., 0.);
		gp_Pnt p2(2., 0., 0.);
		gp_Pnt p3(2., 4., 0.);
		gp_Pnt p4(0., 4., 0.);
		gp_Pnt p5(-2.0, 2., 0.);

		gp_Pnt list[] = {p1, p2, p3, p4, p5};
		int size = sizeof(list) / sizeof(list[0]);

		std::cout << size << std::endl;
		const TopoDS_Shape& shape = prim::make_polygon_panel(list, size);
		BRepTools::Write(shape, "../shape.brep");
	}

	void bool_box() {
		TopoDS_Shape shape1;
		TopoDS_Shape shape2;
		TopTools_ListOfShape objectShapes, toolShapes;

		BRep_Builder builder;

		BRepTools::Read(shape1, "../box33.brep", builder);
		BRepTools::Read(shape2, "../box34.brep", builder);

		BRepTools::Write(shape1, "../box1.brep");
		BRepTools::Write(shape2, "../box2.brep");

		/*BRepAlgoAPI_BooleanOperation b(shape1, shape2, BOPAlgo_Operation::BOPAlgo_FUSE);*/
		BRepAlgoAPI_BuilderAlgo fragments;
		//fragments.SetRunParallel(parallel);
		fragments.SetRunParallel(true);
		objectShapes.Append(shape1);
		objectShapes.Append(shape2);
		toolShapes.Clear();
		fragments.SetArguments(objectShapes);
		fragments.SetFuzzyValue(1e-3);
		fragments.Build();

		/*if (!fragments.IsDone()) {
			Msg::Error("Boolean fragments failed");
			return false;
		}*/
		TopoDS_Shape shape = fragments.Shape();
		BRepTools::Write(shape, "../shape.brep");

	}

	void make_paraboloid_panel() {
		
		const TopoDS_Shape& shape = prim::make_paraboloid_panel(0., 4.0, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}
}