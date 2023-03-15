#ifndef __TOOL_H__
#define __TOOL_H__
#include<TopoDS.hxx>
#include<BndLib.hxx>
#include<TopTools_ListOfShape.hxx>
#include<gp_Dir.hxx>
#include<GeomFill_Trihedron.hxx>
#include<map>
#include<vector>

namespace tool {

	TopoDS_Shape copy_shape(const TopoDS_Shape& shape, const bool copyGeom = true, const bool copyMesh = false);
	Bnd_Box get_shape_bbox(const TopoDS_Shape& shape);
	TopoDS_Shape boolean_union_shape(const TopoDS_Shape& shape, const TopoDS_Shape& shape2);
	TopoDS_Shape boolean_intersection_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2);
	TopoDS_Shape boolean_cut_shape(const TopoDS_Shape& shape1, const TopoDS_Shape& shape2);
	TopoDS_Shape shape_add(const TopTools_ListOfShape& shpaeList);
	TopoDS_Shape shape_split(const TopTools_ListOfShape& shapes, const TopTools_ListOfShape& tools);
	TopoDS_Shape linear_sweep(TopoDS_Shape& shape, const gp_Vec& v);
	TopoDS_Shape rotate_sweep(const TopoDS_Shape& s, const gp_Ax1& ax1, const Standard_Real angle);
	TopoDS_Shape path_sweep(const TopoDS_Wire& w, const TopoDS_Shape& s, const GeomFill_Trihedron m = GeomFill_Trihedron::GeomFill_IsDiscreteTrihedron);
	TopoDS_Shape line_connect2face(const TopoDS_Edge& e1, TopoDS_Edge& e2);
	TopoDS_Shape fill_closure_edge2face(const TopoDS_Edge list[], int size);
	TopoDS_Shape shape_line_array(TopoDS_Shape& shape,
		int x_num = 1, int y_num = 1, int z_num = 1,
		const Standard_Real dx = 0, const Standard_Real dy = 0, const Standard_Real dz = 0, bool link = true);
	std::map<int, std::map<int, std::vector<int>>> analyze_topo(const TopoDS_Shape& shape);
	TopoDS_Shape shape_sphere_array(TopoDS_Shape& shape,
		Standard_Real x, Standard_Real y, Standard_Real z, Standard_Real r,
		Standard_Real x_num, Standard_Real y_num, Standard_Real z_num,
		Standard_Real dx, Standard_Real dy, Standard_Real dz);
}

#endif // !__TOOL_H__
