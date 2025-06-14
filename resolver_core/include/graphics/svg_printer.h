#pragma once
#include < string>
#include <fstream>
#include <format>
#include "geometry/poly.h"
#include "graphics/print_config.h"
#include "tinyfiledialogs.h"
#include <iostream>
#include <sstream>
#include <geometry/shapes2d.h>
#include <geometry/triangle.h>

class SvgPrinter
{

public:
    void writePoly(Polygon &poly);
    void writeTriangle(const Triangle& triangle);
    void writePoints(std::vector<glm::vec2> &points, int size);
    void writeCircle(const Circle& circle, glm::vec3 color);
    static std::string encodeColor(glm::vec3 color);

    void begin(float width, float height, float vp_width, float vp_height);
    void end()
    {
        buffer << "</svg>";
    }

    void exportToFile();

private:
    std::stringstream buffer;
    PrintConfig printConfig;
};