#include <Windows.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

//�G���W���֘A�̃f�[�^
#include "Global.h"
#include "RootObject.h"
#include "Model.h"
#include "Image.h"
#include "Camera.h"
#include "Input.h"
#include "Audio.h"
#include "VFX.h"

//ImGui�֘A�̃f�[�^
#ifdef _DEBUG
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#endif

//#include "../GameManager.h"
#include "GameObject.h"

#pragma comment(lib,"Winmm.lib")

//�萔�錾
const char* WIN_CLASS_NAME = "SampleGame";	//�E�B���h�E�N���X��
class GameObject;
int fpsLimit;
static bool isPaused = false;			// �|�[�Y��

//�v���g�^�C�v�錾
HWND InitApp(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void LimitMousePointer(HWND hwnd);
void ReleaseMousePointer();

#ifdef _DEBUG
//ImGui�ɃE�B���h�E�v���V�[�W���\��������擾����֐�
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

// �G���g���[�|�C���g
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ����������
	srand((unsigned)time(NULL));

	//�@���ݒn���A�Z�b�g�t�H���_�ɐݒ�
	SetCurrentDirectory("Assets");

	int screenWidth;		//�X�N���[���̕�
	int screenHeight;		//�X�N���[���̍���

	//�������t�@�C���isetup.ini�j����K�v�ȏ����擾
	fpsLimit = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");				//FPS�i��ʍX�V���x�j
	int isDrawFps = GetPrivateProfileInt("DEBUG", "ViewFps", 0, ".\\setup.ini");		//�L���v�V�����Ɍ��݂�FPS��\�����邩�ǂ���
#ifdef _DEBUG
	screenWidth = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");			//�X�N���[���̕�
	screenHeight = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");		//�X�N���[���̍���
#else
	// �E�B���h�E���f�B�X�v���C�T�C�Y�ɍ��킹��
	screenWidth = GetSystemMetrics(SM_CXSCREEN) - 16;		//�X�N���[���̕�
	screenHeight = GetSystemMetrics(SM_CYSCREEN) - 40;		//�X�N���[���̍���
#endif

	//�E�B���h�E���쐬
	HWND hWnd = InitApp(hInstance, screenWidth, screenHeight, nCmdShow);

	//Direct3D����
	Direct3D::Initialize(hWnd, screenWidth, screenHeight);

#ifdef _DEBUG
	//ImGui��������
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(Direct3D::pDevice_, Direct3D::pContext_);
#endif

	//�J����������
	Camera::Initialize();

	//���͏����i�L�[�{�[�h�A�}�E�X�A�R���g���[���[�j�̏���
	Input::Initialize(hWnd);

	//�I�[�f�B�I�i���ʉ��j�̏���
	Audio::Initialize();

	//�Q�[���}�l�[�W���[������
	//GameManager::Initialize();

	//���[�g�I�u�W�F�N�g����
	//���ׂẴQ�[���I�u�W�F�N�g�̐e�ƂȂ�I�u�W�F�N�g
	RootObject* pRootObject = new RootObject;
	pRootObject->Initialize();


	//���b�Z�[�W���[�v�i�����N����̂�҂j
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//���b�Z�[�W����i���������D��j
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//���b�Z�[�W�Ȃ��i�����ŃQ�[���̏����j
		else
		{
			// �|�[�Y���̓��[�v�������Ȃ�
			if (isPaused)continue;

			//���Ԍv��
			timeBeginPeriod(1);	//���Ԍv���̐��x���グ��
			static int FPS = 0;								//��ʍX�V�񐔂̃J�E���^
			static DWORD lastFpsResetTime = timeGetTime();	//�Ō�ɃL���v�V������FPS��\������
			static DWORD lastUpdateTime = timeGetTime();	//�Ō�ɉ�ʂ��X�V��������
			DWORD nowTime = timeGetTime();					//���݂̎���

			//�L���v�V�����Ɍ��݂�FPS��\������
			if (isDrawFps)
			{
				//1�b�i1000�~���b�j�o������
				if (nowTime - lastFpsResetTime > 1000)
				{
					//FPS�̒l��\��
					char string[16];
					wsprintf(string, "FPS:%d", FPS);
					SetWindowText(GetActiveWindow(), string);
					FPS = 0;
					lastFpsResetTime = nowTime;
				}
			}


			//�w�肵�����ԁiFPS��60�ɐݒ肵���ꍇ��60����1�b�j�o�߂��Ă�����X�V����
			if ((nowTime - lastUpdateTime) * fpsLimit > 1000.0f)
			{
				//���Ԍv���֘A
				lastUpdateTime = nowTime;	//���݂̎��ԁi�Ō�ɉ�ʂ��X�V�������ԁj���o���Ă���
				FPS++;						//��ʍX�V�񐔂��J�E���g����
#ifdef _DEBUG
				//ImGui�̍X�V����
				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();

				ImGui::NewFrame();
				//ImGui::Begin("Hello");//ImGui�̏������J�n
				//{
				//	//�`�悳���{�^������������...
				//	if (ImGui::Button("button")) {
				//		PostQuitMessage(0);	//�v���O�����I��
				//	}
				//}
				//ImGui::End();//ImGui�̏������I��
#endif

				//���́i�L�[�{�[�h�A�}�E�X�A�R���g���[���[�j�����X�V
				Input::Update();

				//�Q�[���}�l�[�W���[�X�V
				//GameManager::Update();

				//�S�I�u�W�F�N�g�̍X�V����
				//���[�g�I�u�W�F�N�g��Update���Ă񂾂��ƁA�����I�Ɏq�A����Update���Ă΂��
				pRootObject->UpdateSub();

				//�J�������X�V
				Camera::Update();

				//�G�t�F�N�g�̍X�V
				VFX::Update();

				//���̃t���[���̕`��J�n
				Direct3D::BeginDraw();

				//�S�I�u�W�F�N�g��`��
				//���[�g�I�u�W�F�N�g��Draw���Ă񂾂��ƁA�����I�Ɏq�A����Update���Ă΂��
				pRootObject->DrawSub();

				//�G�t�F�N�g�̕`��
				VFX::Draw();

				//�`�揈���̑O�ɋL�q
#ifdef _DEBUG
				ImGui::Render();
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
				//�`��I��
				Direct3D::EndDraw();



				
				//������Ƌx�܂���
				Sleep(1);
			}
			timeEndPeriod(1);	//���Ԍv���̐��x��߂�
		}
	}

	

	//���낢����
	VFX::Release();
	Audio::AllRelease();
	Model::AllRelease();
	Image::AllRelease();
	//GameManager::Release();
	pRootObject->ReleaseSub();
	SAFE_DELETE(pRootObject);

	//ImGui�̊J������
