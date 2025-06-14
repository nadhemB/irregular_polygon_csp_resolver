#pragma once
#include "geometry/triangle.h"
#include <glm/fwd.hpp>
#include <glm/gtc/epsilon.hpp>
#include "geometry/edge.h"
#include "maths/math_tools.h"
#include <unordered_set>
#include "maths/hashs.h"

class DelaunayTriangulator
{
public:
    DelaunayTriangulator() = default;
    void insert_vertex(glm::vec2 vertex);
    std::vector<Triangle> triangulate();
    void calculate_super_triangles();
    void clean(); // remove the simplices who has at least one of the super triangles vertices
    std::vector<Triangle> get_cavity(glm::vec2 point);
    std::vector<Edge> get_exterior_edges(std::vector<Triangle>);

    void setVertices(const std::vector<glm::vec2>& vertices) {
        this->vertices = vertices;
    }


    void draw();

private:
    std::unordered_set < Triangle, TriangleHasher> simplices;
    std::vector<glm::vec2> vertices;
    Triangle super_triangles[2];
};
