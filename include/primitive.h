#ifndef PRIMITIVE_H
#define PRIMITIVE_H

namespace prim {
	
	// Με
	TopoDS_Shape make_box(Standard_Real dx, Standard_Real dy, Standard_Real dz);
	TopoDS_Shape make_cone(Standard_Real r1, Standard_Real r2, Standard_Real h);
	TopoDS_Shape make_cylinder(Standard_Real r, Standard_Real h);
	TopoDS_Shape make_sphere(Standard_Real r);
	TopoDS_Shape make_torus(Standard_Real r1, Standard_Real r2);
	TopoDS_Shape make_prism(Standard_Real dx, Standard_Real dy, Standard_Real dz, Standard_Real xmin, Standard_Real zmin, Standard_Real xmax, Standard_Real zmax);
}

#endif
