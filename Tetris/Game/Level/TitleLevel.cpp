#include <iostream>
#include <chrono>
#include <thread>
#include <array>
#include "Game/Level/TitleLevel.h"
#include "Game/GameInfo.h"
#include "System/Input/InputManager.h"
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
  //白色の値を取得
  /// </summary>
  unsigned int WhiteCr = GetColor(255, 255, 255);

  /// <summary>
  //赤色の値を取得
  /// <summary>
  unsigned int RedCr = GetColor(255, 30, 30);

  /// <summary>
  //選択項目の描画X座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 314;

  /// <summary>
  //選択項目の描画Y座標を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 350;

  /// <summary>
  //1つ目のブロックの描画X座標を定数kFirstBlockXcoordinateに格納する
  /// <summary>
  static const int kFirstBlockXcoordinate = 232;

  /// <summary>
  //2つ目のブロックの描画X座標を定数kSecondBlockXcoordinateに格納する
  /// <summary>
  static const int kSecondBlockXcoordinate = 576;

  /// <summary>
  //ブロックの描画Y座標を定数kBlockYcoordinateに格納する
  /// <summary>
  static const int kBlockYcoordinate = 365;

  /// <summary>
  //選択項目の描画Y座標の間隔を定数kYcoordinateSpaceに格納する
  /// <summary>
  static const int kYcoordinateSpace = 70;

  /// <summary>
  //文字の描画開始X位置と白い枠の描画開始X位置の差を定数kRectangleXに格納する
  /// <summary>
  static const int kRectangleX = 87;

  /// <summary>
  //文字の描画開始Y位置と白い枠の描画開始Y位置の差を定数kRectangleYに格納する
  /// <summary>
  static const int kRectangleY = 35;

  /// <summary>
  ///画像を点滅させるタイミングを定数kFlashBubbleに格納する
  /// </summary>
  static const float kFlashBubble = 0.8f;

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

  // <summary>
  //画面の幅を定数kScreenSizeXに格納する
  /// <summary>
  static const int kScreenSizeX = 800;

  // <summary>
  //画面の高さを定数kScreenSizeYに格納する
  /// <summary>
  static const int kScreenSizeY = 600;

  /// <summary>
  /// タイトル画面の背景画像のファイル名を定数kTitlePngに格納する
  /// </summary>
  static const char* kTitlePng = "Assets/Images/title.png";

  /// <summary>
  /// タイトルロゴ画像のファイル名を定数kTitleLogoPngに格納する
  /// </summary>
  static const char* kTitleLogoPng = "Assets/Images/title_logo.png";

  /// <summary>
  /// タイトル画面の星空背景画像のファイル名を定数kStarBackPngに格納する
  /// </summary>
  static const char* kStarBackPng = "Assets/Images/star_back.png";

  /// <summary>
  /// ボタンの画像のファイル名を定数kButtonHandleに格納する
  /// </summary>
  static const char* kButtonHandle = "Assets/Images/button.png";

  /// <summary>
  /// 選択項目を囲む枠のファイル名を定数kSelectedButtonPngに格納する
  /// </summary>
  static const char* kSelectedButtonPng = "Assets/Images/selected_button.png";

  /// <summary>
  /// ブロックの画像のファイル名を定数kBlockPngに格納する
  /// </summary>
  static const char* kBlockPng = "Assets/Images/o.png";

  /// <summary>
  /// BGMのサウンドファイル名を定数kBgmMp3に格納する
  /// </summary>
  static const char* kBgmMp3 = "Assets/Sounds/cossack-dance-edm-russian-tetris-electronika-151723.mp3";

  /// <summary>
  /// Enterを押した時の音のサウンドファイル名を定数kEnterMp3に格納する
  /// </summary>
  static const char* kEnterMp3 = "Assets/Sounds/Enter26.mp3";

  /// <summary>
  /// カーソル操作効果音のサウンドファイル名を定数kNextPageMp3に格納する
  /// </summary>
  static const char* kCursorMp3 = "Assets/Sounds/Enter2.mp3";

  /// <summary>
  /// タイトル画面の動画のファイル名を定数kTitleMp4に格納する
  /// </summary>
  static const char* kTitleMp4 = "Assets/Images/title.mp4";

  /// <summary>
  /// フォントを指定する文字列を定数kFontに格納する
  /// </summary>
  static const char* kFont = "メイリオ";

  /// <summary>
  /// 「ゲーム開始」を指定する文字列を定数kGameStartStringに格納する
  /// </summary>
  static const char* kGameStartString = "ゲーム開始";

  /// <summary>
  /// 「設定」を指定する文字列を定数kSettingStringに格納する
  /// </summary>
  static const char* kSettingString = "    設定    ";

  /// <summary>
  /// 「ゲーム終了」を指定する文字列を定数kExitStringに格納する
  /// </summary>
  static const char* kExitString = "ゲーム終了";

  /// <summary>
  /// 「%s」を指定する文字列を定数kPercentSに格納する
  /// </summary>
  static const char* kPercentS = "%s";

  /// <summary>
  /// フォントサイズの定数kFontSize
  /// </summary>
  static const int kFontSize = 35;

  /// <summary>
  /// フォントの太さの定数kFontThickness
  /// </summary>
  static const int kFontThickness = 10;

  /// <summary>
  /// 設定を保存するファイル名を定数kSettingCSVに格納する
  /// </summary>
  static const char* kSettingCSV = "setting.csv";

  /// <summary>
  /// 音量の初期値を定数kDefaultVolumeに格納する
  /// </summary>
  static const int kDefaultVolume = 80;

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

  /// <summary>
  //描画角度を定数の配列kPiに格納する
  /// <summary>
  static const double kAngles[] = { 0.0, (3.141592654/4),  (3.141592654 / 2), (3*(3.141592654) / 4), (3.141592654 / 1), (5 * (3.141592654) / 4), (3 * (3.141592654) / 2), (3 * (3.141592654) / 4) };

  /// <summary>
  /// kAnglesの要素数を定数kAnglesElementに格納する
  /// </summary>
  static const int kAnglesElement = 8;

  /// <summary>
  /// ブロックの角度を変えるまでの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const float kWaitTimes[] = { 0.0f, 0.2f, 0.4f, 0.6f, 0.8f, 1.0f, 1.2f, 1.4f, 1.6f };
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
TitleLevel::TitleLevel()
: is_finish_(false)
, accumulation_time_(0.0f)
, display_accumulation_time_(0.0f)
, end_type_(kUnloadTask)
, title_handle_(0)
, width_(0)
, height_(0)
, half_width_(0.0f)
, half_height_(0.0f)
, bgm_handle_(0)
, enter_handle_(0)
, cursor_handle_(0)
, menu_type_(kStartGame)
, select_index_(0)
, movie_handle_(0)
, star_back_handle_(0)
, title_logo_handle_(0)
, white_rectangle_handle_(0)
, sound_volume_(kDefaultVolume)
, fade_(0)
, is_enter_(false)
, selected_button_handle_(0)
, block_gr_handle_(0)
, angle_type_(kAngle0)
{
  DEBUG_PRINT(TitleLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
TitleLevel::TitleLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , end_type_(kUnloadTask)
  , title_handle_(0)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , bgm_handle_(0)
  , enter_handle_(0)
  , cursor_handle_(0)
  , menu_type_(kStartGame)
  , select_index_(0)
  , movie_handle_(0)
  , star_back_handle_(0)
  , title_logo_handle_(0)
  , white_rectangle_handle_(0)
  , sound_volume_(kDefaultVolume)
  , fade_(0)
  , is_enter_(false)
  , selected_button_handle_(0)
  , block_gr_handle_(0)
  , angle_type_(kAngle0)
{
  DEBUG_PRINT(TitleLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
TitleLevel::~TitleLevel() {
  DEBUG_PRINT(TitleLevelのデストラクタ);
}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);
  is_finish_ = true;
}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushFinish() {
  //DEBUG_PRINT(終了ボタンが押された時のイベント);
  //SetEndButton();
  //is_finish_ = true;
}

/// <summary>
/// スペースボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushPause() {
  DEBUG_PRINT(スペースボタンが押された時のイベント);
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void TitleLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);
}

