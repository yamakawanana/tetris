#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include "Game/Level/SettingLevel.h"
#include "Game/GameInfo.h"
#include "System/Input/InputManager.h"
#include "System/FileManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  //黒色の値を取得
  unsigned int Cr = GetColor(0, 0, 0);

  /// <summary>
  /// 累積時間のリセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 1.0f;

  /// <summary>
  /// 三角形の画像を動かすタイミングを定数kMoveTriangleに格納する
  /// </summary>
  static const float kMoveTriangle = 0.5f;

  /// <summary>
  //三角形の画像のX位置を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 595;

  /// <summary>
  //三角形の画像のY位置を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 195;

  /// <summary>
  //2つ目の三角形の画像のY位置を定数kYcoordinateに格納する
  /// <summary>
  static const int kSecondYcoordinate = 335;

  /// <summary>
  //3つ目の三角形の画像のX位置を定数kThirdXcoordinateに格納する
  /// <summary>
  static const int kThirdXcoordinate = 510;

  /// <summary>
  //3つ目の三角形の画像のY位置を定数kThirdYcoordinateに格納する
  /// <summary>
  static const int kThirdYcoordinate = 228;

  /// <summary>
  //4つ目の三角形の画像のY位置を定数kForthYcoordinateに格納する
  /// <summary>
  static const int kForthYcoordinate = 368;

  /// <summary>
  //三角形の画像を横にずらした時のX位置の差を定数kChangeXcoordinateに格納する
  /// <summary>
  static const int kChangeXcoordinate = 5;

  /// <summary>
  /// 音量の変化量を定数kChangeVolumeに格納する
  /// </summary>
  static const int kChangeVolume = 5;

  /// <summary>
  /// 音量の初期値を定数kDefaultVolumeに格納する
  /// </summary>
  static const int kDefaultVolume = 80;

  /// <summary>
  /// 音量の初期値を定数kVolumeMaxに格納する
  /// </summary>
  static const int kVolumeMax = 100;

  // <summary>
  //画面の幅を定数kScreenSizeXに格納する
  /// <summary>
  static const int kScreenSizeX = 800;

  // <summary>
  //画面の高さを定数kScreenSizeYに格納する
  /// <summary>
  static const int kScreenSizeY = 600;

  /// <summary>
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 250;

  /// <summary>
  /// アルファ値から引く値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 25;

  /// <summary>
  /// フェードインの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const int kWaitTime = 30;

  /// <summary>
  /// 背景画像のファイル名を定数kSettingPngに格納する
  /// </summary>
  static const char* kSettingPng = "Assets/Images/setting_back.png";

  /// <summary>
  /// 選択項目を囲む枠のファイル名を定数kSelectedMenuPngに格納する
  /// </summary>
  static const char* kSelectedMenuPng = "Assets/Images/selected_menu.png";

  /// <summary>
  /// 選択項目を囲む枠のファイル名を定数kSelectedButtonPngに格納する
  /// </summary>
  static const char* kSelectedButtonPng = "Assets/Images/selected_button.png";

  /// <summary>
  /// 三角形の画像のファイル名を定数kTrianglePngに格納する
  /// </summary>
  static const char* kTrianglePng = "Assets/Images/triangle.png";

  /// <summary>
  /// BGMのサウンドファイル名を定数kBgmMp3に格納する
  /// </summary>
  static const char* kBgmMp3 = "Assets/Sounds/snd_ev_bossa.mp3";

  /// <summary>
  /// 次のレベルに遷移する効果音のサウンドファイル名を定数kNextLevelMp3に格納する
  /// </summary>
  static const char* kNextLevelMp3 = "Assets/Sounds/Enter26.mp3";

  /// <summary>
  /// カーソル操作効果音のサウンドファイル名を定数kNextPageMp3に格納する
  /// </summary>
  static const char* kCursorMp3 = "Assets/Sounds/Enter2.mp3";

  /// <summary>
  /// 設定を保存するファイル名を定数kSettingCSVに格納する
  /// </summary>
  static const char* kSettingCSV = "setting.csv";

  /// <summary>
  /// 「","」を指定する文字列を定数kCommaに格納する
  /// </summary>
  static const char* kComma = ",";

  /// <summary>
  /// フォントを指定する文字列を定数kFontに格納する
  /// </summary>
  static const char* kFont = "Arial";

  /// <summary>
  /// 「%4d」を指定する文字列を定数kPercentFiveDに格納する
  /// </summary>
  static const char* kPercentFiveD = "%4d";

  /// <summary>
  //音量の描画のX位置を定数kSoundVolumeXに格納する
  /// <summary>
  static const int kSoundVolumeX = 525;

  /// <summary>
  //音量の描画のY位置を定数kSoundVolumeYに格納する
  /// <summary>
  static const int kSoundVolumeY = 210;

  /// <summary>
  /// 「ON」を指定する文字列を定数kOnに格納する
  /// </summary>
  static const char* kOn = "ON";

  /// <summary>
  /// 「OFF」を指定する文字列を定数kOffに格納する
  /// </summary>
  static const char* kOff = "OFF";

  /// <summary>
  //ONの描画のX位置を定数kOnXに格納する
  /// <summary>
  static const int kOnX = 540;

  /// <summary>
  //OFFの描画のX位置を定数kOffXに格納する
  /// <summary>
  static const int kOffX = 530;

  /// <summary>
  //ONOFFの描画のY位置を定数kOnOffYに格納する
  /// <summary>
  static const int kOnOffY = 350;

  /// <summary>
  //円周率を定数kPiに格納する
  /// <summary>
  static const double kPi = 3.141592654;

  /// <summary>
  //選択項目を囲む枠のX位置を定数kSelectedMenuXcoordinateに格納する
  /// <summary>
  static const int kSelectedMenuXcoordinate = 148;

  /// <summary>
  //選択項目を囲む枠のY位置を定数kSelectedMenuYcoordinateに格納する
  /// <summary>
  static const int kSelectedMenuYcoordinate = 130;

  /// <summary>
  //選択項目を囲む2つ目の枠のY位置を定数kSecondSelectedMenuYcoordinateに格納する
  /// <summary>
  static const int kSecondSelectedMenuYcoordinate = 269;

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
SettingLevel::SettingLevel()
  : is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , menu_type_(kGhostDisplay)
  , ghost_display_(kDisplay)
  , setting_handle_(0)
  , triangle_handle_(0)
  , bgm_handle_(0)
  , next_level_handle_(0)
  , cursor_handle_(0)
  , select_index_(0)
  , sound_volume_(kDefaultVolume)
  , selected_menu_handle_(0)
  , selected_button_handle_(0)
  , fade_(0)
  , is_enter_(false)
{
  DEBUG_PRINT(SettingLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
SettingLevel::SettingLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , menu_type_(kGhostDisplay)
  , ghost_display_(kDisplay)
  , setting_handle_(0)
  , triangle_handle_(0)
  , bgm_handle_(0)
  , next_level_handle_(0)
  , cursor_handle_(0)
  , select_index_(0)
  , sound_volume_(kDefaultVolume)
  , selected_menu_handle_(0)
  , selected_button_handle_(0)
  , fade_(0)
  , is_enter_(false)
{
  DEBUG_PRINT(SettingLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
SettingLevel::~SettingLevel() {
  DEBUG_PRINT(SettingLevelのデストラクタ);
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void SettingLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);

  is_finish_ = true;

}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void SettingLevel::OnPushFinish() {
  DEBUG_PRINT(Escキーが押された時のイベント);
  //phase_type_ = kFadeOut;
}

/// <summary>
/// スペースボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void SettingLevel::OnPushPause() {
  DEBUG_PRINT(スペースボタンが押された時のイベント);
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void SettingLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);

}

/// <summary>
/// SetSettingGrHandle関数の定義
/// </summary>
/// <param = "setting_handle">設定画面のグラフィックハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetSettingGrHandle(int setting_handle) {
  setting_handle_ = setting_handle;
}

