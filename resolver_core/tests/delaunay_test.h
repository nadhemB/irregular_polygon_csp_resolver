#pragma once
#include "maths/math_tools.h"
#include "graphics/svg_printer.h"
#include <geometry/triangle.h>
#include <maths/delaunay_triangulator.h>

void delaunayTest()
{
    std::vector<glm::vec2> points;
    for (int i = 0; i < 100; i++)
    {
        int x = math::random_int(0, 1000);
        int y = math::random_int(0, 1000);
        points.push_back(glm::vec2(x, y));
    }

    DelaunayTriangulator dt;
    dt.setVertices(points);
    auto triangulation = dt.triangulate();
    

    SvgPrinter svgPrinter;
    //svgPrinter.begin(720, 480, 2500, 1800);
    //svgPrinter.writePoints(points, 5);
    //svgPrinter.end();
    //svgPrinter.exportToFile();
    //Triangle tr = Triangle(points[0], points[1], points[2]);
    //Circle innercircle = tr.innerCicrcle();
    //Circle circumCircle = tr.circumCircle();
    //Polygon poly(points);


    svgPrinter.begin(720, 480, 2500, 1800);
    for (const auto& t : triangulation) {
        svgPrinter.writeTriangle(t);
    }


    svgPrinter.end();
    svgPrinter.exportToFile();

}