/// <summary>
/// SetTitleGrHandle関数の定義
/// </summary>
/// <param = "title_handle">Titleのグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetTitleGrHandle(int title_handle) {
  title_handle_ = title_handle;
}

/// <summary>
/// GetTitleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Titleのグラフィックハンドル</returns>
int TitleLevel::GetTitleGrHandle() {
  return title_handle_;
}

/// <summary>
/// SetWhiteRectangleGrHandle関数の定義
/// </summary>
/// <param = "white_rectangle_handle">白い長方形のグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetWhiteRectangleGrHandle(int white_rectangle_handle) {
  white_rectangle_handle_ = white_rectangle_handle;
}

/// <summary>
/// GetWhiteRectangleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>白い長方形のグラフィックハンドル</returns>
int TitleLevel::GetWhiteRectangleGrHandle() {
  return white_rectangle_handle_;
}

/// <summary>
/// SetBgmHandle関数の定義
/// </summary>
/// <param = "bgm_handle">BGMのサウンドハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetBgmHandle(int bgm_handle) {
  bgm_handle_ = bgm_handle;
}

/// <summary>
/// GetBgmHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BGMのサウンドハンドル</returns>
int TitleLevel::GetBgmHandle() {
  return bgm_handle_;
}

/// <summary>
/// SetEnterSoundHandle関数の定義
/// </summary>
/// <param = "enter_handle">Enterを押した時のサウンドハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetEnterSoundHandle(int enter_handle) {
  enter_handle_ = enter_handle;
}

