#pragma once

#include <string>

class Serializable
{
public:
    virtual ~Serializable() = default;
    virtual std::string toJsonString() const = 0;
    virtual void fromJSON(const std::string &json) = 0;
};