#include <iostream>
#include "Game/Level/ResultLevel.h"
#include "Game/GameInfo.h"
#include "System/Input/InputManager.h"
#include <DxLib.h>
#include <string>
#include "System/FileManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// 累積時間のリセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 1.6f;

  //黒色の値を取得
  unsigned int Cr = GetColor(0, 0, 0);

  /// <summary>
  //ゲームオーバーの場合に文字を表示するX座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 20;

  /// <summary>
  //ゲームオーバーの場合に文字を表示するY座標を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 480;

  /// <summary>
  /// 文字表示の画像を点滅させるタイミングを定数kFlashBubbleに格納する
  /// </summary>
  static const float kFlashBubble = 0.8f;

  /// <summary>
  /// リザルト画面の背景画像のファイル名を定数kResultPngに格納する
  /// </summary>
  static const char* kResultPng = "Assets/Images/gameover_result.png";

  /// <summary>
  /// 選択項目を囲む枠のファイル名を定数kSelectedButtonPngに格納する
  /// </summary>
  static const char* kSelectedButtonPng = "Assets/Images/selected_button.png";

  /// <summary>
  ///　リザルト画面BGMのサウンドファイル名を定数kGameOverBgmMp3に格納する
  /// </summary>
  static const char* kGameOverBgmMp3 = "Assets/Sounds/piano001.mp3";

  /// <summary>
  /// Enterを押した時の音のサウンドファイル名を定数kEnterMp3に格納する
  /// </summary>
  static const char* kEnterMp3 = "Assets/Sounds/Enter26.mp3";

  /// <summary>
  /// カーソル操作効果音のサウンドファイル名を定数kNextPageMp3に格納する
  /// </summary>
  static const char* kCursorMp3 = "Assets/Sounds/Enter2.mp3";

  /// <summary>
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 250;

  /// <summary>
  /// アルファ値から引く値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 30;

  /// <summary>
  /// フェードインの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const int kWaitTime = 30;

  // <summary>
  //画面の幅を定数kScreenSizeXに格納する
  /// <summary>
  static const int kScreenSizeX = 800;

  // <summary>
  //画面の高さを定数kScreenSizeYに格納する
  /// <summary>
  static const int kScreenSizeY = 600;

  /// <summary>
  /// 設定を保存するファイル名を定数kSettingCSVに格納する
  /// </summary>
  static const char* kSettingCSV = "setting.csv";

  /// <summary>
  /// ハイスコアを保存するファイル名を定数kHighScoreに格納する
  /// </summary>
  static const char* kHighScore = "high_score.csv";

  /// <summary>
  /// 音量の初期値を定数kDefaultVolumeに格納する
  /// </summary>
  static const int kDefaultVolume = 80;

  /// <summary>
  /// フォントを指定する文字列を定数kFontに格納する
  /// </summary>
  static const char* kFont = "Arial";

  /// <summary>
  /// 「%5d」を指定する文字列を定数kPercentFiveDに格納する
  /// </summary>
  static const char* kPercentFiveD = "%5d";

  /// <summary>
  //ハイスコアのX位置を定数kHighScoreXに格納する
  /// <summary>
  static const int kHighScoreX = 535;

  /// <summary>
  //ハイスコアのY位置を定数kHighScoreYに格納する
  /// <summary>
  static const int kHighScoreY = 180;

  /// <summary>
  //スコアのY位置を定数kScoreYに格納する
  /// <summary>
  static const int kScoreY = 260;

  /// <summary>
  //消したライン数のY位置を定数kLinesYに格納する
  /// <summary>
  static const int kLinesY = 340;

  /// <summary>
  //レベルのY位置を定数kLevelYに格納する
  /// <summary>
  static const int kLevelY = 423;

  /// <summary>
  /// フォントサイズの定数kFontSize
  /// </summary>
  static const int kFontSize = 21;

  /// <summary>
  //選択されたボタンを囲む枠のX位置を定数kSelectedButtonXcoordinateに格納する
  /// <summary>
  static const int kSelectedButtonXcoordinate = 102;

  /// <summary>
  //選択されたボタンを囲む枠の2つ目のX位置を定数kSecondSelectedButtonXcoordinateに格納する
  /// <summary>
  static const int kSecondSelectedButtonXcoordinate = 374;

  /// <summary>
  //選択されたボタンを囲む枠のY位置を定数kSelectedButtonYcoordinateに格納する
  /// <summary>
  static const int kSelectedButtonYcoordinate = 464;

  /// <summary>
  /// 効果音の最大音量を定数kVolumeに格納する
  /// </summary>
  static const int kMaxSoundEffectVolume = 255;

  /// <summary>
  /// 100％の分母を定数kHundredに格納する
  /// </summary>
  static const int kHundred = 100;

  /// <summary>
  /// フェードイン時間
  /// </summary>
  const float kFadeInTime = 0.1f;
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ResultLevel::ResultLevel()
  : is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , result_handle_(0)
  , selected_button_handle_(0)
  , bgm_handle_(0)
  , enter_handle_(0)
  , cursor_handle_(0)
  , sound_volume_(kDefaultVolume)
  , menu_type_(kRetry)
  , high_score_(0)
  , score_(0)
  , total_lines_(0)
  , level_(0)
  , select_index_(0)
  , fade_(0)
  , is_enter_(false)
{
  DEBUG_PRINT(ResultLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ResultLevel::ResultLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , result_handle_(0)
  , selected_button_handle_(0)
  , bgm_handle_(0)
  , enter_handle_(0)
  , cursor_handle_(0)
  , sound_volume_(kDefaultVolume)
  , menu_type_(kRetry)
  , high_score_(0)
  , score_(0)
  , total_lines_(0)
  , level_(0)
  , select_index_(0)
  , fade_(0)
  , is_enter_(false)
{
  DEBUG_PRINT(ResultLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
ResultLevel::~ResultLevel() {
  DEBUG_PRINT(ResultLevelのデストラクタ);
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);
  is_finish_ = true;
}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushFinish() {
  //DEBUG_PRINT(終了ボタンが押された時のイベント);
  //SetEndButton();
  //is_finish_ = true;
}

/// <summary>
/// スペースボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushPause() {
  DEBUG_PRINT(スペースボタンが押された時のイベント);
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void ResultLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool ResultLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(ResultLevelの初期化処理);

  //ゲーム情報を取得する
  GameInfo* game_info = GameInfo::GetInstance();

  //今回のスコア、消したライン数、レベルを取得
  score_ = game_info->GetScore();
  total_lines_ = game_info->GetLines();
  level_ = game_info->GetLevel();

  //サウンドハンドルを格納するための変数を用意する
  int bgm_handle = 0;

  //サウンドデータをロードする
  bgm_handle = LoadSoundMem(kGameOverBgmMp3);
  int cursor_sound_handle = LoadSoundMem(kCursorMp3);

  //Enterを押した時の効果音のサウンドハンドルを取得する
  int enter_handle = LoadSoundMem(kEnterMp3);

  //サウンドハンドルを設定する
  SetBgmHandle(bgm_handle);
  SetEnterSoundHandle(enter_handle);
  SetCursorSoundHandle(cursor_sound_handle);

  //ファイルマネージャーのインスタンスを取得
  FileManager* file_manager = FileManager::GetInstance();

  //設定のファイルを読み込む
  std::vector<int> setting = file_manager->ReadDataFromFile(kSettingCSV);

  //音量の設定をセットする
  sound_volume_ = setting.at(1);

  //サウンドの音量を変える
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), bgm_handle_);
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), cursor_handle_);
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), enter_handle_);

  // 前回までのハイスコアを読み込む
  std::vector<int> score = file_manager->ReadDataFromFile(kHighScore);

  //ハイスコアをセットする
  high_score_ = score.front();

  //リザルト画面の画像データをロードする
  int result_handle = LoadGraph(kResultPng);

  //選択されたボタンを囲む枠の画像データをロードする
  int selected_handle = LoadGraph(kSelectedButtonPng);

  //グラフィックハンドルを設定する
  SetResultGrHandle(result_handle);
  SetSelectedButtonGrHandle(selected_handle);

  //サウンドを再生する
  PlaySoundMem(bgm_handle_, DX_PLAYTYPE_LOOP);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool ResultLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(ResultLevelの毎フレーム更新処理のフェーズ処理);

  //入力管理を取得
  InputManager* input_manager = InputManager::GetInstance();

  accumulation_time_ = accumulation_time_ + time;
  if (accumulation_time_ >= kLimitTime) {
    accumulation_time_ = 0.0f;
  }

  //Enterが押された後の場合
  if (is_enter_ == true) {
    display_accumulation_time_ = display_accumulation_time_ + time;
    if (display_accumulation_time_ >= kFadeInTime) {
      fade_++;
      display_accumulation_time_ = 0;
    }
  }
  if (fade_ >= (kFadeValue / kPlusAlpha)) {
    if (select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
      SetBackTitle();
    }
    OnPushDecide();
  }

  if (GetWindowUserCloseFlag()) {
    SetEndButton();
    is_finish_ = true;
    DEBUG_PRINT(×ボタン);
  }

  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kRight) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kRetry)) {
      ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), cursor_handle_);
      PlaySoundMem(cursor_handle_, DX_PLAYTYPE_BACK);
      select_index_ = static_cast<int>(MenuOption::kBackTitle);
    }
  }
  else if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kLeft) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
      ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), cursor_handle_);
      PlaySoundMem(cursor_handle_, DX_PLAYTYPE_BACK);
      select_index_ = static_cast<int>(MenuOption::kRetry);
    }
  }

  //Enterが押されたら、決定ボタンが押された時のイベントを呼び出す
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDecide)) {
    is_enter_ = true;
    PlaySoundMem(enter_handle_, DX_PLAYTYPE_BACK);
  }

  //スペースボタンが押されたら、スペースボタンが押された時のイベントを呼び出す
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kSpace)) {
    OnPushPause();
  }

  //描画処理を実行する
  ProcessingRender();

  return is_finish_;
}