/// <summary>
/// GetEnterSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Enterを押した時のサウンドハンドル</returns>
int TitleLevel::GetEnterSoundHandle() {
  return enter_handle_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void TitleLevel::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int TitleLevel::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void TitleLevel::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int TitleLevel::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void TitleLevel::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float TitleLevel::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void TitleLevel::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float TitleLevel::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool TitleLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(TitleLevelの初期化処理);

  //画像データをロードする
  int title_handle = LoadGraph(kTitlePng);
  int title_logo_handle = LoadGraph(kTitleLogoPng);
  int white_rectangle_handle = LoadGraph(kButtonHandle);
  int star_back_handle = LoadGraph(kStarBackPng);
  int selected_handle = LoadGraph(kSelectedButtonPng);
  int block_handle = LoadGraph(kBlockPng);

  //サウンドデータをロードする
  int bgm_handle = LoadSoundMem(kBgmMp3);
  int enter_handle = LoadSoundMem(kEnterMp3);
  int cursor_sound_handle = LoadSoundMem(kCursorMp3);

  //グラフィックハンドルを設定する
  SetTitleGrHandle(title_handle);
  SetWhiteRectangleGrHandle(white_rectangle_handle);
  SetStarBackGrHandle(star_back_handle);
  SetTitleLogoGrHandle(title_logo_handle);
  SetSelectedButtonGrHandle(selected_handle);
  SetBlockGrHandle(block_handle);

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

  //サウンドを再生する
  PlaySoundMem(bgm_handle_, DX_PLAYTYPE_LOOP);

  //ロードした画像の幅を取得して保存するための整数size_xを用意して初期化
  int size_x = 0;
  //ロードした画像の高さを取得して保存するための整数size_yを用意して初期化
  int size_y = 0;

  //ロードしたキャラクターの画像のサイズを取得する
  GetGraphSize(title_handle, &size_x, &size_y);

  DEBUG_PRINT_VAR(size_x);
  DEBUG_PRINT_VAR(size_y);

  //画像の幅を設定する
  SetWidth(size_x);
  //画像の高さを設定する
  SetHeight(size_y);

  //ロードした画像から取得した幅の半分のサイズを計算する
  float half_width = static_cast<float>(size_x) / 2;
  //ロードした画像から取得した高さの半分のサイズを計算する
  float half_height = static_cast<float>(size_y) / 2;

  //画像の幅の半分を設定する
  SetHalfWidth(half_width);
  //画像の高さの半分を設定する
  SetHalfHeight(half_height);

  //タイトル動画を再生する
  PlayMovie(kTitleMp4, 1, DX_MOVIEPLAYTYPE_NORMAL);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool TitleLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(TitleLevelの毎フレーム更新処理のフェーズ処理);

  //入力管理を取得
  InputManager* input_manager = InputManager::GetInstance();

  accumulation_time_ = accumulation_time_ + time;
  if (accumulation_time_ >= kLimitTime) {
    accumulation_time_ = 0.0f;
  }

  //累積時間によってブロックの角度を変更する
  for (int i = 0; i < (kAnglesElement + 1); i++) {
    if (accumulation_time_ >= kWaitTimes[i] && accumulation_time_ < kWaitTimes[i + 1]) {
      angle_type_ = static_cast<AngleType>((i));
      //DEBUG_PRINT_VAR(angle_type_);
    }
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
    // 選択されたメニューに応じて画面遷移する
    if (static_cast<MenuOption>(select_index_) == kStartGame) {
      OnPushDecide();
      //DEBUG_PRINT(ゲーム開始が確定);
    }
    else if (static_cast<MenuOption>(select_index_) == kSetting) {
      SetSetting();
      OnPushDecide();
      //DEBUG_PRINT(設定が確定);
    }
    else if (static_cast<MenuOption>(select_index_) == kExit) {
      SetEndButton();
      OnPushDecide();
      //DEBUG_PRINT(ゲーム終了が確定);
    }
  }

  //DEBUG_PRINT_VAR(accumulation_time_);

  if (GetWindowUserCloseFlag()) {
    SetEndButton();
    is_finish_ = true;
  }

  //スペースボタンが押されたら、スペースボタンが押された時のイベントを呼び出す
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kSpace)) {
    OnPushPause();
  }

  // 矢印キーで選択を変更する
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kUp) && is_enter_ == false) {
    PlaySoundMem(cursor_handle_, DX_PLAYTYPE_BACK);
    select_index_ = (select_index_ - 1 + static_cast<int>((MenuOption::kExit)+1)) % static_cast<int>((MenuOption::kExit)+1);
  }
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDown) && is_enter_ == false) {
    PlaySoundMem(cursor_handle_, DX_PLAYTYPE_BACK);
    select_index_ = (select_index_ + 1) % static_cast<int>((MenuOption::kExit)+1);
  }

  // エンターキーが押された場合
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDecide) && (static_cast<MenuOption>(select_index_) == kStartGame || static_cast<MenuOption>(select_index_) == kSetting || static_cast<MenuOption>(select_index_) == kExit)) {
    is_enter_ = true;
    PlaySoundMem(enter_handle_, DX_PLAYTYPE_BACK);
  }

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
void TitleLevel::ProcessingRender() {
  //DEBUG_PRINT(TitleLevelの描画処理);

  //タイトルを表示する
  DrawGraph(0, 0, title_handle_, TRUE);
  DrawGraph(0, 0, star_back_handle_, TRUE);
  DrawGraph(0, 0, title_logo_handle_, TRUE);

  ChangeFont(kFont);
  SetFontSize(kFontSize);
  //SetFontThickness(kFontThickness);
  // メニューの描画
  for (int i = 0; i < static_cast<int>((MenuOption::kExit)+1); ++i) {
    DrawGraph(kXcoordinate - kRectangleX, kYcoordinate + (i * kYcoordinateSpace) - kRectangleY, white_rectangle_handle_, TRUE);
    if (i == select_index_) {
      // 選択中の項目は周りにピンクの枠を表示する
      DrawFormatString(kXcoordinate, kYcoordinate + i * kYcoordinateSpace, WhiteCr, kPercentS, (static_cast<MenuOption>(i)== kStartGame) ? kGameStartString : (static_cast<MenuOption>(i) == kSetting) ? kSettingString : kExitString);
      DrawGraph(kXcoordinate - kRectangleX, kYcoordinate + (i * kYcoordinateSpace) - kRectangleY, selected_button_handle_, TRUE);
      for (int j = 0; j < kAnglesElement; j++) {
        if (angle_type_ == static_cast<AngleType>(j)) {
          DrawRotaGraph(kFirstBlockXcoordinate, kBlockYcoordinate + i * kYcoordinateSpace, 1.0, kAngles[j], block_gr_handle_, TRUE);
          DrawRotaGraph(kSecondBlockXcoordinate, kBlockYcoordinate + i * kYcoordinateSpace, 1.0, kAngles[j], block_gr_handle_, TRUE);
        }
      }

    }
    else {
      DrawFormatString(kXcoordinate, kYcoordinate + i * kYcoordinateSpace, WhiteCr, kPercentS, (static_cast<MenuOption>(i) == kStartGame) ? kGameStartString : (static_cast<MenuOption>(i) == kSetting) ? kSettingString : kExitString);
    }
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
bool TitleLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(TitleLevelの終了処理);
  //描画をクリアする
  ClearDrawScreen();

  //取得したグラフィックハンドルを使い、リソースを破棄する
  DeleteGraph(GetTitleGrHandle());
  DeleteGraph(GetWhiteRectangleGrHandle());
  DeleteGraph(GetStarBackGrHandle());
  DeleteGraph(GetTitleLogoGrHandle());
  DeleteGraph(GetSelectedButtonGrHandle());
  DeleteGraph(GetBlockGrHandle());

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
/// フェードイン表示する関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void TitleLevel::FadeIn(int x, int y, int size_x, int size_y, int fade, int plus_alpha) {

  //DEBUG_PRINT(フェードイン開始);

  int alpha = plus_alpha * fade;
  //DEBUG_PRINT_VAR(alpha);

  SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
  DrawBox(x, y, size_x, size_y, Cr, TRUE);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// SetMovieGrHandle関数の定義
/// </summary>
/// <param = "movie_handle">動画のグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetMovieGrHandle(int movie_handle) {
  movie_handle_ = movie_handle;
}

/// <summary>
/// GetMovieGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>動画のグラフィックハンドル</returns>
int TitleLevel::GetMovieGrHandle() {
  return movie_handle_;
}

/// <summary>
/// SetStarBackGrHandle関数の定義
/// </summary>
/// <param = "star_back_handle">星空背景のグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetStarBackGrHandle(int star_back_handle) {
  star_back_handle_ = star_back_handle;
}

