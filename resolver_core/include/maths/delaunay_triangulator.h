#pragma once
#include "geometry/triangle.h"
#include <glm/fwd.hpp>
#include "geometry/edge.h"
#include "maths/math_tools.h"

class DelaunayTriangulator
{
public:
    DelaunayTriangulator() = default;
    void insert_vertex(glm::vec2 vertex);
    void triangulate();
    void calculate_super_triangles();
    void clean(); // remove the simplices who has at least one of the super triangles vertices
    std::vector<Triangle> get_cavity(glm::vec2 point);
    std::vector<Edge> get_exterior_edges(std::vector<Triangle>);

    void draw();

private:
    std::vector<Triangle> simplices;
    std::vector<Triangle> simplices_vector;
    std::vector<glm::vec3> vertices;
    Triangle super_triangles[2];
};
