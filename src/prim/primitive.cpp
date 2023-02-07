#include<TopoDS.hxx>
#include<Standard_TypeDef.hxx>
#include<gp_Pnt.hxx>
#include<BRepPrimAPI_MakeBox.hxx>
#include<BRepPrimAPI_MakeCone.hxx>
#include<BRepPrimAPI_MakeCylinder.hxx>
#include<BRepPrimAPI_MakeSphere.hxx>
#include<BRepPrimAPI_MakeTorus.hxx>
#include<BRepPrimAPI_MakePrism.hxx>
#include<BRepPrimAPI_MakeWedge.hxx>

namespace prim {

	// 创建方体
	TopoDS_Shape make_box(Standard_Real dx, Standard_Real dy, Standard_Real dz) {
		BRepPrimAPI_MakeBox box(dx, dy, dz);
		const TopoDS_Shape&  shape = box.Shape();
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
	TopoDS_Shape make_prism( Standard_Real dx, Standard_Real dy, Standard_Real dz, Standard_Real xmin, Standard_Real zmin, Standard_Real xmax, Standard_Real zmax) {
		BRepPrimAPI_MakeWedge wedge(dx, dy, dz, xmin, zmin, xmax, zmax);
		const TopoDS_Shape& shape = wedge.Shape();
		return shape;
	}

	// 椭圆体 TODO

	// 三角形面




}