/// <summary>
/// 毎フレームの描画処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ResultLevel::ProcessingRender() {
  //DEBUG_PRINT(ResultLevelの描画処理);

  //リザルト画面を表示する
  DrawGraph(0, 0, result_handle_, TRUE);

  SetFontSize(kFontSize);
  //ハイスコア、スコア、消したライン数、レベルを描画する
  DrawFormatString(kHighScoreX, kHighScoreY, Cr, kPercentFiveD, high_score_);
  DrawFormatString(kHighScoreX, kScoreY, Cr, kPercentFiveD, score_);
  DrawFormatString(kHighScoreX, kLinesY, Cr, kPercentFiveD, total_lines_);
  DrawFormatString(kHighScoreX, kLevelY, Cr, kPercentFiveD, level_);

  //選択されている項目を囲む枠を表示する
  if (select_index_ == static_cast<int>(MenuOption::kRetry)) {
    DrawGraph(kSelectedButtonXcoordinate, kSelectedButtonYcoordinate, selected_button_handle_, TRUE);
  }
  else if (select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
    DrawGraph(kSecondSelectedButtonXcoordinate, kSelectedButtonYcoordinate, selected_button_handle_, TRUE);
  }

  //画面遷移時の黒いフェードイン
  if (is_enter_ == true) {
    if (fade_ <= (kFadeValue / kPlusAlpha)) {
      FadeIn(0, 0, kScreenSizeX, kScreenSizeY, fade_, kPlusAlpha);
    }
  }
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool ResultLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(ResultLevelの終了処理);

  //描画をクリアする
  ClearDrawScreen();

  //取得したグラフィックハンドルを使い、リソースを破棄する
  DeleteGraph(GetResultGrHandle());
  DeleteGraph(GetSelectedButtonGrHandle());

  //サウンドのリソースを破棄する
  DeleteSoundMem(GetBgmHandle());
  DeleteSoundMem(GetEnterSoundHandle());
  DeleteSoundMem(GetCursorSoundHandle());

  if (end_type_ == kUnloadTask) {

    //フェーズを破棄フェーズに変更する
    end_type_ = kDelete;
  }
  else if (end_type_ == kDelete) {

  }
  return true;
}

