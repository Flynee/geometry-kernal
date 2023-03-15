#include<iostream>
#include<TopoDS.hxx>
#include<gp_Trsf.hxx>
#include<TopLoc_Location.hxx>
#include<BRepBuilderAPI_Transform.hxx>
#include<gp_Vec.hxx>
#include<gp_Mat.hxx>
#include<gp_Ax1.hxx>
#include<gp_Ax2.hxx>
#include<TopoDS.hxx>

namespace transf {

	// 平移
	TopoDS_Shape translate_shape(TopoDS_Shape& shape, const gp_Vec& v) {
		gp_Trsf t;
		t.SetTranslation(v);
		TopLoc_Location loc(t);
		shape.Location(loc, true);

		return shape;
	}

	// 旋转
	TopoDS_Shape rotate_shape(TopoDS_Shape& shape, const gp_Ax1& a1, Standard_Real angel) {
		gp_Trsf t;
		t.SetRotation(a1, angel);
		TopLoc_Location loc(t);
		shape.Move(loc);

		return shape;
	}

	// 缩放
	TopoDS_Shape scale_shape(TopoDS_Shape& shape, const gp_Pnt& p, Standard_Real scale) {
	
		/*gp_Trsf t;
		t.SetScale(p, scale);

		TopLoc_Location loc(t);

		shape.Move(loc); // 此方法有bug
		*/

		gp_Trsf t;
		t.SetScale(p, scale);
		BRepBuilderAPI_Transform bt(shape, t);
		shape = bt.Shape();

		return shape;
	
	}

	// 镜面对称
	TopoDS_Shape mirror_shape(TopoDS_Shape& shape, const gp_Ax2& a2) {
		gp_Trsf t;
		t.SetMirror(a2);
		BRepBuilderAPI_Transform bt(shape, t);
		shape = bt.Shape();

		return shape;
	}

}