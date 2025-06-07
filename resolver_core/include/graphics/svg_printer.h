#pragma once
#include < string>
#include <fstream>
#include <format>
#include "geomtery/poly.h"
#include "graphics/print_config.h"
#include "tinyfiledialogs.h"
#include <iostream>
#include <sstream>

class SvgPrinter
{

public:
    void writePoly(Polygon &poly);
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