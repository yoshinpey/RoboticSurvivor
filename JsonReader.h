#include <string>
#include "json.hpp"

namespace JsonReader
{
	// �t�@�C����
	std::string fileName_;

	// JSON�f�[�^
	nlohmann::json data_;

	// JSON�t�@�C���̓ǂݍ���
	void Load(const std::string& filename);

	// JSON�t�@�C���ւ̏�������
	void Save(const std::string& filename);

	// JSON�f�[�^�̎擾
	const nlohmann::json& GetData() { return data_; };

	// JSON�f�[�^�̕ύX
	void SetData(const nlohmann::json& data) { data_ = data; };
};