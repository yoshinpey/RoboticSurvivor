#pragma once
#include <string>
#include "json.hpp"

using json = nlohmann::json;

// jsonデータを読み取るクラス
class JsonReader 
{
private:
    std::string filename_;
    json jsonData_;

public:
    JsonReader(const std::string& filename);
    bool loadJsonData();
    json& getData();
};
