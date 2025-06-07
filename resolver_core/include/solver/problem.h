#pragma once
#include <glm/vec2.hpp>
#include <vector>
#include "geomtery/poly.h"
#include "io/json_adapter.h"

class Problem : public Serializable
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

    void fromJSON(const std::string &jsonStr) override
    {
        pieces.clear();
        auto j = nlohmann::json::parse(jsonStr);
        j.at("panel").get_to(panel);

        for (const auto &item : j["pieces"])
        {

            Polygon poly;
            poly.fromJSON(item["vertices"].dump());
            int count = item["count"];
            for (int i = 0; i < count; i++)
                pieces.push_back(Polygon(poly));
        }
    }

    std::vector<Polygon> getPieces() const
    {
        return pieces;
    }

private:
    glm::vec2 panel;
    std::vector<Polygon> pieces;
};