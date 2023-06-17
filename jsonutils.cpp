#include "jsonutils.h"
#include "logging.h"
#include <fstream>

// ================================================================================================================================
JsonUtils* JsonUtils::create()
{
    return new JsonUtils();
}
// ================================================================================================================================
JsonUtils* JsonUtils::create(std::string path)
{  
    JsonUtils* ret = new JsonUtils();
    if (ret->readFromFile(path)) {
        return ret;
    } else {
        delete ret;
        return nullptr;
    }
}
// ================================================================================================================================
bool JsonUtils::readFromFile(std::string filePath)
{
    std::ifstream file(filePath);
    if (not file.is_open())
        return false;
    try {
        boost::property_tree::read_json(file, json);
        file.close();
        return true;
    } catch (const boost::property_tree::ptree_error& e) {
        SLog()->logCL("JSON: error parsing file");
        return false;
    }

}
// ================================================================================================================================
std::string JsonUtils::getValue(std::string paramPath)
{
    return json.get<std::string>(paramPath);
}
// ================================================================================================================================
JsonUtils::JsonUtils()
{

}
// ================================================================================================================================
