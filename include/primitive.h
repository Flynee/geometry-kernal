#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__
#include<TopoDS.hxx>
#include<Standard_TypeDef.hxx>
#include<TColgp_Array1OfPnt.hxx>
#include<gp_Pnt.hxx>

namespace prim {
	
		// Ìå
		TopoDS_Shape make_box(Standard_Real dx, Standard_Real dy, Standard_Real dz);
		TopoDS_Shape make_cone(Standard_Real r1, Standard_Real r2, Standard_Real h);
		TopoDS_Shape make_cylinder(Standard_Real r, Standard_Real h);
		TopoDS_Shape make_sphere(Standard_Real r);
		TopoDS_Shape make_torus(Standard_Real r1, Standard_Real r2);
		TopoDS_Shape make_prism(Standard_Real dx, Standard_Real dy, Standard_Real dz, Standard_Real xmin, Standard_Real zmin, Standard_Real xmax, Standard_Real zmax);



		// Ãæ
		TopoDS_Shape make_triangle_panel(const gp_Pnt& p1, const gp_Pnt& p2, const gp_Pnt& p3);
		TopoDS_Shape make_rectangle_panel(const gp_Pnt& p1, const gp_Pnt& p2, const gp_Pnt& p3, const gp_Pnt& p4);
		TopoDS_Shape make_circle_panel(Standard_Real r);
		TopoDS_Shape make_ellipse_panel(Standard_Real r1, Standard_Real r2);
		TopoDS_Shape make_polygon_panel(const gp_Pnt pt[], int size);
		TopoDS_Shape make_paraboloid_panel(Standard_Real min, Standard_Real max, Standard_Real f);

		// Ïß
		TopoDS_Shape make_segment(const gp_Pnt& p1, const gp_Pnt& p2);
		TopoDS_Shape make_polyline(const gp_Pnt list[], int size);
		TopoDS_Shape make_circle(Standard_Real r);
		TopoDS_Shape  make_ellipse(Standard_Real r1, Standard_Real r2);
		TopoDS_Shape make_bezier_curve(const TColgp_Array1OfPnt& list);
		TopoDS_Shape make_parabola(Standard_Real min, Standard_Real max, Standard_Real f);
		TopoDS_Shape make_hyperbola(Standard_Real major, Standard_Real minor, Standard_Real min, Standard_Real max);
}

#endif // !__PRIMITIVE_H__
