#include "maths/math_tools.h"


glm::vec2 math::lineIntersection(const Ray& r1, const Ray& r2) {
    glm::vec3 c0 = glm::vec3(r1.dir, 0);
    glm::vec3 c1 = glm::vec3(-r2.dir, 0);
    glm::vec3 c2 = glm::vec3(0, 0, 1);
    glm::vec3 B = glm::vec3(r2.origin - r1.origin, 0);
    glm::mat3 A = glm::mat3(c0, c1, c2);
    glm::vec3 X = glm::inverse(A) * B;
    float t = X.x;
    return r1.origin + t * r1.dir;
}


int math::random_int(int min, int max) {
    // Static to keep the generator seeded once
    static std::random_device rd;  // Seed source
    static std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}

glm::vec2* math::calculate_boundaries(std::vector<glm::vec2> points) {
    glm::vec2 min = points[0];
    glm::vec2 max = points[0];
    for (int i = 1; i < points.size(); i++) {
        glm::vec2 pointX = points[i];
        if (pointX.x < min.x) {
            min.x = pointX.x;
        }
        if (pointX.y < min.y) {
            min.y = pointX.y;
        }

        if (pointX.x > max.x) {
            max.x = pointX.x;
        }
        if (pointX.y > max.y) {
            max.y = pointX.y;
        }

    }
    glm::vec2 boundaries[] = { min, max };
    return boundaries;
}


glm::vec2 math::project(glm::vec2 point, glm::vec2 a, glm::vec2 b) {
    glm::vec2 ap = point - a;
    glm::vec2 ab = b - a;
    glm::vec2 pr = a + glm::dot(ap, ab) / glm::length(ab) * glm::normalize(ab);
    return pr;
}

std::vector<glm::vec2> math::order(std::vector<glm::vec2> list) {
    //find smallest vertex
    int startIndex = 0;
    glm::vec2 startPoint = list[0];
    for (int i = 1; i < list.size(); i++) {
        auto current = list[i];
        float diff = current.x - startPoint.x;
        if (diff < -1e-6) {
            startPoint = current;
            startIndex = i;
        }
        else if (std::abs(diff) < 1e-6) {
            float yDiff = current.y - startPoint.y;
            if (yDiff < -1e-6) {
                startIndex = i;
                startPoint = current;
            }
        }
    }
    //rotate
    std::vector<glm::vec2> orderedList;
    for (int i = 0; i < list.size(); i++) {
        int index = (startIndex + i) % list.size();
        orderedList.push_back(list[index]);
    }
    return orderedList;
}

bool math::verticesEquality(const std::vector<glm::vec2>& vertices0, const std::vector<glm::vec2>& vertices1)
{
    if (vertices0.size() != vertices1.size())
        return false;
    bool equal = true;
    std::vector<glm::vec2> ordered0 = math::order(vertices0);
    std::vector<glm::vec2> reversed = std::vector<glm::vec2>(vertices0.begin(), vertices0.end());
    reversed = math::order(reversed);
    std::reverse(reversed.begin(), reversed.end());
    std::vector<glm::vec2> ordered1 = math::order(vertices1);

    for (int i = 0; i < ordered0.size(); i++) {
        glm::bvec2 comp = glm::epsilonEqual(ordered0[i], ordered1[i], static_cast<float>(1e-6));
        if (!comp.x || !comp.y) {
            equal = false;
            break;
        }
    }
    if (!equal) {
        equal = true;
        for (int i = 0; i < ordered0.size(); i++) {
            glm::bvec2 comp = glm::epsilonEqual(reversed[i], ordered1[i], static_cast<float>(1e-6));
            if (!comp.x || !comp.y) {
                equal = false;
                break;
            }
        }
    }
    return equal;
}