/// <summary>
/// SetResultGrHandle関数の定義
/// </summary>
/// <param = "result_handle">Resultのグラフィックハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetResultGrHandle(int result_handle) {
  result_handle_ = result_handle;
}

/// <summary>
/// GetResultGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Resultのグラフィックハンドル</returns>
int ResultLevel::GetResultGrHandle() {
  return result_handle_;
}

/// <summary>
/// SetSelectedButtonGrHandle関数の定義
/// </summary>
/// <param = "selected_button_handle">選択されたボタンを囲む枠のグラフィックハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetSelectedButtonGrHandle(int selected_button_handle) {
  selected_button_handle_ = selected_button_handle;
}

/// <summary>
/// GetSelectedButtonGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>選択されたボタンを囲む枠のグラフィックハンドル</returns>
int ResultLevel::GetSelectedButtonGrHandle() {
  return selected_button_handle_;
}

/// <summary>
/// SetBgmHandle関数の定義
/// </summary>
/// <param = "bgm_handle">BGMのサウンドハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetBgmHandle(int bgm_handle) {
  bgm_handle_ = bgm_handle;
}

/// <summary>
/// GetBgmHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BGMのサウンドハンドル</returns>
int ResultLevel::GetBgmHandle() {
  return bgm_handle_;
}

/// <summary>
/// SetEnterSoundHandle関数の定義
/// </summary>
/// <param = "enter_handle">Enterを押した時のサウンドハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetEnterSoundHandle(int enter_handle) {
  enter_handle_ = enter_handle;
}

/// <summary>
/// GetEnterSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Enterを押した時のサウンドハンドル</returns>
int ResultLevel::GetEnterSoundHandle() {
  return enter_handle_;
}

/// フェードイン表示する関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void ResultLevel::FadeIn(int x, int y, int size_x, int size_y, int fade, int plus_alpha) {

  //DEBUG_PRINT(フェードイン開始);

  int alpha = plus_alpha * fade;
  //DEBUG_PRINT_VAR(alpha);

  SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
  DrawBox(x, y, size_x, size_y, Cr, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// SetCursorSoundHandle関数の定義
/// </summary>
/// <param = "cursor_sound_handle">カーソル操作のサウンドハンドル</param>
/// <returns>なし</returns>
void ResultLevel::SetCursorSoundHandle(int cursor_handle) {
  cursor_handle_ = cursor_handle;
}

/// <summary>
/// GetCursorSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>カーソル操作のサウンドハンドル</returns>
int ResultLevel::GetCursorSoundHandle() {
  return cursor_handle_;
}