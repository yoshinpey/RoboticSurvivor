#include "jsonReader.h"

#include <fstream>

namespace JsonReader
{
    // JSON�t�@�C���̓ǂݍ���
    void Load(const std::string& filename)
    {
        fileName_ = filename + ".json";
        std::ifstream ifs(fileName_);

        if (!ifs.is_open()) assert(data_ >= 0);

        ifs >> data_;
    }

    // JSON�t�@�C���ւ̏�������
    void Save(const std::string& filename)
    {
        fileName_ = filename + ".json";
        std::ofstream ofs(fileName_);

        if (!ofs.is_open()) assert(data_ >= 0);

        ofs << data_;
    }

}