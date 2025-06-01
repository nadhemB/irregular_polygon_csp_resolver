#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include "geomtery/poly.h"
#include "io/json_adapter.h"

class Problem : public Serializable<Problem>
{

public:
    Problem() = default;

    Problem(glm::vec2 panel, std::vector<Polygon> pieces) : panel(panel), pieces(pieces) {}
    std::string toJsonString() const override
    {
        nlohmann::json j;
        j["panel"] = panel;

        std::vector<nlohmann::json> jsonPieces;
        for (const auto &piece : pieces)
        {
            jsonPieces.push_back(nlohmann::json::parse(piece.toJsonString()));
        }
        j["pieces"] = jsonPieces;

        return j.dump(4); // pretty print
    }

    Problem &fromJSON(std::string jsonStr) override
    {
        auto j = nlohmann::json::parse(jsonStr);
        j.at("panel").get_to(panel);

        for (const auto &item : j["pieces"])
        {
            Polygon poly;
            poly = poly.fromJSON(item.dump());
            pieces.push_back(poly);
        }

        return *this;
    }

private:
    glm::vec2 panel;
    std::vector<Polygon> pieces;
};