#ifdef _DEBUG
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
#endif
	Direct3D::Release();

	return 0;
}


//�E�B���h�E�̍쐬
HWND InitApp(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow)
{
	//�E�B���h�E�N���X�i�݌v�}�j���쐬
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);					//���̍\���̂̃T�C�Y
	wc.hInstance = hInstance;						//�C���X�^���X�n���h��
	wc.lpszClassName = WIN_CLASS_NAME;				//�E�B���h�E�N���X��
	wc.lpfnWndProc = WndProc;						//�E�B���h�E�v���V�[�W��
	wc.style = CS_VREDRAW | CS_HREDRAW;				//�X�^�C���i�f�t�H���g�j
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);	//�A�C�R��
	wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);	//�������A�C�R��
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	//�}�E�X�J�[�\��
	wc.lpszMenuName = nullptr;						//���j���[�i�Ȃ��j
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//�w�i�i���j
	RegisterClassEx(&wc);

	//�E�B���h�E�T�C�Y�̌v�Z
	RECT winRect = { 0, 0, screenWidth, screenHeight };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);

	//�^�C�g���o�[�ɕ\��������e
	char caption[64];
	GetPrivateProfileString("SCREEN", "Caption", "***", caption, 64, ".\\setup.ini");

#ifdef _DEBUG
	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,						//�E�B���h�E�N���X��
		caption,							//�^�C�g���o�[�ɕ\��������e
		WS_OVERLAPPEDWINDOW,				//�X�^�C���i���ʂ̃E�B���h�E WS_OVERLAPPEDWINDOW�j�t���ɂ������Ƃ� WS_POPUP | WS_VISIBLE
		CW_USEDEFAULT,						//�\���ʒu���i���܂����j
		CW_USEDEFAULT,						//�\���ʒu��i���܂����j
		winRect.right - winRect.left,		//�E�B���h�E��
		winRect.bottom - winRect.top,		//�E�B���h�E����
		nullptr,							//�e�E�C���h�E�i�Ȃ��j
		nullptr,							//���j���[�i�Ȃ��j
		hInstance,							//�C���X�^���X
		nullptr								//�p�����[�^�i�Ȃ��j
	);
