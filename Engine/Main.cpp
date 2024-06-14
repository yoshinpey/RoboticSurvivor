#include <Windows.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

//エンジン関連のデータ
#include "Global.h"
#include "RootObject.h"
#include "Model.h"
#include "Image.h"
#include "Camera.h"
#include "Input.h"
#include "Audio.h"
#include "VFX.h"

//ImGui関連のデータ
#ifdef _DEBUG
#include "ImGui/imgui.h"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"
#endif

//#include "../GameManager.h"
#include "GameObject.h"

#pragma comment(lib,"Winmm.lib")

//定数宣言
const char* WIN_CLASS_NAME = "SampleGame";	//ウィンドウクラス名
class GameObject;
int fpsLimit;
static bool isPaused = false;			// ポーズ中

//プロトタイプ宣言
HWND InitApp(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void LimitMousePointer(HWND hwnd);
void ReleaseMousePointer();

#ifdef _DEBUG
//ImGuiにウィンドウプロシージャ―から情報を取得する関数
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif

// エントリーポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 乱数初期化
	srand((unsigned)time(NULL));

	//　現在地をアセットフォルダに設定
	SetCurrentDirectory("Assets");

	int screenWidth;		//スクリーンの幅
	int screenHeight;		//スクリーンの高さ

	//初期化ファイル（setup.ini）から必要な情報を取得
	fpsLimit = GetPrivateProfileInt("GAME", "Fps", 60, ".\\setup.ini");				//FPS（画面更新速度）
	int isDrawFps = GetPrivateProfileInt("DEBUG", "ViewFps", 0, ".\\setup.ini");		//キャプションに現在のFPSを表示するかどうか
#ifdef _DEBUG
	screenWidth = GetPrivateProfileInt("SCREEN", "Width", 800, ".\\setup.ini");			//スクリーンの幅
	screenHeight = GetPrivateProfileInt("SCREEN", "Height", 600, ".\\setup.ini");		//スクリーンの高さ
#else
	// ウィンドウをディスプレイサイズに合わせる
	screenWidth = GetSystemMetrics(SM_CXSCREEN) - 16;		//スクリーンの幅
	screenHeight = GetSystemMetrics(SM_CYSCREEN) - 40;		//スクリーンの高さ
#endif

	//ウィンドウを作成
	HWND hWnd = InitApp(hInstance, screenWidth, screenHeight, nCmdShow);

	//Direct3D準備
	Direct3D::Initialize(hWnd, screenWidth, screenHeight);

#ifdef _DEBUG
	//ImGuiを初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(Direct3D::pDevice_, Direct3D::pContext_);
#endif

	//カメラを準備
	Camera::Initialize();

	//入力処理（キーボード、マウス、コントローラー）の準備
	Input::Initialize(hWnd);

	//オーディオ（効果音）の準備
	Audio::Initialize();

	//ゲームマネージャー初期化
	//GameManager::Initialize();

	//ルートオブジェクト準備
	//すべてのゲームオブジェクトの親となるオブジェクト
	RootObject* pRootObject = new RootObject;
	pRootObject->Initialize();


	//メッセージループ（何か起きるのを待つ）
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		//メッセージあり（こっちが優先）
		if (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		//メッセージなし（ここでゲームの処理）
		else
		{
			// ポーズ中はループ処理しない
			if (isPaused)continue;

			//時間計測
			timeBeginPeriod(1);	//時間計測の制度を上げる
			static int FPS = 0;								//画面更新回数のカウンタ
			static DWORD lastFpsResetTime = timeGetTime();	//最後にキャプションにFPSを表示した
			static DWORD lastUpdateTime = timeGetTime();	//最後に画面を更新した時間
			DWORD nowTime = timeGetTime();					//現在の時間

			//キャプションに現在のFPSを表示する
			if (isDrawFps)
			{
				//1秒（1000ミリ秒）経ったら
				if (nowTime - lastFpsResetTime > 1000)
				{
					//FPSの値を表示
					char string[16];
					wsprintf(string, "FPS:%d", FPS);
					SetWindowText(GetActiveWindow(), string);
					FPS = 0;
					lastFpsResetTime = nowTime;
				}
			}


			//指定した時間（FPSを60に設定した場合は60分の1秒）経過していたら更新処理
			if ((nowTime - lastUpdateTime) * fpsLimit > 1000.0f)
			{
				//時間計測関連
				lastUpdateTime = nowTime;	//現在の時間（最後に画面を更新した時間）を覚えておく
				FPS++;						//画面更新回数をカウントする
#ifdef _DEBUG
				//ImGuiの更新処理
				ImGui_ImplDX11_NewFrame();
				ImGui_ImplWin32_NewFrame();

				ImGui::NewFrame();
				//ImGui::Begin("Hello");//ImGuiの処理を開始
				//{
				//	//描画されるボタンを押したら...
				//	if (ImGui::Button("button")) {
				//		PostQuitMessage(0);	//プログラム終了
				//	}
				//}
				//ImGui::End();//ImGuiの処理を終了
#endif

				//入力（キーボード、マウス、コントローラー）情報を更新
				Input::Update();

				//ゲームマネージャー更新
				//GameManager::Update();

				//全オブジェクトの更新処理
				//ルートオブジェクトのUpdateを呼んだあと、自動的に子、孫のUpdateが呼ばれる
				pRootObject->UpdateSub();

				//カメラを更新
				Camera::Update();

				//エフェクトの更新
				VFX::Update();

				//このフレームの描画開始
				Direct3D::BeginDraw();

				//全オブジェクトを描画
				//ルートオブジェクトのDrawを呼んだあと、自動的に子、孫のUpdateが呼ばれる
				pRootObject->DrawSub();

				//エフェクトの描画
				VFX::Draw();

				//描画処理の前に記述
#ifdef _DEBUG
				ImGui::Render();
				ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
#endif
				//描画終了
				Direct3D::EndDraw();



				
				//ちょっと休ませる
				Sleep(1);
			}
			timeEndPeriod(1);	//時間計測の制度を戻す
		}
	}

	

	//いろいろ解放
	VFX::Release();
	Audio::AllRelease();
	Model::AllRelease();
	Image::AllRelease();
	//GameManager::Release();
	pRootObject->ReleaseSub();
	SAFE_DELETE(pRootObject);

	//ImGuiの開放処理
#ifdef _DEBUG
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();
#endif
	Direct3D::Release();

	return 0;
}


