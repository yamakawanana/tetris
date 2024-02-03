﻿#include <iostream>
#include "DxLib.h"
#include "System/Task/TaskManager.h"
#include "System/Task/Task.h"
#include "System/LogConsole.h"
#include "System/Level/LevelChanger.h"
#include "System/Level/Level.h"
#include "Game/GameInfo.h"
#include "Game/FadeManager.h"
#include "System/Input/InputManager.h"
#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>
#endif

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  // <summary>
  //taskクラスに設定するIDの定数kFirstIdを用意する
  /// <summary>
  static const int kFirstId = 1;

  // <summary>
  //毎フレーム更新処理の引数として入れる0.0fを変数float_timeに格納する
  /// <summary>
  float float_time = 0.0f;

  // <summary>
  //screen_handleの幅を定数kScreenHandleXに格納する
  /// <summary>
  static const int kScreenHandleX = 640;

  // <summary>
  //screen_handleの高さを定数kScreenHandleYに格納する
  /// <summary>
  static const int kScreenHandleY = 480;

  // <summary>
  //毎フレーム更新処理の引数として入れる0.0fを変数float_timeに格納する
  /// <summary>

  //====================================================
  //白色の値を取得
  //====================================================
  unsigned int Cr = GetColor(255, 255, 255);

  //====================================================
  //赤色の値を取得
  //====================================================
  unsigned int RedCr = GetColor(255, 30, 30);

  /// <summary>
  //DrawString関数のX座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 250;

  /// <summary>
  //メインループである事の文字出力のDrawString関数のY座標を定数kYMainroopに格納する
  /// <summary>
  static const int kYMainroop = 160;

  /// <summary>
  //ミリ秒を秒に変換するために1000で割るので、1000を定数kNumConvertSecondに格納する
  /// <summary>
  static const float kNumConvertSecond = 1000;

  /// <summary>
  //カラービット数を定数kColorBitNumに格納する
  /// <summary>
  static const int kColorBitNum = 32;

  /// <summary>
  /// 目標FPS
  /// </summary>
  static const int kTargetFps = 60;

  /// <summary>
  /// 1フレームの時間（秒）
  /// </summary>
  static const float kOneFrameTimeSecond = (static_cast<float>(kNumConvertSecond) / static_cast<float>(kTargetFps)) / kNumConvertSecond;

  /// <summary>
  /// 現在の時間（ミリ秒）
  /// </summary>
  int current_time_millisecond = 0;

  /// <summary>
  /// 前回のフレーム実行時の時間（ミリ秒）
  /// </summary>
  int last_frame_time_millisecond = 0;

  /// <summary>
  /// フレーム数のカウント用
  /// </summary>
  int frame_count = 0;

  /// <summary>
  /// 最後にフレームレートを更新した時間（ミリ秒）
  /// </summary>
  int last_update_frame_rate_time_millisecond = 0;

  /// <summary>
  /// 算出したフレームレート格納用
  /// </summary>
  float frame_rate = 0.0f;
}

/// <summary>
/// フレームレート計算用
/// </summary>
void CalcFrameRate();

/// <summary>
/// フレームレート描画用
/// </summary>
void DrawFrameRate();

/// <summary>
/// プログラムは WinMain から始まります
/// </summary>
/// <param name = "hInstance">アプリケーションの現在のインスタンスハンドル</param>
/// <param name = "hPrevInstance">Win16 の産物（常にNULL）</param>
/// <param name = "lpCmdLine">コマンドライン引数</param>
/// <param name = "nCmdShow">ウィンドウの表示状態</param>
/// <returns>アプリケーションの終了コード</returns>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#if defined(_WIN64) || defined(_WIN32)
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
  //_CrtSetBreakAlloc(1084);
