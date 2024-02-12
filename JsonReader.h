#include "picojson.h"
#include <fstream>
#include <iostream>


template<typename T>
bool LoadDataFromJson(const std::string& filename, const std::string& key, T& data) 
{
    std::ifstream ifs(filename);
    if (!ifs.is_open()) 
    {
        std::cerr << "JSON�t�@�C�����J���܂���ł����B" << std::endl;
        return false;
    }

    picojson::value json_value;
    ifs >> json_value;

    std::string err = picojson::get_last_error();
    if (!err.empty()) 
    {
        std::cerr << "JSON�p�[�X�G���[: " << err << std::endl;
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
        std::cerr << "�w�肳�ꂽ�L�[�ɑ΂���f�[�^��������܂���ł����B" << std::endl;
        return false;
    }
}