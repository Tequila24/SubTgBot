#pragma once

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "StringUtils.h"

class JsonUtils
{
public:
    static JsonUtils* create();
    static JsonUtils* create(std::string path);

    bool readFromFile(std::string filePath);

    std::string getValue(std::string paramPath);

protected:
    JsonUtils();

    boost::property_tree::ptree json;
};
