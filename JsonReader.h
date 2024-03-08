#include <string>
#include "json.hpp"

namespace JsonReader
{
	// ファイル名
	std::string fileName_;

	// JSONデータ
	nlohmann::json data_;

	// JSONファイルの読み込み
	void Load(const std::string& filename);

	// JSONファイルへの書き込み
	void Save(const std::string& filename);

	// JSONデータの取得
	const nlohmann::json& GetData() { return data_; };

	// JSONデータの変更
	void SetData(const nlohmann::json& data) { data_ = data; };
};