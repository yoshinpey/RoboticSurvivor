#include "InputManager.h"
#include <fstream>
#include <string>
#include "json.hpp"
#include <iostream>

namespace InputManager
{
	using json = nlohmann::json;
	using Input::IsKey;

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
	void InputManager::Initialize()
	{
		// �ݒ�t�@�C������{�^���̐ݒ��ǂݍ���
		std::ifstream configFile(CONFIG_FILE_PATH);
		if (configFile.is_open())
		{
			json configJson;
			configFile >> configJson;

			// �ݒ��ButtonConfig�\���̂ɓǂݍ���
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
		else
		{
			// �G���[���b�Z�[�W��\��
			std::cerr << "Error: Could not open config file." << std::endl;
		}
	}

	// �{�^���z�u�̃Q�b�^�[
	ButtonConfig GetButtonConfig()
	{
		return buttonConfig;
	}

	bool IsShoot()			{ return Input::IsMouseButtonDown(buttonConfig.MOUSE_LEFT); }
	bool IsWeaponAction()	{ return Input::IsMouseButtonUp(buttonConfig.MOUSE_RIGHT); }

	bool IsMoveForward()	{ return IsKey(buttonConfig.MOVE_FORWARD_KEY); }
	bool IsMoveLeft()		{ return IsKey(buttonConfig.MOVE_LEFT_KEY); }
	bool IsMoveBackward()	{ return IsKey(buttonConfig.MOVE_BACKWARD_KEY); }
	bool IsMoveRight()		{ return IsKey(buttonConfig.MOVE_RIGHT_KEY); }

	bool IsRun()			{ return IsKey(buttonConfig.RUN_KEY); }
	bool IsReload()			{ return IsKey(buttonConfig.RELOAD_KEY); }
	bool IsMenu()			{ return IsKey(buttonConfig.MENU_KEY); }
	bool IsEventAction()	{ return IsKey(buttonConfig.EVENT_ACTION_KEY); }
	bool IsAbility()		{ return IsKey(buttonConfig.ABILITY_KEY); }

	bool IsJump()			{ return Input::IsKeyDown(buttonConfig.JUMP_KEY); }
	bool IsWalk()			{ return IsMoveForward() || IsMoveLeft() || IsMoveBackward() || IsMoveRight(); }
}


