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
        simplices.insert(triangle);
    }
    //remove the cavity
    for (int i = 0; i < cavity.size(); i++) {
        Triangle triangle = cavity[i];
        simplices.erase(triangle);
    }
}

std::vector<Triangle> DelaunayTriangulator::triangulate()
{
    simplices.clear();
    calculate_super_triangles();
    auto iter = vertices.begin();
    while (iter != vertices.end()) {
        glm::vec2 vertex = *iter;
        insert_vertex(vertex);
        iter++;
    }
    clean();
   
    return std::vector<Triangle>(simplices.begin(), simplices.end()) ;
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

    glm::vec2 v0 = center + dimensions;
    glm::vec2 v1 = center + glm::vec2(-dimensions.x, dimensions.y);
    glm::vec2 v2 = center - dimensions;
    glm::vec2 v3 = center + glm::vec2(dimensions.x, -dimensions.y);

    Triangle t1 = Triangle(v0, v1, v2);
    Triangle t2 = Triangle(v0, v2, v3);
    //petform edge swap if necessary
    if (t1.circumCircle().contains(v3)) {
        t1 = Triangle(v0, v1, v3);
        t2 = Triangle(v1, v2, v3);
    }
    simplices.insert(t1);
    simplices.insert(t2);
    super_triangles[0] = t1;
    super_triangles[1] = t2;
}

void DelaunayTriangulator::clean()
{
    std::vector<glm::vec2> super_triangles_vertices;
    super_triangles_vertices.push_back(super_triangles[0].v0());
    super_triangles_vertices.push_back(super_triangles[0].v1() );
    super_triangles_vertices.push_back(super_triangles[0].v2() );
    super_triangles_vertices.push_back(super_triangles[1].v0());
    super_triangles_vertices.push_back(super_triangles[1].v1());
    super_triangles_vertices.push_back(super_triangles[1].v2());
    auto iter = simplices.begin();
    std::vector<Triangle> triangles_to_delete;
    while (iter != simplices.end()) {
        for (int i = 0; i < super_triangles_vertices.size(); i++) {
            auto v0check = glm::epsilonEqual(super_triangles_vertices[i], iter->v0(), 0.001f);
            auto v1check = glm::epsilonEqual(super_triangles_vertices[i], iter->v1(), 0.001f);
            auto v2check = glm::epsilonEqual(super_triangles_vertices[i], iter->v2(), 0.001f);

            if (((v0check == glm::bvec2(true)) || (v1check == glm::bvec2(true)))
                || (v2check == glm::bvec2(true))) {
                triangles_to_delete.push_back(*iter);
                break;
            }
        }
        iter++;

    }
    for (int i = 0; i < triangles_to_delete.size(); i++) {
        simplices.erase(triangles_to_delete[i]);
    }

}

std::vector<Edge> DelaunayTriangulator::get_exterior_edges(std::vector<Triangle> triangles)
{
    std::unordered_set<Edge, EdgeHasher> exterior_edges;
    std::unordered_set<Edge, EdgeHasher> shared_edges;
    for (int i = 0; i < triangles.size(); i++)
    {
        auto triangle_edges = triangles[i].getEdges();
        for (int i = 0; i < 3; i++) {
            if (shared_edges.find(triangle_edges[i]) != shared_edges.end()) {
                continue;
            }
            else {
                auto exterior = exterior_edges.find(triangle_edges[i]);
                if (exterior == exterior_edges.end()) {
                    exterior_edges.insert(triangle_edges[i]);
                }
                else {
                    shared_edges.insert(triangle_edges[i]);
                    exterior_edges.erase(exterior);
                }
            }
        }
    }
    std::vector<Edge> vector;
    vector.assign(exterior_edges.begin(), exterior_edges.end());
    return vector;
}