#else
	//�E�B���h�E���쐬
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,						//�E�B���h�E�N���X��
		caption,							//�^�C�g���o�[�ɕ\��������e
		WS_POPUP | WS_VISIBLE,				//�X�^�C���i���ʂ̃E�B���h�E WS_OVERLAPPEDWINDOW�j�t���ɂ������Ƃ� WS_POPUP | WS_VISIBLE
		CW_USEDEFAULT,						//�\���ʒu���i���܂����j
		CW_USEDEFAULT,						//�\���ʒu��i���܂����j
		winRect.right - winRect.left,		//�E�B���h�E��
		winRect.bottom - winRect.top,		//�E�B���h�E����
		nullptr,							//�e�E�C���h�E�i�Ȃ��j
		nullptr,							//���j���[�i�Ȃ��j
		hInstance,							//�C���X�^���X
		nullptr								//�p�����[�^�i�Ȃ��j
	);
#endif

	//�E�B���h�E��\��
	ShowWindow(hWnd, nCmdShow);

	return hWnd;
}

//�E�B���h�E�v���V�[�W���i�������������ɂ�΂��֐��j
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static bool isCursorVisible = false;	// �J�[�\�����\������Ă���
    static bool isCursorLimited = true;		// �J�[�\�����������󂯂Ă���

    switch (msg)
    {
        //�E�B���h�E�����
    case WM_DESTROY:
        ReleaseMousePointer();  //�}�E�X�|�C���^�[�̐���������
        PostQuitMessage(0);     //�v���O�����I��
        return 0;

        //�}�E�X��������
    case WM_MOUSEMOVE:
        if (isCursorLimited)
        {
			Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
            LimitMousePointer(hWnd);			// �}�E�X�J�[�\�����E�B���h�E�̒��S�Ɉړ�
			while (ShowCursor(FALSE) >= 0);		// �J�[�\�����\��
        }
        return 0;
        //�L�[�{�[�h�̃L�[�������ꂽ
    case WM_KEYDOWN:
        // �G�X�P�[�v�L�[�������ꂽ�ꍇ
        if (wParam == VK_ESCAPE)
        {
			ReleaseMousePointer();			// �}�E�X�|�C���^�[�̐���������
            while (ShowCursor(TRUE) < 0);   // �}�E�X�J�[�\����\������
            int result = MessageBox(hWnd, "�v���O�������I�����܂����H", "�m�F", MB_OKCANCEL | MB_ICONQUESTION);

            if (result == IDOK)PostQuitMessage(0);					// �v���O�����I��
            else if (result == IDCANCEL)LimitMousePointer(hWnd);	// �}�E�X�|�C���^�[�̐�����ݒ�
        }
		// �f�o�b�N�p
#ifdef _DEBUG
		else if (wParam == 'I')
		{
			if (isCursorVisible)
			{
				// �J�[�\�����\��
				while (ShowCursor(FALSE) >= 0);
				isCursorVisible = false;
			}
			else
			{
				// �J�[�\����\��
				while (ShowCursor(TRUE) < 0);
				isCursorVisible = true;
				ReleaseMousePointer();
			}

			// �}�E�X�|�C���^�[�̐������������邩�ݒ肷�邩�؂�ւ���
			isCursorLimited = !isCursorVisible;
		}
		//fps�ς���
		else if (wParam == 'O')
		{
			fpsLimit *= 2.0f;
		}
		else if (wParam == 'L')
		{
			fpsLimit *= 0.5f;
		}
		else if (wParam == 'P')
		{
			isPaused = !isPaused;
		}
#endif
        return 0;
    }

    //ImGui�ɏ���n��
#ifdef _DEBUG
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    {
        return true;
    }
#endif
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// �}�E�X�|�C���^�[�𒆉��ɌŒ肷��֐�
void LimitMousePointer(HWND hwnd)
{
	RECT windowRect;
	GetClientRect(hwnd, &windowRect);

	// �E�B���h�E�̋�`�̈���X�N���[�����W�ɕϊ�
	MapWindowPoints(hwnd, nullptr, reinterpret_cast<POINT*>(&windowRect), 2);
	windowRect.left++;
	windowRect.top++;
	windowRect.right--;
	windowRect.bottom--;

	// �}�E�X�|�C���^�[�𐧌�
	ClipCursor(&windowRect);

	// �E�B���h�E�̒��S���W���v�Z
	POINT windowCenter = { Direct3D::screenWidth_ / 2, Direct3D::screenHeight_ / 2 };

	// �}�E�X�|�C���^�[���E�B���h�E�̒��S�Ɉړ�
	SetCursorPos(windowRect.left + windowCenter.x, windowRect.top + windowCenter.y);
}

// �}�E�X�|�C���^�[�̐�������������֐�
void ReleaseMousePointer()
{
	ClipCursor(nullptr);
}
