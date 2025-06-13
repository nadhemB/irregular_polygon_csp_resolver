#include "maths/delaunay_triangulator.h"


std::vector<Triangle> DelaunayTriangulator::get_cavity(glm::vec2 point)
{
    std::vector<Triangle> cavity;
    auto iterator = this->simplices.begin();
    while (iterator != this->simplices.end())
    {
        Triangle triangle = *iterator;
        if (triangle.circumCircle().contains(point))
        {
            cavity.push_back(triangle);
        }
        iterator++;
    }
    return cavity;
}

void DelaunayTriangulator::insert_vertex(glm::vec2 vertex)
{
    auto cavity = get_cavity(vertex);
    auto exterior_edges = get_exterior_edges(cavity);
    //construct the ball
    for (int i = 0; i < exterior_edges.size(); i++) {
        Edge edge = exterior_edges[i];
        Triangle triangle = Triangle(vertex, edge.getV0(), edge.getV1());
        simplices.push_back(triangle);
    }
    //remove the cavity
    for (int i = 0; i < cavity.size(); i++) {
        Triangle triangle = cavity[i];
        //simplices.erase(triangle);
    }
}

void DelaunayTriangulator::triangulate()
{
    simplices.clear();
    calculate_super_triangles();
    auto iter = vertices.begin();
    while (iter != vertices.end()) {
        glm::vec3 vertex = *iter;
        insert_vertex(vertex);
        iter++;
    }
    clean();
}

void DelaunayTriangulator::calculate_super_triangles()
{
    std::vector<glm::vec2> cloud;
    cloud.assign(vertices.begin(), vertices.end());

    glm::vec2* boundaries = math::calculate_boundaries(cloud);
    glm::vec2 lower_bound = boundaries[0];
    glm::vec2 higher_bound = boundaries[1];
    glm::vec2 center = (lower_bound + higher_bound) / 2.0f;
    glm::vec2 dimensions = (higher_bound - lower_bound) / 2.0f;
    dimensions *= 1.1f;// to make sure all points lie strictly inside the super trangles

    //glm::vec2 v0 = center + dimensions;
    //glm::vec2 v1 = center + glm::vec3(-dimensions.x, dimensions.y, 0.0f);
    //glm::vec2 v2 = center - dimensions;
    //glm::vec2 v3 = center + glm::vec3(dimensions.x, -dimensions.y, 0.0f);

    //Triangle t1 = Triangle(v0, v1, v2);
    //Triangle t2 = Triangle(v0, v2, v3);
    //petform edge swap if necessary
    //if (t1.get_circum_circle().contains(v3)) {
    //    t1 = Triangle(v0, v1, v3);
    //    t2 = Triangle(v1, v2, v3);
    //}
    //simplices.insert(t1);
    //simplices.insert(t2);
    //super_triangles[0] = t1;
    //super_triangles[1] = t2;
}

void DelaunayTriangulator::clean()
{
}

std::vector<Edge> DelaunayTriangulator::get_exterior_edges(std::vector<Triangle>)
{
    return std::vector<Edge>();
}
