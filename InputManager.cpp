#include "InputManager.h"
#include <fstream>
#include <string>

namespace InputManager
{

	// �{�^���z�u�̐ݒ�
	struct ButtonConfig
	{
		int MOVE_FORWARD_KEY;
		int MOVE_LEFT_KEY;
		int MOVE_BACKWARD_KEY;
		int MOVE_RIGHT_KEY;
		int JUMP_KEY;
		int RUN_KEY;
		int RELOAD_KEY;
		int MENU_KEY;
		int EVENT_ACTION_KEY;
		int ABILITY_KEY;
		int MOUSE_LEFT;
		int MOUSE_RIGHT;
	};
	// �ݒ�t�@�C���̃p�X
	const char* CONFIG_FILE_PATH = "input_config.json";

	// �{�^���z�u�̐ݒ��ێ�����ϐ�
	ButtonConfig buttonConfig;

	// �������֐�
	void Initialize()
	{
		// �ݒ�t�@�C������{�^���̐ݒ��ǂݍ���
		LoadButtonConfig();
	}


	// �{�^���z�u�̐ݒ��ǂݍ��ފ֐�
	void LoadButtonConfig()
	{
		std::ifstream configFile(CONFIG_FILE_PATH);
		if (configFile.is_open())
		{
			// �ݒ�t�@�C������ JSON �������ǂݍ���
			std::string jsonStr((std::istreambuf_iterator<char>(configFile)), std::istreambuf_iterator<char>());

			// JSON �p�[�X
			nlohmann::json configJson = nlohmann::json::parse(jsonStr);

			// �e�ݒ�� buttonConfig �ɃZ�b�g
			buttonConfig.MOVE_FORWARD_KEY = configJson["MOVE_FORWARD_KEY"];
			buttonConfig.MOVE_LEFT_KEY = configJson["MOVE_LEFT_KEY"];
			buttonConfig.MOVE_BACKWARD_KEY = configJson["MOVE_BACKWARD_KEY"];
			buttonConfig.MOVE_RIGHT_KEY = configJson["MOVE_RIGHT_KEY"];
			buttonConfig.JUMP_KEY = configJson["JUMP_KEY"];
			buttonConfig.RUN_KEY = configJson["RUN_KEY"];
			buttonConfig.RELOAD_KEY = configJson["RELOAD_KEY"];
			buttonConfig.MENU_KEY = configJson["MENU_KEY"];
			buttonConfig.EVENT_ACTION_KEY = configJson["EVENT_ACTION_KEY"];
			buttonConfig.ABILITY_KEY = configJson["ABILITY_KEY"];
			buttonConfig.MOUSE_LEFT = configJson["MOUSE_LEFT"];
			buttonConfig.MOUSE_RIGHT = configJson["MOUSE_RIGHT"];

			configFile.close();
		}
	}
}

namespace InputManager
{
	using Input::IsKey;

	bool IsShoot() { return Input::IsMouseButtonDown(buttonConfig.MOUSE_LEFT); }
	bool IsWeaponAction() { return Input::IsMouseButtonUp(buttonConfig.MOUSE_RIGHT); }

	bool IsMoveForward() { return IsKey(buttonConfig.MOVE_FORWARD_KEY); }
	bool IsMoveLeft() { return IsKey(buttonConfig.MOVE_LEFT_KEY); }
	bool IsMoveBackward() { return IsKey(buttonConfig.MOVE_BACKWARD_KEY); }
	bool IsMoveRight() { return IsKey(buttonConfig.MOVE_RIGHT_KEY); }
	bool IsJump() { return IsKey(buttonConfig.JUMP_KEY); }
	bool IsWalk() { return IsMoveForward() || IsMoveLeft() || IsMoveBackward() || IsMoveRight(); }
	bool IsRun() { return IsKey(buttonConfig.RUN_KEY); }
	bool IsReload() { return IsKey(buttonConfig.RELOAD_KEY); }
	bool IsMenu() { return IsKey(buttonConfig.MENU_KEY); }
	bool IsEventAction() { return IsKey(buttonConfig.EVENT_ACTION_KEY); }
	bool IsAbility() { return IsKey(buttonConfig.ABILITY_KEY); }
}


