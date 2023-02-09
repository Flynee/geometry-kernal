#include<iostream>
#include<math.h>

#include<TopoDS.hxx>
#include<Standard_TypeDef.hxx>
#include<BRepPrimAPI_MakeBox.hxx>
#include<BRepPrimAPI_MakeCone.hxx>
#include<BRepPrimAPI_MakeCylinder.hxx>
#include<BRepPrimAPI_MakeSphere.hxx>
#include<BRepPrimAPI_MakeTorus.hxx>
#include<BRepPrimAPI_MakePrism.hxx>
#include<BRepPrimAPI_MakeWedge.hxx>


#include<BRepBuilderAPI_MakeEdge.hxx>
#include<BRepBuilderAPI_MakeWire.hxx>
#include<BRepBuilderAPI_MakeFace.hxx>
#include<BRepBuilderAPI_MakePolygon.hxx>
#include<BRepPrimAPI_MakeRevol.hxx>
#include<GC_MakeArcOfParabola.hxx>
#include<gp_Ax2.hxx>
#include<gp_Ax1.hxx>
#include<gp_Dir.hxx>
#include<gp_Circ.hxx>
#include<gp_Elips.hxx>
#include<gp_Lin.hxx>
#include<gp_Parab.hxx>
#include<Geom_Curve.hxx>
#include<Geom_TrimmedCurve.hxx>

namespace prim {

	// 创建方体
	TopoDS_Shape make_box(Standard_Real dx, Standard_Real dy, Standard_Real dz) {
		BRepPrimAPI_MakeBox box(dx, dy, dz);
		const TopoDS_Shape& shape = box.Shape();
		return shape;
	}

	// 创建圆锥/圆台 体
	TopoDS_Shape make_cone(Standard_Real r1, Standard_Real r2, Standard_Real h) {
		BRepPrimAPI_MakeCone cone(r1, r2, h);
		const TopoDS_Shape& shape = cone.Shape();
		return shape;
	}

	// 创建圆柱
	TopoDS_Shape make_cylinder(Standard_Real r, Standard_Real h) {
		BRepPrimAPI_MakeCylinder cylinder(r, h);
		const TopoDS_Shape& shape = cylinder.Shape();
		return shape;
	}

	// 创建球体
	TopoDS_Shape make_sphere(Standard_Real r) {
		BRepPrimAPI_MakeSphere sphere(r);
		const TopoDS_Shape& shape = sphere.Shape();
		return shape;
	}

	// 圆环体
	TopoDS_Shape make_torus(Standard_Real r1, Standard_Real r2) {
		BRepPrimAPI_MakeTorus torus(r1, r2);
		const TopoDS_Shape& shape = torus.Shape();
		return shape;
	}

	// 棱锥体/棱柱 （用楔子构造）
	TopoDS_Shape make_prism(Standard_Real dx, Standard_Real dy, Standard_Real dz, Standard_Real xmin, Standard_Real zmin, Standard_Real xmax, Standard_Real zmax) {
		BRepPrimAPI_MakeWedge wedge(dx, dy, dz, xmin, zmin, xmax, zmax);
		const TopoDS_Shape& shape = wedge.Shape();
		return shape;
	}

	// 椭圆体 TODO

	// 三角形面
	TopoDS_Shape make_triangle_panel(const gp_Pnt& p1, const gp_Pnt& p2, const gp_Pnt& p3) {
		BRepBuilderAPI_MakePolygon wire(p1, p2, p3, p1);
		BRepBuilderAPI_MakeFace face(wire);
		const TopoDS_Shape& shape = face.Shape();
		return shape;
	}

	// 四边形面
	TopoDS_Shape make_rectangle_panel(const gp_Pnt& p1, const gp_Pnt& p2, const gp_Pnt& p3, const gp_Pnt& p4) {
		BRepBuilderAPI_MakePolygon wire;
		wire.Add(p1);
		wire.Add(p2);
		wire.Add(p3);
		wire.Add(p4);
		wire.Add(p1);

		BRepBuilderAPI_MakeFace face(wire);
		const TopoDS_Shape& shape = face.Shape();
		return shape;
	}

	// 圆面 
	TopoDS_Shape make_circle_panel(Standard_Real r) {
		gp_Ax2 a2;
		gp_Circ gpc(a2, r);
		BRepBuilderAPI_MakeEdge edge(gpc);
		BRepBuilderAPI_MakeWire wire(edge);
		BRepBuilderAPI_MakeFace face(wire);
		const TopoDS_Shape& shape = face.Shape();
		return shape;
	}

	// 椭圆面
	TopoDS_Shape make_ellipse_panel(Standard_Real r1, Standard_Real r2) {
		gp_Ax2 a2;
		gp_Elips gpe(a2, r1, r2);
		BRepBuilderAPI_MakeEdge edge(gpe);
		BRepBuilderAPI_MakeWire wire(edge);
		BRepBuilderAPI_MakeFace face(wire);
		const TopoDS_Shape& shape = face.Shape();
		return shape;
	}

	// 多边形面
	TopoDS_Shape make_polygon_panel(const gp_Pnt list[], int size) {
		BRepBuilderAPI_MakePolygon wire;
		for (int i = 0; i < size; i++) {
			gp_Pnt p = list[i];
			wire.Add(p);
		}
		gp_Pnt p = list[0];
		wire.Add(p);
		BRepBuilderAPI_MakeFace face(wire);
		const TopoDS_Shape& shape = face.Shape();
		return shape;
	}

	// 抛物面
	TopoDS_Shape make_paraboloid_panel(Standard_Real min, Standard_Real max, Standard_Real f) {
		gp_Ax1 a1(gp_Pnt(0, 0, 0), gp_Dir(1.0, 0, 0));
		gp_Ax2 a2;
		gp_Parab gpp(a2, f);
		GC_MakeArcOfParabola tc(gpp, min, max, true);
		Handle(Geom_TrimmedCurve) tcurve = tc.Value();
	
		BRepBuilderAPI_MakeEdge edge(tcurve);
		const TopoDS_Shape& shape = BRepPrimAPI_MakeRevol(edge, a1);

		return shape;
	}





}