/// <summary>
/// GetStarBackGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>星空背景のグラフィックハンドル</returns>
int TitleLevel::GetStarBackGrHandle() {
  return star_back_handle_;
}

/// <summary>
/// SetTitleLogoGrHandle関数の定義
/// </summary>
/// <param = "title_logo_handle">Titleロゴのグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetTitleLogoGrHandle(int title_logo_handle) {
  title_logo_handle_ = title_logo_handle;
}

/// <summary>
/// GetTitleLogoGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Titleロゴのグラフィックハンドル</returns>
int TitleLevel::GetTitleLogoGrHandle() {
  return title_logo_handle_;
}

/// <summary>
/// SetCursorSoundHandle関数の定義
/// </summary>
/// <param = "cursor_sound_handle">カーソル操作のサウンドハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetCursorSoundHandle(int cursor_handle) {
  cursor_handle_ = cursor_handle;
}

/// <summary>
/// GetCursorSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>カーソル操作のサウンドハンドル</returns>
int TitleLevel::GetCursorSoundHandle() {
  return cursor_handle_;
}

/// <summary>
/// SetSelectedButtonGrHandle関数の定義
/// </summary>
/// <param = "selected_button_handle">選択されたボタンを囲む枠のグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetSelectedButtonGrHandle(int selected_button_handle) {
  selected_button_handle_ = selected_button_handle;
}

/// <summary>
/// GetSelectedButtonGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>選択されたボタンを囲む枠のグラフィックハンドル</returns>
int TitleLevel::GetSelectedButtonGrHandle() {
  return selected_button_handle_;
}

/// <summary>
/// SetBlockGrHandle関数の定義
/// </summary>
/// <param = "block_gr_handle">ブロックのグラフィックハンドル</param>
/// <returns>なし</returns>
void TitleLevel::SetBlockGrHandle(int block_gr_handle) {
  block_gr_handle_ = block_gr_handle;
}

/// <summary>
/// GetBlockGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックのグラフィックハンドル</returns>
int TitleLevel::GetBlockGrHandle() {
  return block_gr_handle_;
}