//ウィンドウの作成
HWND InitApp(HINSTANCE hInstance, int screenWidth, int screenHeight, int nCmdShow)
{
	//ウィンドウクラス（設計図）を作成
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);					//この構造体のサイズ
	wc.hInstance = hInstance;						//インスタンスハンドル
	wc.lpszClassName = WIN_CLASS_NAME;				//ウィンドウクラス名
	wc.lpfnWndProc = WndProc;						//ウィンドウプロシージャ
	wc.style = CS_VREDRAW | CS_HREDRAW;				//スタイル（デフォルト）
	wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);	//アイコン
	wc.hIconSm = LoadIcon(nullptr, IDI_WINLOGO);	//小さいアイコン
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);	//マウスカーソル
	wc.lpszMenuName = nullptr;						//メニュー（なし）
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//背景（白）
	RegisterClassEx(&wc);

	//ウィンドウサイズの計算
	RECT winRect = { 0, 0, screenWidth, screenHeight };
	AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);

	//タイトルバーに表示する内容
	char caption[64];
	GetPrivateProfileString("SCREEN", "Caption", "***", caption, 64, ".\\setup.ini");

#ifdef _DEBUG
	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,						//ウィンドウクラス名
		caption,							//タイトルバーに表示する内容
		WS_OVERLAPPEDWINDOW,				//スタイル（普通のウィンドウ WS_OVERLAPPEDWINDOW）フルにしたいとき WS_POPUP | WS_VISIBLE
		CW_USEDEFAULT,						//表示位置左（おまかせ）
		CW_USEDEFAULT,						//表示位置上（おまかせ）
		winRect.right - winRect.left,		//ウィンドウ幅
		winRect.bottom - winRect.top,		//ウィンドウ高さ
		nullptr,							//親ウインドウ（なし）
		nullptr,							//メニュー（なし）
		hInstance,							//インスタンス
		nullptr								//パラメータ（なし）
	);