/// <summary>
/// GetSettingGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>設定画面のグラフィックハンドル</returns>
int SettingLevel::GetSettingGrHandle() {
  return setting_handle_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void SettingLevel::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int SettingLevel::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void SettingLevel::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int SettingLevel::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void SettingLevel::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// SetTriangleGrHandle関数の定義
/// </summary>
/// <param = "triangle_handle">三角形の画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetTriangleGrHandle(int triangle_handle) {
  triangle_handle_ = triangle_handle;
}

/// <summary>
/// GetTriangleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>三角形の画像のグラフィックハンドル</returns>
int SettingLevel::GetTriangleGrHandle() {
  return triangle_handle_;
}

/// <summary>
/// SetBgmHandle関数の定義
/// </summary>
/// <param = "bgm_handle">BGMのサウンドハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetBgmHandle(int bgm_handle) {
  bgm_handle_ = bgm_handle;
}

/// <summary>
/// GetBgmHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BGMのサウンドハンドル</returns>
int SettingLevel::GetBgmHandle() {
  return bgm_handle_;
}

/// <summary>
/// SetCursorSoundHandle関数の定義
/// </summary>
/// <param = "cursor_sound_handle">カーソル操作のサウンドハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetCursorSoundHandle(int cursor_handle) {
  cursor_handle_ = cursor_handle;
}

