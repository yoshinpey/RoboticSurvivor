<はじめに>
ゲームは”実行ファイル”フォルダ内のexeファイルから実行ができます。
プレイ動画は”実行ファイル”フォルダ内のショートカット先に置いてあります。

続々と出現する敵をすべて討伐するシューティングゲームです

<こだわった点>
･他人が見ても一目で内容が分かるよう、丁寧な変数名と関数名、コメントをつけるよう心がけました。
･ステータスやパラメータなど、後に変更が必要になると思われる箇所は外部ファイルから読み取りを行うようにしました。
･実体を持つオブジェクトはそれぞれベースクラスを継承させ、マネージャークラスで管理することで、追加や削除が用意になるように設計しました。

<操作方法>
移動:WASD
ジャンプ:Space
通常射撃:LeftClick
範囲攻撃:RightClick

<ファイル構成>
│  Aim.cpp
│  Aim.h
│  AudioManager.cpp
│  AudioManager.h
│  BulletBase.h
│  Bullet_Explosion.cpp
│  Bullet_Explosion.h
│  Bullet_Normal.cpp
│  Bullet_Normal.h
│  Button.cpp
│  Button.h
│  ButtonFactory.cpp
│  ButtonFactory.h
│  CharacterBase.cpp
│  ClearScene.cpp
│  ClearScene.h
│  Crystal.cpp
│  Crystal.h
│  EffectManager.cpp
│  EffectManager.h
│  EnemyBase.h
│  EnemyManager.cpp
│  EnemyManager.h
│  EnemyState.cpp
│  EnemyState.h
│  Enemy_Explosion.cpp
│  Enemy_Explosion.h
│  Enemy_Fly.cpp
│  Enemy_Fly.h
│  Enemy_Ground.cpp
│  Enemy_Ground.h
│  EventManager.cpp
│  EventManager.h
│  GameManager.cpp
│  GameManager.h
│  Gauge.cpp
│  Gauge.h
│  Gravity.cpp
│  Gravity.h
│  Ground.cpp
│  Ground.h
│  Gun.cpp
│  Gun.h
│  InputManager.cpp
│  InputManager.h
│  ItemBase.h
│  ItemManager.cpp
│  ItemManager.h
│  JsonReader.h
│  OverScene.cpp
│  OverScene.h
│  picojson.h
│  Player.cpp
│  Player.h
│  PlayerBase.h
│  PlayerState.cpp
│  PlayerState.h
│  PlayScene.cpp
│  PlayScene.h
│  pugiconfig.hpp
│  pugixml.cpp
│  pugixml.hpp
│  RoboticSurvivors.sln
│  RoboticSurvivors.vcxproj
│  RoboticSurvivors.vcxproj.filters
│  RoboticSurvivors.vcxproj.user
│  Score.cpp
│  Score.h
│  SkyBox.cpp
│  SkyBox.h
│  StateBase.h
│  StateManager.cpp
│  StateManager.h
│  Timer.cpp
│  Timer.h
│  TitleScene.cpp
│  TitleScene.h
│
├─Assets
│  │  char.png
│  │  imgui.ini
│  │  setup.ini
│  │
│  ├─Character
│  │      Enemy_02.fbx
│  │      Enemy_Explosion.fbx
│  │      Enemy_Fly.fbx
│  │      Enemy_Ground.fbx
│  │
│  ├─DebugCollision
│  │      BoxCollider.fbx
│  │      SphereCollider.fbx
│  │
│  ├─Entity
│  │      Bullet.fbx
│  │      Rifle.fbx
│  │
│  ├─Paticle
│  │      bubble.png
│  │      circle_B.png
│  │      circle_R.png
│  │      circle_W.png
│  │      circle_Y.png
│  │      cloudA.png
│  │      cloudB.png
│  │      cloudC.png
│  │      flashA_B.png
│  │      flashA_R.png
│  │      flashA_W.png
│  │      flashA_Y.png
│  │      flashB_B.png
│  │      flashB_R.png
│  │      flashB_W.png
│  │      flashB_Y.png
│  │      flashC_B.png
│  │      flashC_R.png
│  │      flashC_W.png
│  │      flashC_Y.png
│  │      magic_A.png
│  │      magic_B.png
│  │      magic_C.png
│  │      magic_D.png
│  │      magic_E.png
│  │      magic_F.png
│  │      magic_G.png
│  │      RingCloud.png
│  │      rlingA_B.png
│  │      rlingA_R.png
│  │      rlingA_W.png
│  │      rlingA_Y.png
│  │      rlingB_B.png
│  │      rlingB_R.png
│  │      rlingB_W.png
│  │      rlingB_Y.png
│  │      slash_B.png
│  │      slash_R.png
│  │      slash_W.png
│  │      slash_Y.png
│  │      star.png
│  │      vortex.png
│  │      water.png
│  │      waterdrop.png
│  │
│  ├─Pictures
│  │      Clear.jpg
│  │      Earth.png
│  │      HitPoint.png
│  │      HitPointFrame.png
│  │      HitPoint_long.png
│  │      Over.jpg
│  │      StarrySky.png
│  │      Title.jpg
│  │
│  ├─Settings
│  │      EnemySettings.ini
│  │      PlayerSettings.ini
│  │      WeaponSettings.ini
│  │
│  ├─Shader
│  │      BillBoard.hlsl
│  │      Debug3D.hlsl
│  │      Simple2D.hlsl
│  │      Simple3D.hlsl
│  │      SkyBox.hlsl
│  │
│  └─Stage
│          Ground.fbx
│          Rock029_2K-JPG_Color.jpg
│          Rock029_2K-JPG_NormalGL.jpg
│          skyBox.fbx
│          skyBox.png
│
└─Engine
    │  Audio.cpp
    │  Audio.h
    │  BillBoard.cpp
    │  BillBoard.h
    │  BoxCollider.cpp
    │  BoxCollider.h
    │  Camera.cpp
    │  Camera.h
    │  Collider.cpp
    │  Collider.h
    │  CsvReader.cpp
    │  CsvReader.h
    │  Debug.cpp
    │  Debug.h
    │  Direct3D.cpp
    │  Direct3D.h
    │  Fbx.cpp
    │  Fbx.h
    │  FbxParts.cpp
    │  FbxParts.h
    │  GameObject.cpp
    │  GameObject.h
    │  Global.h
    │  Image.cpp
    │  Image.h
    │  Input.cpp
    │  Input.h
    │  Main.cpp
    │  Memo.txt
    │  Model.cpp
    │  Model.h
    │  RootObject.cpp
    │  RootObject.h
    │  SceneManager.cpp
    │  SceneManager.h
    │  SphereCollider.cpp
    │  SphereCollider.h
    │  Sprite.cpp
    │  Sprite.h
    │  Text.cpp
    │  Text.h
    │  Texture.cpp
    │  Texture.h
    │  Transform.cpp
    │  Transform.h
    │  VFX.cpp
    │  VFX.h
    │
    └─imgui
            imconfig.h
            imgui.cpp
            imgui.h
            imgui_draw.cpp
            imgui_impl_dx11.cpp
            imgui_impl_dx11.h
            imgui_impl_win32.cpp
            imgui_impl_win32.h
            imgui_internal.h
            imgui_tables.cpp
            imgui_widgets.cpp
            imstb_rectpack.h
            imstb_textedit.h
            imstb_truetype.h