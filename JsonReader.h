#include "picojson.h"
#include <fstream>
#include <iostream>


template<typename T>
bool LoadDataFromJson(const std::string& filename, const std::string& key, T& data) 
{
    std::ifstream ifs(filename);
    if (!ifs.is_open()) 
    {
        std::cerr << "JSONファイルを開けませんでした。" << std::endl;
        return false;
    }

    picojson::value json_value;
    ifs >> json_value;

    std::string err = picojson::get_last_error();
    if (!err.empty()) 
    {
        std::cerr << "JSONパースエラー: " << err << std::endl;
        return false;
    }

    const picojson::value& value = json_value.get(key);
    if (value.is<T>()) 
    {
        data = value.get<T>();
        return true;
    }

    else 
    {
        std::cerr << "指定されたキーに対するデータが見つかりませんでした。" << std::endl;
        return false;
    }
}