#include <vector>
#include <glm/fwd.hpp>
#include "../include/geomtery/poly.h"
#include "graphics/print_config.h"
#include "graphics/svg_printer.h"

void printPolytoSVG()
{
    std::vector<glm::vec2> vertices;
    vertices.push_back(glm::vec2(0, 900));
    vertices.push_back(glm::vec2(600, 900));
    vertices.push_back(glm::vec2(600, 600));
    vertices.push_back(glm::vec2(900, 600));
    vertices.push_back(glm::vec2(900, 0));
    vertices.push_back(glm::vec2(0, 0));
    Polygon poly;
    poly.setVertices(vertices);
    PrintConfig printConfig;
    SvgPrinter svgPrinter;

    svgPrinter.begin(720, 480, 2500, 1800);
    svgPrinter.writePoly(poly);
    svgPrinter.end();
    svgPrinter.exportToFile();
}