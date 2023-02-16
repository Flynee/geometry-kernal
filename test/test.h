#ifndef __TEST_H__
#define __TEST_H__

namespace test {

	void make_box();
	void make_cone();
	void make_cylinder();
	void make_sphere();
	void make_torus();
	void make_prism();

	void make_circle_panel();
	void make_ellipse_panel();
	void make_triangle_panel();
	void make_rectangle_panel();
	void make_polygon_panel();
	void make_paraboloid_panel();

	void make_segment();
	void make_polyline();
	void make_circle();
	void make_ellipse();
	void make_besizer_curve();
	void make_parabola();
	void make_hyperbola();
	
	void bool_box();
	void transform_shape();
	void rotate_shape();
	void scale_shape();
	void mirror_shape();

	void copy_shape();
	void boolean_union_shape();
	void boolean_intersection_shape();
	void boolean_cut_shape();

	void shape_add();
	void shape_split();
	void get_shape_bbox();
	void linear_sweep_edge2face();
	void linear_sweep_face2solid();
	void rotate_sweep_edge2face();
	void rotate_sweep_face2solid();
	void path_sweep_edge2face();
	void path_sweep_face2solid();

}


#endif // !__TEST_H__

