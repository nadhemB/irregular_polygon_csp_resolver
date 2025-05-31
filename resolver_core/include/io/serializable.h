#pragma once

template <typename T>
class Serializable
{
public:
    virtual std::string toJsonString() const = 0;
    virtual T fromJSON(std::string json) = 0;
};