#endif

  ////LogConsoleクラスを宣言する
  //LogConsole log_console;

  ////CreateConsole関数を呼び出す
  //log_console.CreateConsole();

  ////ゲーム情報のインスタンスを作成する
  GameInfo::CreateInstance();

  ////インスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();

  ////ゲーム情報を初期化する
  if (game_info != nullptr) {
    game_info->InitGameInfo();
  }

  //ログファイルは出力しない設定にする
  SetOutApplicationLogValidFlag(TRUE);

  ////解像度の幅と高さを取得する
  int resolution_x_size = game_info->GetResolutionXSize();
  int resolution_y_size = game_info->GetResolutionYSize();

  SetWindowUserCloseEnableFlag(FALSE);

  //====================================================
  //DXライブラリの初期化前の設定
  //====================================================
  ChangeWindowMode(TRUE); // ウィンドウモードに設定
  SetGraphMode(resolution_x_size, resolution_y_size, kColorBitNum);

  //====================================================
  //DXライブラリの初期化処理
  //====================================================
  if (DxLib_Init() == -1) {
    return -1;          // エラーが起きたら直ちに終了
  }

  //描画先の画面を裏画面に設定
  SetDrawScreen(DX_SCREEN_BACK);

  //ウィンドウが非アクティブになってもゲームは止めないようにする
  SetAlwaysRunFlag(true);

  //入力管理を取得
  InputManager* input_manager = InputManager::GetInstance();

  //フェードマネージャーを取得・初期化
  FadeManager* fade_manager = FadeManager::GetInstance();
  fade_manager->InitFadeManager();

  //====================================================
  //TaskManagerクラスを生成
  //====================================================
  TaskManager* task_manager = new TaskManager();
  //生成に失敗した場合、アプリを終了する
  if (task_manager == nullptr) {
    DxLib_End();
    return -1;
  }

  //====================================================
  //LevelChangerクラスを生成
  //====================================================
  LevelChanger* level_changer = new LevelChanger();

  //====================================================
  //タスクIDを設定する
  //====================================================

  level_changer->SetTaskManager(task_manager);

  //====================================================
  //TaskManagerにタスクを積む
  //====================================================
  task_manager->AddTask(level_changer);

  //ゲームメインループ
  while (ProcessMessage() != -1) {

    //システムに処理を渡す
    Sleep(1);

    //現在の時間更新
    current_time_millisecond = GetNowCount();

    //経過時間が目標フレームレート分の1以上経過しているならフレームを実行する
    if (current_time_millisecond - last_frame_time_millisecond >= kNumConvertSecond / kTargetFps)
    {
      //前回フレーム実行からの経過時間を秒で算出
      float delta_time = static_cast<float>(current_time_millisecond - last_frame_time_millisecond) / kNumConvertSecond;

      //最後にフレームを実行した時間を更新
      last_frame_time_millisecond = current_time_millisecond;

      //フレーム実行のたびにFPSをカウントする
      ++frame_count;

      //画面の消去
      ClearDrawScreen();

      //ウィンドウがアクティブなら実行する処理
      if (GetWindowActiveFlag() == TRUE) {

        //全てのキー情報の更新
        input_manager->UpdateKeyStateAll(delta_time);

        //タスクの更新
        task_manager->UpdateTask(delta_time);

        //フェードマネージャーの更新
        fade_manager->UpdateFadeManager(delta_time);

        //全てのキー情報の記録
        input_manager->RecordKeyStateAll(delta_time);
      }

      //タスクの描画
      task_manager->RenderTask();

      //フェードマネージャーの描画
      fade_manager->RenderFadeManager();

      //フレームレートの計算
      CalcFrameRate();

      //フレームレートの描画
      DrawFrameRate();

      //経過時間を描画
      //DrawFormatString(0, 16, RedCr, "delta_time[%.4f]", delta_time);

      //表画面への出力
      ScreenFlip();
    }
    
  }

  //====================================================
  // 積んであるタスクを降ろす
  //====================================================
  task_manager->UnloadTask(level_changer->GetId());

  //TaskManagerクラスのメモリを開放する
  delete task_manager;
  task_manager = nullptr;

  //LevelChangerクラスのメモリを開放する
  delete level_changer;
  level_changer = nullptr;

  //フェードマネージャーの破棄
  fade_manager->FinFadeManager();
  FadeManager::Destroy();

  //入力管理の破棄
  InputManager::Destroy();

  //ＤＸライブラリ使用の終了処理
  DxLib_End();

  //ゲーム情報を解放する
  game_info->ReleaseInstance();

  //DestroyConsole関数を呼び出す
  //log_console.DestroyConsole();

  //====================================================
  //ソフトの終了
  //====================================================
  return 0;
}

/// <summary>
/// フレームレート計算用
/// </summary>
void CalcFrameRate()
{
  //前回のフレームレート更新からの経過時間を求める
  int diff_time = current_time_millisecond - last_update_frame_rate_time_millisecond;

  //前回のフレームレート更新から1秒以上経過していたらフレームレートを更新する
  if (diff_time > kNumConvertSecond)
  {
    //フレーム回数をミリ秒に合わせる
    //少数まで出したいのでfloatにキャスト
    float count = (float)(frame_count * kNumConvertSecond);

    //フレームレートを求める
    //理想どうりなら 60000 / 1000 で 60 となる
    frame_rate = count / diff_time;

    //フレームカウントをクリア
    frame_count = 0;

    //フレームレート更新時間を更新
    last_update_frame_rate_time_millisecond = current_time_millisecond;
  }

}

/// <summary>
/// フレームレート描画用
/// </summary>
void DrawFrameRate()
{
  //DrawFormatString(0, 0, RedCr, "FPS[%.2f]", frame_rate);
}
