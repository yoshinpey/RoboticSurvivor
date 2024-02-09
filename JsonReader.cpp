#include "JsonReader.h"
#include <iostream>
#include <fstream>

JsonReader::JsonReader(const std::string& filename) : filename_(filename) {}

bool JsonReader::loadJsonData() 
{
    std::ifstream file(filename_);
    if (!file.is_open()) 
    {
        std::cerr << "Error: Failed to open file " << filename_ << std::endl;
        return false;
    }

    try 
    {
        file >> jsonData_;
    }
    catch (const std::exception& e) 
    {
        std::cerr << "Error: Failed to parse JSON file " << filename_ << ": " << e.what() << std::endl;
        return false;
    }

    file.close();
    return true;
}

json& JsonReader::getData() 
{
    return jsonData_;
}
