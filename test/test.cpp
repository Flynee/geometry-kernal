#include<iostream>
#include<math.h>
#include<TopoDS.hxx>
#include<BRepTools.hxx>
#include<STEPControl_Writer.hxx>

#include<BRep_Builder.hxx>
#include<BRepBuilderAPI_MakeFace.hxx>
#include<BRepBuilderAPI_MakeEdge.hxx>
#include<BRepBuilderAPI_MakeWire.hxx>
#include<BRepAlgoAPI_BooleanOperation.hxx>
#include<TopTools_ListOfShape.hxx>
#include<TColgp_Array1OfPnt.hxx>
#include<TopExp_Explorer.hxx>
#include<gp_Pnt.hxx>
#include<gp_Vec.hxx>
#include<gp_Ax1.hxx>
#include<gp_Ax2.hxx>
#include<gp_Dir.hxx>
#include<gp_Pln.hxx>
#include<Bnd_Box.hxx>
#include<TopAbs_ShapeEnum.hxx>

#include"primitive.h"
#include"transform.h"
#include"tool.h"

namespace test {
	// ���Դ�������
	void make_box() {
		const TopoDS_Shape& shape = prim::make_box(1.0, 1.0, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}
	// ���Դ���Բ׶/Բ̨ ��
	void make_cone() {
		const TopoDS_Shape& shape = prim::make_cone(1.0, .3, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}
	// ���Դ���Բ����
	void make_cylinder() {
		const TopoDS_Shape& shape = prim::make_cylinder(1.0, 2.0);
		BRepTools::Write(shape, "../shape.brep");
	}
	// ���Դ�������
	void make_sphere() {
		const TopoDS_Shape& shape = prim::make_sphere(1.0);
		BRepTools::Write(shape, "../shape.brep");
	}
	// ���Դ���Բ����
	void make_torus() {
		const TopoDS_Shape& shape = prim::make_torus(1.0, .3);
		BRepTools::Write(shape, "../shape.brep");
	}
	// ���Դ���Ш�ӣ���׶��������壩
	void make_prism() {
		const TopoDS_Shape& shape = prim::make_prism(1.0, 2.0, 1.0, 0.3, 0.3, 0.7, 0.7);
		BRepTools::Write(shape, "../shape.brep");
	}



	// ���Դ���Բ��
	void make_circle_panel() {
		const TopoDS_Shape& shape = prim::make_circle_panel(1.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ���Դ�����Բ��
	void make_ellipse_panel() {
		const TopoDS_Shape& shape = prim::make_ellipse_panel(2.0, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ���Դ�����������
	void make_triangle_panel() {
		gp_Pnt p1(0., 0., 0.);
		gp_Pnt p2(2., 0., 0.);
		gp_Pnt p3(3., 1., 0.);
		const TopoDS_Shape& shape = prim::make_triangle_panel(p1, p2, p3);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ���Դ����ı�����
	void make_rectangle_panel() {
		gp_Pnt p1(0., 0., 0.);
		gp_Pnt p2(2., 0., 0.);
		gp_Pnt p3(2., 4., 0.);
		gp_Pnt p4(0., 4., 0.);
		const TopoDS_Shape& shape = prim::make_rectangle_panel(p1, p2, p3, p4);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ���Դ��������
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
	// ���Բ�������
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

	// ���Դ���������
	void make_paraboloid_panel() {
		
		const TopoDS_Shape& shape = prim::make_paraboloid_panel(0., 4.0, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ���Դ����߶�
	void make_segment() {
		const TopoDS_Shape& shape = prim::make_segment(gp_Pnt(0, 0, 0), gp_Pnt(2, 0, 0));
		BRepTools::Write(shape, "../shape.brep");
		
	}

	// ���Դ�������
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

	// ���Դ���Բ��
	void make_circle() {

		const TopoDS_Shape& shape = prim::make_circle(1.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ���Դ�����Բ��
	void make_ellipse() {
		const TopoDS_Shape& shape = prim::make_ellipse(2.0, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ���Դ�������������
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

	// ���Դ���������
	void make_parabola() {
		const TopoDS_Shape& shape = prim::make_parabola(-4.0, 4.0, 1.0);
		BRepTools::Write(shape, "../shape.brep");
	}
	
	// ���Դ���˫����
	void make_hyperbola() {
		const TopoDS_Shape& shape = prim::make_hyperbola(4.0, 2.0, -2.0, 2.0);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ����ƽ�ƹ���
	void transform_shape() {
		TopoDS_Shape shape;
		BRep_Builder builder;

		BRepTools::Read(shape, "../box33.brep", builder);

		shape = transf::translate_shape(shape, gp_Vec(3., 3., 3.));
		BRepTools::Write(shape, "../shape.brep");

	}

	// ������ת
	void rotate_shape() {
		TopoDS_Shape shape;
		BRep_Builder builder;
		BRepTools::Read(shape, "../box33.brep", builder);
		gp_Ax1 a1(gp_Pnt(0, 0, 0), gp_Dir(1.0, 0., 0.));
		shape = transf::rotate_shape(shape, a1, M_PI/2);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ��������
	void scale_shape() {
		TopoDS_Shape shape;
		BRep_Builder builder;
		BRepTools::Read(shape, "../box33.brep", builder);

		shape = transf::scale_shape(shape, gp_Pnt(3, 4, 5), 6);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ���Ծ���
	void mirror_shape() {
		TopoDS_Shape shape;
		BRep_Builder builder;
		BRepTools::Read(shape, "../box33.brep", builder);
		gp_Ax2 a2(gp_Pnt(20, 0, 0), gp_Dir(1, 0, 0));
		shape = transf::mirror_shape(shape, a2);
		BRepTools::Write(shape, "../shape.brep");
		
	}

	// ���Կ�������
	void copy_shape() {
		TopoDS_Shape shape;
		BRep_Builder builder;
		BRepTools::Read(shape, "../box33.brep", builder);
		shape = tool::copy_shape(shape);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ���Բ��� �ϲ�
	void boolean_union_shape() {
	
		TopoDS_Shape shape1;
		TopoDS_Shape shape2;
		TopTools_ListOfShape objectShapes, toolShapes;

		BRep_Builder builder;

		BRepTools::Read(shape1, "../box33.brep", builder);
		BRepTools::Read(shape2, "../box34.brep", builder);


		TopoDS_Shape shape = tool::boolean_union_shape(shape1, shape2);
		BRepTools::Write(shape, "../shape.brep");

		
	}

	// ���Բ����ཻ
	void boolean_intersection_shape() {
		TopoDS_Shape shape1;
		TopoDS_Shape shape2;
		TopTools_ListOfShape objectShapes, toolShapes;

		BRep_Builder builder;

		BRepTools::Read(shape1, "../box33.brep", builder);
		BRepTools::Read(shape2, "../box34.brep", builder);


		TopoDS_Shape shape = tool::boolean_intersection_shape(shape1, shape2);
		BRepTools::Write(shape, "../shape.brep");

	}

	// ���Բ������
	void boolean_cut_shape() {
		TopoDS_Shape shape1;
		TopoDS_Shape shape2;
		TopTools_ListOfShape objectShapes, toolShapes;

		BRep_Builder builder;

		BRepTools::Read(shape1, "../box33.brep", builder);
		BRepTools::Read(shape2, "../box34.brep", builder);


		TopoDS_Shape shape = tool::boolean_cut_shape(shape1, shape2);
		BRepTools::Write(shape, "../shape.brep");

	}

	// ģ�����
	void shape_add() {
	
		TopoDS_Shape shape1;
		TopoDS_Shape shape2;
		TopTools_ListOfShape objectShapes, toolShapes;

		BRep_Builder builder;

		BRepTools::Read(shape1, "../box33.brep", builder);
		BRepTools::Read(shape2, "../box34.brep", builder);

		TopTools_ListOfShape shapeList;
		shapeList.Append(shape1);
		shapeList.Append(shape2);

		TopoDS_Shape shape = tool::shape_add(shapeList);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ģ�Ͳ�� �����罫һ��ģ�Ͳ�ֳ������֣�
	void shape_split() {

		TopoDS_Shape shape1;
		TopTools_ListOfShape objectShapes, toolShapes;

		BRep_Builder builder;

		BRepTools::Read(shape1, "../box33.brep", builder);

		objectShapes.Append(shape1);

		gp_Pln gpl(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0));

		BRepBuilderAPI_MakeFace face(gpl);
		toolShapes.Append(face.Shape());


		TopoDS_Shape shape = tool::shape_split(objectShapes, toolShapes);
		BRepTools::Write(shape, "../shape.brep");
		STEPControl_Writer stpWriter;
		stpWriter.Transfer(shape, STEPControl_AsIs);
		stpWriter.Write("../shape.stp");
	}

	// ��ȡģ��bbox
	void get_shape_bbox() {
	
		TopoDS_Shape shape;
		BRep_Builder builder;
		BRepTools::Read(shape, "../box33.brep", builder);

		Bnd_Box bbox = tool::get_shape_bbox(shape);

		gp_Pnt minPoint = bbox.CornerMin();
		gp_Pnt maxPoint = bbox.CornerMax();

		shape = prim::make_segment(minPoint, maxPoint);
		BRepTools::Write(shape, "../shape.brep");

	}

	// ����ɨ�ʣ���ɨ�ӳ���
	void linear_sweep_edge2face() {
		TopoDS_Shape lineShape = prim::make_segment(gp_Pnt(0, 0, 0), gp_Pnt(2, 0, 0));

		TopoDS_Shape shape = tool::linear_sweep(lineShape, gp_Vec(0, 2, 0));
		BRepTools::Write(shape, "../shape.brep");
	}

	// ����ɨ�ʣ���ɨ�ʳ���
	void linear_sweep_face2solid() {
		TopoDS_Shape panelShape = prim::make_rectangle_panel(gp_Pnt(0, 0, 0), gp_Pnt(2, 0, 0), gp_Pnt(2, 2, 0), gp_Pnt(0, 2, 0));

		TopoDS_Shape shape = tool::linear_sweep(panelShape, gp_Vec(0, 0, 3));
		BRepTools::Write(shape, "../shape.brep");
	}

	// ��תɨ�ʣ���ɨ�ʳ���
	void rotate_sweep_edge2face() {
		TopoDS_Shape lineShape = prim::make_segment(gp_Pnt(0, 0, 0), gp_Pnt(2, 0, 0));
		gp_Ax1 ax1;

		TopoDS_Shape shape = tool::rotate_sweep(lineShape, ax1, M_PI * 0.75);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ��תɨ�ʣ���ɨ�ʳ���
	void rotate_sweep_face2solid() {
		TopoDS_Shape panelShape = prim::make_rectangle_panel(gp_Pnt(0, 0, 0), gp_Pnt(2, 0, 0), gp_Pnt(2, 2, 0), gp_Pnt(0, 2, 0));

		gp_Ax1 ax1(gp_Pnt(0, 0, 0), gp_Dir(1, 0, 0));

		TopoDS_Shape shape = tool::rotate_sweep(panelShape, ax1, M_PI * 0.75);
		BRepTools::Write(shape, "../shape.brep");
	}

	// ·��ɨ�ʣ���ɨ�ʳ���
	void path_sweep_edge2face() {
		TopoDS_Shape lineShape = prim::make_segment(gp_Pnt(0, 0, 0), gp_Pnt(2, 0, 0));
		gp_Pnt list[] = { gp_Pnt(0, 0, 0), gp_Pnt(1, 0, 3), gp_Pnt(-1, 0, 5), gp_Pnt(0, 0, 7) };
		int size = sizeof(list) / sizeof(list[0]);

		TopoDS_Shape s = prim::make_polyline(list, size);
		TopExp_Explorer te(s, TopAbs_ShapeEnum::TopAbs_WIRE);
		TopoDS_Wire w = TopoDS::Wire(te.Current());
		TopoDS_Shape shape = tool::path_sweep(w, lineShape);
		BRepTools::Write(shape, "../shape.brep");
		
	}

	// ·��ɨ�ʣ���ɨ�ʳɹܵ�
	void path_sweep_face2solid() {
		TopoDS_Shape circleShape = prim::make_circle_panel(2);
		gp_Pnt list[] = { gp_Pnt(0, 0, 0), gp_Pnt(1, 0, 3), gp_Pnt(-1, 0, 5), gp_Pnt(0, 0, 7) };
		int size = sizeof(list) / sizeof(list[0]);

		TopoDS_Shape s = prim::make_polyline(list, size);
		TopExp_Explorer te(s, TopAbs_ShapeEnum::TopAbs_WIRE);
		TopoDS_Wire w = TopoDS::Wire(te.Current());
		TopoDS_Shape shape = tool::path_sweep(w, circleShape);
		BRepTools::Write(shape, "../shape.brep");

	}
}