#include "graphics/svg_printer.h"

void SvgPrinter::writePoly(Polygon &poly)
{
    std::string points = "";
    for (auto &point : poly.vertices)
    {
        points += std::format("{},{} ", static_cast<int>(point.x), static_cast<int>(point.y));
    }

    std::string svg = std::format("<polyline points=\"{}\" fill=\"{}\" stroke=\"{}\" />",
                                  points, encodeColor(printConfig.fillColor), encodeColor(printConfig.strokeColor));

    buffer << svg << std::endl;
}



void SvgPrinter::writePoints(std::vector<glm::vec2> &points, int size)
{
    for (auto &point : points)
    {
        buffer << std::format("<circle cx=\" {} \" cy=\" {} \" r=\"{}\" />", static_cast<int>(point.x),
                              static_cast<int>(point.y), size)
               << std::endl;
    }
}
void SvgPrinter::writeCircle(const Circle& circle, glm::vec3 color)
{
    buffer << std::format("<circle cx=\" {} \" cy=\" {} \" r=\"{}\"  stroke=\"{}\" fill=\"none\" />",
        static_cast<int>(circle.center.x),
        static_cast<int>(circle.center.y), static_cast<int>(circle.radius), encodeColor(color))
        << std::endl;
}

void SvgPrinter::writeTriangle(const Triangle& triangle) {
     
     std::string points = "";
     std::vector<glm::vec2>  vertices =  triangle.getVertices();

     for (auto& point : vertices)
     {
         points += std::format("{},{} ", static_cast<int>(point.x), static_cast<int>(point.y));
     }

     std::string svg = std::format("<polyline points=\"{}\" fill=\"{}\" stroke=\"{}\" />",
         points, encodeColor(printConfig.fillColor), encodeColor(printConfig.strokeColor));

     buffer << svg << std::endl;

}

std::string SvgPrinter::encodeColor(glm::vec3 color)
{
    float r = std::clamp(color.r, 0.0f, 1.0f);
    float g = std::clamp(color.g, 0.0f, 1.0f);
    float b = std::clamp(color.b, 0.0f, 1.0f);

    // Convert to 0-255 range
    int ri = static_cast<int>(r * 255.0f + 0.5f);
    int gi = static_cast<int>(g * 255.0f + 0.5f);
    int bi = static_cast<int>(b * 255.0f + 0.5f);

    return std::format("#{:02X}{:02X}{:02X}", ri, gi, bi);
}

void SvgPrinter::begin(float width, float height, float vp_width, float vp_height)
{
    std::string header = std::format(
        "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"{}\" height=\"{}\" viewBox=\"0 0 {} {}\">",
        static_cast<int>(width),
        static_cast<int>(height),
        static_cast<int>(vp_width),
        static_cast<int>(vp_height));
    buffer << header << std::endl;
}

void SvgPrinter::exportToFile()
{
    const char *filters[] = {"*.svg"};
    const char *path = tinyfd_saveFileDialog(
        "Save SVG File", "output.svg", 1, filters, "SVG files (*.svg)");

    if (path)
    {
        std::ofstream file(path);

        // If file already exists, user will be warned by OS.
        if (file.is_open())
        {
            std::string content = buffer.str();
            file << content;
            file.close();
        }
    }
    else
    {
        std::cerr << "Save dialog canceled by user.\n";
    }
}