#else
	//ウィンドウを作成
	HWND hWnd = CreateWindow(
		WIN_CLASS_NAME,						//ウィンドウクラス名
		caption,							//タイトルバーに表示する内容
		WS_POPUP | WS_VISIBLE,				//スタイル（普通のウィンドウ WS_OVERLAPPEDWINDOW）フルにしたいとき WS_POPUP | WS_VISIBLE
		CW_USEDEFAULT,						//表示位置左（おまかせ）
		CW_USEDEFAULT,						//表示位置上（おまかせ）
		winRect.right - winRect.left,		//ウィンドウ幅
		winRect.bottom - winRect.top,		//ウィンドウ高さ
		nullptr,							//親ウインドウ（なし）
		nullptr,							//メニュー（なし）
		hInstance,							//インスタンス
		nullptr								//パラメータ（なし）
	);
#endif

	//ウィンドウを表示
	ShowWindow(hWnd, nCmdShow);

	return hWnd;
}

//ウィンドウプロシージャ（何かあった時によばれる関数）
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static bool isCursorVisible = false;	// カーソルが表示されている
    static bool isCursorLimited = true;		// カーソルが制限を受けている

    switch (msg)
    {
        //ウィンドウを閉じた
    case WM_DESTROY:
        ReleaseMousePointer();  //マウスポインターの制限を解除
        PostQuitMessage(0);     //プログラム終了
        return 0;

        //マウスが動いた
    case WM_MOUSEMOVE:
        if (isCursorLimited)
        {
			Input::SetMousePosition(LOWORD(lParam), HIWORD(lParam));
            LimitMousePointer(hWnd);			// マウスカーソルをウィンドウの中心に移動
			while (ShowCursor(FALSE) >= 0);		// カーソルを非表示
        }
        return 0;
        //キーボードのキーが押された
    case WM_KEYDOWN:
        // エスケープキーが押された場合
        if (wParam == VK_ESCAPE)
        {
			ReleaseMousePointer();			// マウスポインターの制限を解除
            while (ShowCursor(TRUE) < 0);   // マウスカーソルを表示する
            int result = MessageBox(hWnd, "プログラムを終了しますか？", "確認", MB_OKCANCEL | MB_ICONQUESTION);

            if (result == IDOK)PostQuitMessage(0);					// プログラム終了
            else if (result == IDCANCEL)LimitMousePointer(hWnd);	// マウスポインターの制限を設定
        }
		// デバック用
#ifdef _DEBUG
		else if (wParam == 'I')
		{
			if (isCursorVisible)
			{
				// カーソルを非表示
				while (ShowCursor(FALSE) >= 0);
				isCursorVisible = false;
			}
			else
			{
				// カーソルを表示
				while (ShowCursor(TRUE) < 0);
				isCursorVisible = true;
				ReleaseMousePointer();
			}

			// マウスポインターの制限を解除するか設定するか切り替える
			isCursorLimited = !isCursorVisible;
		}
		//fps変える
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

    //ImGuiに情報を渡す
#ifdef _DEBUG
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
    {
        return true;
    }
#endif
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

// マウスポインターを中央に固定する関数
void LimitMousePointer(HWND hwnd)
{
	RECT windowRect;
	GetClientRect(hwnd, &windowRect);

	// ウィンドウの矩形領域をスクリーン座標に変換
	MapWindowPoints(hwnd, nullptr, reinterpret_cast<POINT*>(&windowRect), 2);
	windowRect.left++;
	windowRect.top++;
	windowRect.right--;
	windowRect.bottom--;

	// マウスポインターを制限
	ClipCursor(&windowRect);

	// ウィンドウの中心座標を計算
	POINT windowCenter = { Direct3D::screenWidth_ / 2, Direct3D::screenHeight_ / 2 };

	// マウスポインターをウィンドウの中心に移動
	SetCursorPos(windowRect.left + windowCenter.x, windowRect.top + windowCenter.y);
}

// マウスポインターの制限を解除する関数
void ReleaseMousePointer()
{
	ClipCursor(nullptr);
}