/// <summary>
/// GetCursorSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>カーソル操作のサウンドハンドル</returns>
int SettingLevel::GetCursorSoundHandle() {
  return cursor_handle_;
}

/// <summary>
/// SetNextLevelSoundHandle関数の定義
/// </summary>
/// <param = "next_level_handle">次のレベルに遷移する時のサウンドハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetNextLevelSoundHandle(int next_level_handle) {
  next_level_handle_ = next_level_handle;
}

/// <summary>
/// GetNextLevelSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>次のレベルに遷移する時のサウンドハンドル</returns>
int SettingLevel::GetNextLevelSoundHandle() {
  return next_level_handle_;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float SettingLevel::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void SettingLevel::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float SettingLevel::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool SettingLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(SettingLevelの初期化処理);

  //画像データをロードする
  int rule_gr_handle = LoadGraph(kSettingPng);
  int triangle_handle = LoadGraph(kTrianglePng);
  int selected_menu_handle = LoadGraph(kSelectedMenuPng);
  int selected_button_handle = LoadGraph(kSelectedButtonPng);

  //サウンドデータをロードする
  int bgm_handle = LoadSoundMem(kBgmMp3);
  int next_level_handle = LoadSoundMem(kNextLevelMp3);
  int cursor_sound_handle = LoadSoundMem(kCursorMp3);

  //グラフィックハンドルを設定する
  SetSettingGrHandle(rule_gr_handle);
  //三角形の画像のグラフィックハンドルを設定する
  SetTriangleGrHandle(triangle_handle);
  //選択された枠のグラフィックハンドルを設定する
  SetSelectedMenuGrHandle(selected_menu_handle);
  SetSelectedButtonGrHandle(selected_button_handle);

  //サウンドハンドルを設定する
  SetBgmHandle(bgm_handle);
  SetCursorSoundHandle(cursor_sound_handle);
  SetNextLevelSoundHandle(next_level_handle);

  //ファイルマネージャーのインスタンスを取得
  FileManager* file_manager = FileManager::GetInstance();

  //設定のファイルを読み込む
  std::vector<int> setting = file_manager->ReadDataFromFile(kSettingCSV);

  //音量の設定をセットする
  sound_volume_ = setting.at(1);
  DEBUG_PRINT_VAR(sound_volume_);

  //サウンドの音量を変える
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), bgm_handle_);
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), next_level_handle_);
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), cursor_handle_);

  //サウンドを再生する
  PlaySoundMem(bgm_handle_, DX_PLAYTYPE_LOOP);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool SettingLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(SettingLevelの毎フレーム更新処理のフェーズ処理);

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
    WriteDataToFile(kSettingCSV, ghost_display_, sound_volume_);
    OnPushDecide();
  }

  //×ボタンが押された場合
  if (GetWindowUserCloseFlag()) {
    SetEndButton();
    is_finish_ = true;
  }

  //Enterが押されたら、決定ボタンが押された時のイベントを呼び出す
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDecide) && (select_index_ == static_cast<int>(MenuOption::kBackTitle) || select_index_ == static_cast<int>(MenuOption::kGoBattle))) {
    is_enter_ = true; 
    PlaySoundMem(next_level_handle_, DX_PLAYTYPE_BACK);
  }

  // 矢印キーで変更する
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kUp) && is_enter_ == false) {
    PlaySoundMem(cursor_handle_, DX_PLAYTYPE_BACK);
    if (select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
      select_index_ = static_cast<int>(MenuOption::kGhostDisplay);
    }
    else {
      select_index_ = (select_index_ - 1 + static_cast<int>(MenuOption::kBackTitle)) % static_cast<int>((MenuOption::kBackTitle));
    }
  }
  else if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDown) && is_enter_ == false) {
    PlaySoundMem(cursor_handle_, DX_PLAYTYPE_BACK);
    select_index_ = (select_index_ + 1) % static_cast<int>(MenuOption::kBackTitle);
  }
  else if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kRight) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kGoBattle)) {
      PlaySoundMem(cursor_handle_, DX_PLAYTYPE_BACK);
      select_index_ = static_cast<int>(MenuOption::kBackTitle);
    }
    else if (select_index_ == static_cast<int>(MenuOption::kGhostDisplay)) {
      if (ghost_display_ == kDisplay) {
        ghost_display_ = kDontDisplay;
      }
      else {
        ghost_display_ = kDisplay;
      }
    }
    else if (select_index_ == static_cast<int>(MenuOption::kSoundVolume) && sound_volume_ < kVolumeMax) {
      sound_volume_ = sound_volume_ + kChangeVolume;
    }
  }
  else if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kLeft) && is_enter_ == false) {
    if (select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
      PlaySoundMem(cursor_handle_, DX_PLAYTYPE_BACK);
      select_index_ = static_cast<int>(MenuOption::kGoBattle);
    }
    else if (select_index_ == static_cast<int>(MenuOption::kGhostDisplay)) {
      if (ghost_display_ == kDisplay) {
        ghost_display_ = kDontDisplay;
      }
      else {
        ghost_display_ = kDisplay;
      }
    }
    else if (select_index_ == static_cast<int>(MenuOption::kSoundVolume) && sound_volume_ > 0) {
      sound_volume_ = sound_volume_ - kChangeVolume;
    }
  }

  DEBUG_PRINT_VAR(select_index_);

  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), bgm_handle_);

  //描画処理を実行する
  ProcessingRender();

  //各ボタンを押された時のイベントでis_finish_がtrueになった時、処理終了する
  return is_finish_;
}

