#include<iostream>
#include<math.h>
#include<TopoDS.hxx>
#include<BRepTools.hxx>

#include<BRepAlgoAPI_BooleanOperation.hxx>
#include<BRep_Builder.hxx>
#include<TopTools_ListOfShape.hxx>
#include<TColgp_Array1OfPnt.hxx>
#include<gp_Pnt.hxx>
#include<gp_Vec.hxx>
#include<gp_Ax1.hxx>
#include<gp_Ax2.hxx>
#include<gp_Dir.hxx>

#include"primitive.h"
#include"transform.h"

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
	// 测试布尔运算
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

	// 测试创建抛物面
	void make_paraboloid_panel() {
		
		const TopoDS_Shape& shape = prim::make_paraboloid_panel(0., 4.0, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试创建线段
	void make_segment() {
		const TopoDS_Shape& shape = prim::make_segment(gp_Pnt(0, 0, 0), gp_Pnt(2, 0, 0));
		BRepTools::Write(shape, "../shape.brep");
		
	}

	// 测试创建折线
	void make_polyline() {
		gp_Pnt p1(0., 0., 0.);
		gp_Pnt p2(2., 0., 0.);
		gp_Pnt p3(2., 4., 0.);
		gp_Pnt p4(0., 4., 0.);
		gp_Pnt p5(-2.0, 2., 0.);

		gp_Pnt list[] = { p1, p2, p3, p4, p5 };
		int size = sizeof(list) / sizeof(list[0]);

		std::cout << size << std::endl;
		const TopoDS_Shape& shape = prim::make_polyline(list, size);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试创建圆线
	void make_circle() {

		const TopoDS_Shape& shape = prim::make_circle(1.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试创建椭圆线
	void make_ellipse() {
		const TopoDS_Shape& shape = prim::make_ellipse(2.0, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试创建贝塞尔曲线
	void make_besizer_curve() {
		gp_Pnt p1(0., 0., 0.);
		gp_Pnt p2(1., 1., 0.);
		gp_Pnt p3(2., -1., 0.);
		gp_Pnt p4(4, 1., 0.);

		TColgp_Array1OfPnt list(1, 4); // sizing array                  
		list.SetValue(1, p1);
		list.SetValue(2, p2);
		list.SetValue(3, p3);
		list.SetValue(4, p4);

		const TopoDS_Shape& shape = prim::make_bezier_curve(list);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试创建抛物线
	void make_parabola() {
		const TopoDS_Shape& shape = prim::make_parabola(-4.0, 4.0, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}
	
	// 测试创建双曲线
	void make_hyperbola() {
		const TopoDS_Shape& shape = prim::make_hyperbola(4.0, 2.0, -2.0, 2.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试平移功能
	void transform_shape() {
		TopoDS_Shape shape;
		BRep_Builder builder;

		BRepTools::Read(shape, "../box33.brep", builder);

		shape = transf::translate_shape(shape, gp_Vec(3., 3., 3.));
		BRepTools::Write(shape, "../shape.brep");

	}

	// 测试旋转
	void rotate_shape() {
		TopoDS_Shape shape;
		BRep_Builder builder;
		BRepTools::Read(shape, "../box33.brep", builder);
		gp_Ax1 a1(gp_Pnt(0, 0, 0), gp_Dir(1.0, 0., 0.));
		shape = transf::rotate_shape(shape, a1, M_PI/2);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试缩放
	void scale_shape() {
		TopoDS_Shape shape;
		BRep_Builder builder;
		BRepTools::Read(shape, "../box33.brep", builder);

		shape = transf::scale_shape(shape, gp_Pnt(3, 4, 5), 6);
		BRepTools::Write(shape, "../shape.brep");
	}

	// 测试镜面
	void mirror_shape() {
		TopoDS_Shape shape;
		BRep_Builder builder;
		BRepTools::Read(shape, "../box33.brep", builder);
		gp_Ax2 a2(gp_Pnt(20, 0, 0), gp_Dir(1, 0, 0));
		shape = transf::mirror_shape(shape, a2);
		BRepTools::Write(shape, "../shape.brep");
		
	}

}