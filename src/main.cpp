#include<iostream>
#include<TopoDS.hxx>
#include<BRepTools.hxx>

#include"primitive.h"

int main() {

    std::cout<<"SYSTEM IS RUNNING..."<<std::endl;

    // ²âÊÔ´´½¨
    const TopoDS_Shape& shape = prim::make_prism(1.0, 2.0, 1.0, 0.5, 0.5, 0.5, 0.5);

    BRepTools::Write(shape, "../shape.brep");

    return 0;

}