/// <summary>
/// 毎フレームの描画処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void SettingLevel::ProcessingRender() {
  //設定画面の背景画像を描画する
  DrawGraph(0, 0, setting_handle_, TRUE);

  //選択項目の枠を描画する
  if (select_index_ == static_cast<int>(MenuOption::kSoundVolume)) {
    DrawGraph(kSelectedMenuXcoordinate, kSelectedMenuYcoordinate, selected_menu_handle_, TRUE);
  }
  else if (select_index_ == static_cast<int>(MenuOption::kGhostDisplay)) {
    DrawGraph(kSelectedMenuXcoordinate, kSecondSelectedMenuYcoordinate, selected_menu_handle_, TRUE);
  }
  else if (select_index_ == static_cast<int>(MenuOption::kGoBattle)) {
    DrawGraph(kSelectedButtonXcoordinate, kSelectedButtonYcoordinate, selected_button_handle_, TRUE);
  }
  else if (select_index_ == static_cast<int>(MenuOption::kBackTitle)) {
    DrawGraph(kSecondSelectedButtonXcoordinate, kSelectedButtonYcoordinate, selected_button_handle_, TRUE);
  }
  
  ChangeFont(kFont);
  //ゴースト表示のONOFFを描画する
  if (ghost_display_ == kDisplay) {
    DrawString(kOnX, kOnOffY, kOn, Cr);
  }
  else{
    DrawString(kOffX, kOnOffY, kOff, Cr);
  }
  //音量を描画する
  DrawFormatString(kSoundVolumeX, kSoundVolumeY, Cr, kPercentFiveD, sound_volume_);

  //三角形の画像を描画する
  if (accumulation_time_ < kMoveTriangle) {
    DrawGraph(kXcoordinate, kYcoordinate, triangle_handle_, TRUE);
    DrawGraph(kXcoordinate, kSecondYcoordinate, triangle_handle_, TRUE);
    DrawRotaGraph(kThirdXcoordinate, kThirdYcoordinate, 1.0, kPi / 1, triangle_handle_, TRUE);
    DrawRotaGraph(kThirdXcoordinate, kForthYcoordinate, 1.0, kPi / 1, triangle_handle_, TRUE);
  }
  else if (accumulation_time_ >= kMoveTriangle && accumulation_time_ < kLimitTime) {
    DrawGraph((kXcoordinate + kChangeXcoordinate), kYcoordinate, triangle_handle_, TRUE);
    DrawGraph((kXcoordinate + kChangeXcoordinate), kSecondYcoordinate, triangle_handle_, TRUE);
    DrawRotaGraph((kThirdXcoordinate - kChangeXcoordinate), kThirdYcoordinate, 1.0, kPi / 1, triangle_handle_, TRUE);
    DrawRotaGraph((kThirdXcoordinate - kChangeXcoordinate), kForthYcoordinate, 1.0, kPi / 1, triangle_handle_, TRUE);
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
bool SettingLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(SettingLevelの終了処理);
  //描画をクリアする
  ClearDrawScreen();

  //取得したグラフィックハンドルを使い、リソースを破棄する

  DeleteGraph(GetSettingGrHandle());
  DeleteGraph(GetTriangleGrHandle());
  DeleteGraph(GetSelectedMenuGrHandle());
  DeleteGraph(GetSelectedButtonGrHandle());

  //サウンドのリソースを破棄する
  DeleteSoundMem(GetBgmHandle());
  DeleteSoundMem(GetCursorSoundHandle());
  DeleteSoundMem(GetNextLevelSoundHandle());

  if (end_type_ == kUnloadTask) {

    //フェーズを破棄フェーズに変更する
    end_type_ = kDelete;
  }
  else if (end_type_ == kDelete) {

  }
  return true;
}

/// <summary>
/// WriteDataToFile関数の定義
/// </summary>
/// <param="filename">ファイル名</param>
/// <param="num">データを書き込む整数</param>
/// <returns>なし</returns>
void SettingLevel::WriteDataToFile(std::string filename, GhostDisplay ghost_display, int num) {
  // CSVファイルに書き込む
  std::ofstream output_file(filename);

  // ファイルが正しく開かれたか確認
  if (output_file.is_open()) {
    // CSVファイルに書き込む
    output_file << ghost_display << std::endl;
    output_file << num << std::endl;

    // ファイルを閉じる
    output_file.close();

    std::cout << ghost_display << std::endl;
    std::cout << num << std::endl;
  }
  else {
    std::cerr << "ファイルを開くことができなかった" << std::endl;
  }
}

/// <summary>
/// SetSelectedMenuGrHandle関数の定義
/// </summary>
/// <param = "selected_menu_handle">選択項目を囲む枠のグラフィックハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetSelectedMenuGrHandle(int selected_menu_handle) {
  selected_menu_handle_ = selected_menu_handle;
}

/// <summary>
/// GetSelectedMenuGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>選択項目を囲む枠のグラフィックハンドル</returns>
int SettingLevel::GetSelectedMenuGrHandle() {
  return selected_menu_handle_;
}

/// <summary>
/// SetSelectedButtonGrHandle関数の定義
/// </summary>
/// <param = "selected_button_handle">選択されているボタンを囲む枠のグラフィックハンドル</param>
/// <returns>なし</returns>
void SettingLevel::SetSelectedButtonGrHandle(int selected_button_handle) {
  selected_button_handle_ = selected_button_handle;
}

/// <summary>
/// GetSelectedButtonGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>選択されているボタンを囲む枠のグラフィックハンドル</returns>
int SettingLevel::GetSelectedButtonGrHandle() {
  return selected_button_handle_;
}

/// <summary>
/// フェードイン表示する関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void SettingLevel::FadeIn(int x, int y, int size_x, int size_y, int fade, int plus_alpha) {

  //DEBUG_PRINT(フェードイン開始);

  int alpha = plus_alpha * fade;
  //DEBUG_PRINT_VAR(alpha);

  SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
  DrawBox(x, y, size_x, size_y, Cr, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}