#include <iostream>
#include <random>
#include <fstream>
#include "DxLib.h"
#include "Game/Level/BattleLevel.h"
#include "Game/GameInfo.h"
#include "System/Input/InputManager.h"
#include "Game/FadeManager.h"
#include "System/Math.h"
#include "System/FileManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  //黒色の値を取得
  unsigned int Cr = GetColor(0, 0, 0);

  /// <summary>
  /// 制限時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 0.5f;

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
  /// 少し透過させた状態でフェードインする時のフェード値を定数kMiddleFadeValueに格納する
  /// </summary>
  static const int kMiddleFadeValue = 50;

  // <summary>
  //screen_handleの幅を定数kScreenHandleXに格納する
  /// <summary>
  static const int kScreenHandleX = 640;

  // <summary>
  //screen_handleの高さを定数kScreenHandleYに格納する
  /// <summary>
  static const int kScreenHandleY = 480;

  /// <summary>
  /// アルファ値に足しこむ値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 10;

  /// <summary>
  /// フェードインの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const int kWaitTime = 100;

  /// <summary>
  //表示するX座標を定数kXcoordinateに格納する
  /// <summary>
  static const int kXcoordinate = 120;

  /// <summary>
  //表示するY座標を定数kYcoordinateに格納する
  /// <summary>
  static const int kYcoordinate = 560;

  /// <summary>
  /// BattleLevelの背景画像のファイル名を定数kBattleBackPngに格納する
  /// </summary>
  static const char* kBattleBackPng = "Assets/Images/battle_back.png";

  /// <summary>
  /// キー操作情報の画像のファイル名を定数kKeyInfoPngに格納する
  /// </summary>
  static const char* kKeyInfoPng = "Assets/Images/key_info.png";

  /// <summary>
  /// 黒い画像のファイル名を定数kBlackPngに格納する
  /// </summary>
  static const char* kBlackPng = "Assets/Images/black.png";

  /// <summary>
  /// ゲームオーバーの画像のファイル名を定数kGameOverPngに格納する
  /// </summary>
  static const char* kGameOverPng = "Assets/Images/gameover.png";

  /// <summary>
  /// スタートUIの画像のファイル名を定数kStartPngに格納する
  /// </summary>
  static const char* kStartPng = "Assets/Images/start.png";

  /// <summary>
  /// ポーズUIの画像のファイル名を定数kPausePngに格納する
  /// </summary>
  static const char* kPausePng = "Assets/Images/pause.png";

  /// <summary>
  /// フィールドにブロックがない状態の画像のファイル名を定数kNonePngに格納する
  /// </summary>
  static const char* kNonePng = "Assets/Images/empty.png";

  /// <summary>
  /// 水色のブロックの画像のファイル名を定数kLightBluePngに格納する
  /// </summary>
  static const char* kLightBluePng = "Assets/Images/lightblue.png";

  /// <summary>
  /// 青色のブロックの画像のファイル名を定数kBluePngに格納する
  /// </summary>
  static const char* kBluePng = "Assets/Images/blue.png";

  /// <summary>
  /// 黄緑色のブロックの画像のファイル名を定数kEmeraldPngに格納する
  /// </summary>
  static const char* kEmeraldPng = "Assets/Images/emerald.png";

  /// <summary>
  /// オレンジ色のブロックの画像のファイル名を定数kOrangePngに格納する
  /// </summary>
  static const char* kOrangePng = "Assets/Images/orange.png";

  /// <summary>
  /// 黄色のブロックの画像のファイル名を定数kYellowPngに格納する
  /// </summary>
  static const char* kYellowPng = "Assets/Images/yellow.png";

  /// <summary>
  /// 紫色のブロックの画像のファイル名を定数kPurplePngに格納する
  /// </summary>
  static const char* kPurplePng = "Assets/Images/purple.png";

  /// <summary>
  /// 赤色のブロックの画像のファイル名を定数kRedPngに格納する
  /// </summary>
  static const char* kRedPng = "Assets/Images/red.png";

  /// <summary>
  /// 発光したブロックの画像のファイル名を定数kLightPngに格納する
  /// </summary>
  static const char* kLightPng = "Assets/Images/light.png";

  /// <summary>
  /// レベルアップ表示の画像のファイル名を定数kLevelUpPngに格納する
  /// </summary>
  static const char* kLevelUpPng = "Assets/Images/level_up.png";

  /// <summary>
  /// スコア表示の画像のファイル名を定数kScorePngに格納する
  /// </summary>
  static const char* kScorePng = "Assets/Images/score.png";

  /// <summary>
  /// Next表示の画像のファイル名を定数kNextPngに格納する
  /// </summary>
  static const char* kNextPng = "Assets/Images/next.png";

  /// <summary>
  /// Hold表示の画像のファイル名を定数kHoldPngに格納する
  /// </summary>
  static const char* kHoldPng = "Assets/Images/hold.png";

  /// <summary>
  /// I型ブロックの画像のファイル名を定数kIBlockPngに格納する
  /// </summary>
  static const char* kIBlockPng = "Assets/Images/i.png";

  /// <summary>
  /// O型ブロックの画像のファイル名を定数kOBlockPngに格納する
  /// </summary>
  static const char* kOBlockPng = "Assets/Images/o.png";

  /// <summary>
  /// S型ブロックの画像のファイル名を定数kSBlockPngに格納する
  /// </summary>
  static const char* kSBlockPng = "Assets/Images/s.png";

  /// <summary>
  /// Z型ブロックの画像のファイル名を定数kZBlockPngに格納する
  /// </summary>
  static const char* kZBlockPng = "Assets/Images/z.png";

  /// <summary>
  /// J型ブロックの画像のファイル名を定数kJBlockPngに格納する
  /// </summary>
  static const char* kJBlockPng = "Assets/Images/j.png";

  /// <summary>
  /// L型ブロックの画像のファイル名を定数kLBlockPngに格納する
  /// </summary>
  static const char* kLBlockPng = "Assets/Images/l.png";

  /// <summary>
  /// T型ブロックの画像のファイル名を定数kTBlockPngに格納する
  /// </summary>
  static const char* kTBlockPng = "Assets/Images/t.png";

  /// <summary>
  /// 「SINGLE」表示用画像のファイル名を定数kSinglePngに格納する
  /// </summary>
  static const char* kSinglePng = "Assets/Images/single.png";

  /// <summary>
  /// 「DOUBLE」表示用画像のファイル名を定数kDoublePngに格納する
  /// </summary>
  static const char* kDoublePng = "Assets/Images/double.png";

  /// <summary>
  /// 「TRIPLE」表示用画像のファイル名を定数kTriplePngに格納する
  /// </summary>
  static const char* kTriplePng = "Assets/Images/triple.png";

  /// <summary>
  /// 「TETRIS」表示用画像のファイル名を定数kTetrisPngに格納する
  /// </summary>
  static const char* kTetrisPng = "Assets/Images/tetris.png";

  /// <summary>
  /// クマの画像のファイル名を定数kBearPngに格納する
  /// </summary>
  static const char* kBearPng = "Assets/Images/standing_bear.png";

  /// <summary>
  /// アヒルの画像のファイル名を定数kBearPngに格納する
  /// </summary>
  static const char* kDuckPng = "Assets/Images/standing_duck.png";

  /// <summary>
  /// ダメージを受けたクマの画像のファイル名を定数kDamageBearPngに格納する
  /// </summary>
  static const char* kDamageBearPng = "Assets/Images/damage_bear.png";

  /// <summary>
  /// ダメージを受けたアヒルの画像のファイル名を定数kDamageDuckPngに格納する
  /// </summary>
  static const char* kDamageDuckPng = "Assets/Images/damage_duck.png";

  /// <summary>
  /// BGMのサウンドファイル名を定数kBgmMp3に格納する
  /// </summary>
  static const char* kBgmMp3 = "Assets/Sounds/rasputin-russia-tetris-game-cossack-puzzle-soundtrack-mystery-148250.mp3";

  /// <summary>
  /// 左右移動のサウンドのファイル名を定数kCursorMp3に格納する
  /// </summary>
  static const char* kCursorMp3 = "Assets/Sounds/Cursor12.mp3";

  /// <summary>
  /// ブロックが固定された時のサウンドのファイル名を定数kFixMp3に格納する
  /// </summary>
  static const char* kFixMp3 = "Assets/Sounds/Enter39.mp3";

  /// <summary>
  /// ホールドした時のサウンドのファイル名を定数kHoldMp3に格納する
  /// </summary>
  static const char* kHoldMp3 = "Assets/Sounds/Enter2.mp3";

  /// <summary>
  /// 回転時のサウンドのファイル名を定数kSpinMp3に格納する
  /// </summary>
  static const char* kSpinMp3 = "Assets/Sounds/Move42.mp3";

  /// <summary>
  /// ブロックがラインで消えた時のサウンドのファイル名を定数kDeleteLineMp3に格納する
  /// </summary>
  static const char* kDeleteLineMp3 = "Assets/Sounds/シーン切り替え2.mp3";

  /// <summary>
  /// ゲームオーバーのサウンドのファイル名を定数kGameOverMp3に格納する
  /// </summary>
  static const char* kGameOverMp3 = "Assets/Sounds/Shock4.mp3";

  /// <summary>
  /// ゲームオーバーの動画のファイル名を定数kGameOverMp4に格納する
  /// </summary>
  static const char* kGameOverMp4 = "Assets/Images/gameover.mp4";

  /// <summary>
  /// ハイスコアを保存するファイル名を定数kHighScoreに格納する
  /// </summary>
  static const char* kHighScore = "high_score.csv";

  /// <summary>
  /// 設定を保存するファイル名を定数kSettingCSVに格納する
  /// </summary>
  static const char* kSettingCSV = "setting.csv";

  /// <summary>
  /// ブロックの二次元配列の左上のX座標の開始位置を定数kStartBlockXに格納する
  /// </summary>
  static const int kStartBlockX = 5;

  /// <summary>
  /// ブロックの二次元配列の左上のY座標の開始位置を定数kStartBlockYに格納する
  /// </summary>
  static const int kStartBlockY = 0;

  /// <summary>
  /// フェードイン時間
  /// </summary>
  const float kFadeInTime = 1.0f;

  /// <summary>
  /// スコアの種類がkOneLineの時のスコアを定数kOneLineScoreに格納する
  /// </summary>
  static const int kOneLineScore = 10;

  /// <summary>
  /// スコアの種類がkTwoLineの時のスコアを定数kTwoLineScoreに格納する
  /// </summary>
  static const int kTwoLineScore = 30;

  /// <summary>
  /// スコアの種類がkThreeLineの時のスコアを定数kThreeLineScoreに格納する
  /// </summary>
  static const int kThreeLineScore = 50;

  /// <summary>
  /// スコアの種類がkFourLineの時のスコアを定数kFourLineScoreに格納する
  /// </summary>
  static const int kFourLineScore = 80;

  /// <summary>
  /// 上キーを押して移動した回数当たりの加点を定数kHardDropScoreに格納する
  /// </summary>
  static const int kHardDropScore = 2;

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
  /// BGMの元の周波数を定数kFrequencyに格納する
  /// </summary>
  static const int kFrequency = 24000;

  /// <summary>
  /// 速くしたBGMの元の周波数を定数kFastFrequencyに格納する
  /// </summary>
  static const int kFastFrequency = 48000;

  /// <summary>
  /// ブロックがもうすぐ天井に付きそうな高さのY位置を定数kDangerousYに格納する
  /// </summary>
  static const int kDangerousY = 6;

  /// <summary>
  /// キャラクターの画像の横向きの分割数を定数kBearDuckXに格納する
  /// </summary>
  static const int kBearDuckX = 3;

  /// <summary>
  /// キャラクターの画像の縦向きの分割数を定数kBearDuckYに格納する
  /// </summary>
  static const int kBearDuckY = 1;

  // <summary>
  //クマとアヒルの画像の幅と高さを定数kBearDuckSizeに格納する
  /// <summary>
  static const int kBearDuckSize = 40;

  // <summary>
  //ダメージを受けたクマの画像の幅と高さを定数kDamageBearSizeに格納する
  /// <summary>
  static const int kDamageBearSize = 60;

  // <summary>
  //ダメージを受けたアヒルの画像の幅を定数kDamageDuckSizeXに格納する
  /// <summary>
  static const int kDamageDuckSizeX = 120;

  // <summary>
  //ダメージを受けたアヒルの画像の高さを定数kDamageDuckSizeYに格納する
  /// <summary>
  static const int kDamageDuckSizeY = 64;

  /// <summary>
  /// 紙吹雪の画像のグラフィックハンドルの縦向きの分割数を定数kConfettiYに格納する
  /// </summary>
  static const int kConfettiY = 12;

  /// <summary>
  /// 紙吹雪のアニメーションコマ数を定数kConfettiCountに格納する
  /// </summary>
  static const int kConfettiCount = 5;

  /// <summary>
  /// 紙吹雪の画像のファイル名を定数kConfettiPngに格納する
  /// </summary>
  static const char* kConfettiPng = "Assets/Images/confetti.png";

}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleLevel::BattleLevel()
  : is_finish_(false)
  , accumulation_time_(0.0f)
  , field_(nullptr)
  , block_(nullptr)
  , game_mode_(nullptr)
  , start_ui_(nullptr)
  , pause_ui_(nullptr)
  , end_type_(kUnloadTask)
  , fix_accumulation_time_(0.0f)
  , gameover_handle_(0)
  , phase_type_(kPreparation)
  , gameover_fade_end_(false)
  , bgm_handle_(0)
  , gameover_sound_handle_(0)
  , score_(0)
  , is_can_fix_blocks_(false)
  , score_type_(kOneLine)
  , is_lined_(false)
  , combo_(0)
  , total_lines_(0)
  , level_(1)
  , is_can_hold_(true)
  , hold_block_(Block::kMinoMax)
  , pre_hold_block_(Block::kMinoMax)
  , fade_(0)
  , pre_field_phase_(Field::kFieldInitialized)
  , high_score_(0)
  , sound_volume_(kDefaultVolume)
  , block_line_(false)
  , white_rectangle_handle_(0)
  , fix_sound_handle_(0)
  , hold_sound_handle_(0)
  , delete_sound_handle_(0)
{
  DEBUG_PRINT(BattleLevelのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleLevel::BattleLevel(TaskId task_id, TaskManager* task_manager)
  : Level(task_id, task_manager)
  , is_finish_(false)
  , accumulation_time_(0.0f)
  , field_(0)
  , block_(0)
  , game_mode_(0)
  , start_ui_(0)
  , pause_ui_(0)
  , end_type_(kUnloadTask)
  , fix_accumulation_time_(0.0f)
  , gameover_handle_(0)
  , phase_type_(kPreparation)
  , gameover_fade_end_(false)
  , bgm_handle_(0)
  , gameover_sound_handle_(0)
  , score_(0)
  , is_can_fix_blocks_(false)
  , score_type_(kOneLine)
  , is_lined_(false)
  , combo_(0)
  , total_lines_(0)
  , level_(1)
  , is_can_hold_(true)
  , hold_block_(Block::kMinoMax)
  , pre_hold_block_(Block::kMinoMax)
  , fade_(0)
  , pre_field_phase_(Field::kFieldInitialized)
  , high_score_(0)
  , sound_volume_(kDefaultVolume)
  , block_line_(false)
  , white_rectangle_handle_(0)
  , fix_sound_handle_(0)
  , hold_sound_handle_(0)
  , delete_sound_handle_(0)
{
  DEBUG_PRINT(BattleLevelのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
BattleLevel::~BattleLevel() {
  DEBUG_PRINT(BattleLevelのデストラクタ);
}

/// <summary>
/// 各方向キーが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushDirectionKey() {
  DEBUG_PRINT(各方向キーが押された時のイベント);


    //サウンドを再生する
    //PlaySoundMem(walk_sound, DX_PLAYTYPE_BACK);

}

/// <summary>
/// 決定ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushDecide() {
  DEBUG_PRINT(決定ボタンが押された時のイベント);
  //フェードアウトでレベルを終了する
  //FadeOut();
  //is_finish_ = true;
}

/// <summary>
/// 終了ボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushFinish() {
  //DEBUG_PRINT(終了ボタンが押された時のイベント);
  //SetEndButton();
  //is_finish_ = true;
}

/// <summary>
/// ポーズボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushPause() {
  DEBUG_PRINT(ポーズボタンが押された時のイベント);
  //プレイ中の場合
  if (phase_type_ == kProcessing) {

    //ポーズUIを表示中フェーズにする
    pause_ui_->SetPhaseType(PauseUi::kDisplay);

    //プレイ中断フェーズに変更する
    phase_type_ = kStop;

    //全ての動きを止める
    StopAll();

    //サウンドを止める
    StopSoundMem(bgm_handle_);
  }

  //プレイ中段中の場合
  else if (phase_type_ == kStop) {

    //ポーズUIを表示前フェーズにする
    pause_ui_->SetPhaseType(PauseUi::kPreDisplay);

    //プレイ中フェーズに変更する
    phase_type_ = kProcessing;

    //全ての動きを元に戻す
    SetPlayingAll();

    //サウンドを再生する
    PlaySoundMem(bgm_handle_, DX_PLAYTYPE_LOOP, FALSE);
  }
}

/// <summary>
/// BackSpaceボタンが押された時のイベント
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::OnPushBackSpace() {
  DEBUG_PRINT(BackSpaceボタンが押された時のイベント);
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BattleLevel::InitializeUpdate(float time) {
  DEBUG_PRINT(BattleLevelの初期化処理);

  //画像データをロードする
  ImageInfo battle_back_info = LoadImage(kBattleBackPng);
  ImageInfo key_info = LoadImage(kKeyInfoPng);
  ImageInfo black_info = LoadImage(kBlackPng);
  ImageInfo start_info = LoadImage(kStartPng);
  ImageInfo pause_info = LoadImage(kPausePng); 
  ImageInfo none_info = LoadImage(kNonePng);
  ImageInfo lightblue_info = LoadImage(kLightBluePng);
  ImageInfo blue_info = LoadImage(kBluePng);
  ImageInfo emerald_info = LoadImage(kEmeraldPng);
  ImageInfo yellow_info = LoadImage(kYellowPng);
  ImageInfo orange_info = LoadImage(kOrangePng);
  ImageInfo purple_info = LoadImage(kPurplePng);
  ImageInfo red_info = LoadImage(kRedPng);
  ImageInfo light_info = LoadImage(kLightPng);
  ImageInfo score_info = LoadImage(kScorePng);
  ImageInfo levelup_info = LoadImage(kLevelUpPng);
  ImageInfo hold_info = LoadImage(kHoldPng);
  ImageInfo next_info = LoadImage(kNextPng);
  ImageInfo i_block_info = LoadImage(kIBlockPng);
  ImageInfo o_block_info = LoadImage(kOBlockPng);
  ImageInfo s_block_info = LoadImage(kSBlockPng);
  ImageInfo z_block_info = LoadImage(kZBlockPng);
  ImageInfo j_block_info = LoadImage(kJBlockPng);
  ImageInfo l_block_info = LoadImage(kLBlockPng);
  ImageInfo t_block_info = LoadImage(kTBlockPng);
  ImageInfo single_info = LoadImage(kSinglePng);
  ImageInfo double_info = LoadImage(kDoublePng);
  ImageInfo triple_info = LoadImage(kTriplePng);
  ImageInfo tetris_info = LoadImage(kTetrisPng);
  std::array<int, kBearElementNumber> bear_handle;
  int bear_gr_handle = LoadDivGraph(kBearPng, kBearElementNumber, kBearDuckX, kBearDuckY, kBearDuckSize, kBearDuckSize, &bear_handle[0]);
  std::array<int, kBearElementNumber> duck_handle;
  int duck_gr_handle = LoadDivGraph(kDuckPng, kDuckElementNumber, kBearDuckX, kBearDuckY, kBearDuckSize, kBearDuckSize, &duck_handle[0]);
  std::array<int, kBearElementNumber> damage_bear_handle;
  int damage_bear_gr_handle = LoadDivGraph(kDamageBearPng, kBearElementNumber, kBearDuckX, kBearDuckY, kDamageBearSize, kDamageBearSize, &damage_bear_handle[0]);
  std::array<int, kDamageDuckElementNumber> damage_duck_handle;
  int damage_duck_gr_handle = LoadDivGraph(kDamageDuckPng, kDamageDuckElementNumber, kDamageDuckElementNumber, kBearDuckY, kDamageDuckSizeX, kDamageDuckSizeY, &damage_duck_handle[0]);
  std::array<int, kConfettiElementNumber> confetti_handle;
  int confetti_gr_handle = LoadDivGraph(kConfettiPng, kConfettiElementNumber, kBearDuckX, kConfettiY, kScreenSizeX, kScreenSizeY, &confetti_handle[0]);

  //サウンドデータをロードする
  int bgm_handle = LoadSoundMem(kBgmMp3);
  int move_handle = LoadSoundMem(kCursorMp3);
  int gameover_sound_handle = LoadSoundMem(kGameOverMp3);
  int fix_sound_handle = LoadSoundMem(kFixMp3);
  int hold_sound_handle = LoadSoundMem(kHoldMp3);
  int spin_sound_handle = LoadSoundMem(kSpinMp3);
  int delete_sound_handle = LoadSoundMem(kDeleteLineMp3);
  //動画のデータをロードする
  //int gameover_movie = LoadGraph(kGameOverMp4);

  //フィールドのインスタンスを生成する
  field_ = new Field(Task::kField, task_manager_);

  //ブロックのインスタンスを生成する
  block_ = new Block(Task::kBlock, task_manager_);

  //スタートUIのインスタンスを生成する
  start_ui_ = new StartUi(Task::kStartUi);

  //ポーズUIのインスタンスを生成する
  pause_ui_ = new PauseUi(Task::kPauseUi, pause_info.handle);

  //ロードした画像データのグラフィックハンドルを渡す
  field_->SetBattleBackGrHandle(battle_back_info.handle);
  field_->SetNoneGrHandle(none_info.handle);
  field_->SetLightBlueGrHandle(lightblue_info.handle);
  field_->SetBlueGrHandle(blue_info.handle);
  field_->SetEmeraldGrHandle(emerald_info.handle);
  field_->SetYellowGrHandle(yellow_info.handle);
  field_->SetOrangeGrHandle(orange_info.handle);
  field_->SetPurpleGrHandle(purple_info.handle);
  field_->SetRedGrHandle(red_info.handle);
  field_->SetLightGrHandle(light_info.handle);
  //field_->SetKeyInfoGrHandle(key_info.handle);
  field_->SetBlackGrHandle(black_info.handle);
  block_->SetLightBlueGrHandle(lightblue_info.handle);
  block_->SetBlueGrHandle(blue_info.handle);
  block_->SetEmeraldGrHandle(emerald_info.handle);
  block_->SetYellowGrHandle(yellow_info.handle);
  block_->SetOrangeGrHandle(orange_info.handle);
  block_->SetPurpleGrHandle(purple_info.handle);
  block_->SetRedGrHandle(red_info.handle);
  start_ui_->SetGrHandle(start_info.handle);
  field_->SetScoreGrHandle(score_info.handle);
  field_->SetNextGrHandle(next_info.handle);
  field_->SetLevelUpGrHandle(levelup_info.handle);
  field_->SetHoldGrHandle(hold_info.handle);
  field_->SetIMinoGrHandle(i_block_info.handle);
  field_->SetOMinoGrHandle(o_block_info.handle);
  field_->SetSMinoGrHandle(s_block_info.handle);
  field_->SetZMinoGrHandle(z_block_info.handle);
  field_->SetJMinoGrHandle(j_block_info.handle);
  field_->SetLMinoGrHandle(l_block_info.handle);
  field_->SetTMinoGrHandle(t_block_info.handle);
  field_->SetSingleGrHandle(single_info.handle);
  field_->SetDoubleGrHandle(double_info.handle);
  field_->SetTripleGrHandle(triple_info.handle);
  field_->SetTetrisGrHandle(tetris_info.handle);
  field_->SetBearGrHandle(bear_handle);
  field_->SetDamageBearGrHandle(damage_bear_handle);
  field_->SetDuckGrHandle(duck_handle);
  field_->SetDamageDuckGrHandle(damage_duck_handle);
  field_->SetConfettiHandle(confetti_handle);
  //field_->SetMovieGrHandle(gameover_movie);

  //サウンドハンドルを設定する
  SetBgmHandle(bgm_handle);
  block_->SetXMoveSoundHandle(move_handle);
  SetGameOverSoundHandle(gameover_sound_handle);
  SetFixSoundHandle(fix_sound_handle);
  SetHoldSoundHandle(hold_sound_handle);
  block_->SetSpinSoundHandle(spin_sound_handle);
  SetDeleteLineSoundHandle(delete_sound_handle);

  //ロードした画像から取得した幅をスタートUI画像の幅に設定する
  start_ui_->SetWidth(start_info.size_x);
  //ロードした画像から取得した高さをスタートUI画像の幅に設定する
  start_ui_->SetHeight(start_info.size_y);

  //ロードした画像から取得した幅の半分のサイズを計算する
  float half_width = static_cast<float> (start_info.size_x) / 2;
  //ロードした画像から取得した高さの半分のサイズを計算する
  float half_height = static_cast<float> (start_info.size_y) / 2;

  //スタートUI画像の幅の半分を設定する
  start_ui_->SetHalfWidth(half_width);
  //スタートUI画像の高さの半分を設定する
  start_ui_->SetHalfHeight(half_height);

  //ロードした画像から取得した幅をポーズUI画像の幅に設定する
  pause_ui_->SetWidth(pause_info.size_x);
  //ロードした画像から取得した高さをポーズUI画像の幅に設定する
  pause_ui_->SetHeight(pause_info.size_y);

  //ロードした画像から取得した幅の半分のサイズを計算する
  half_width = static_cast<float> (pause_info.size_x) / 2;
  //ロードした画像から取得した高さの半分のサイズを計算する
  half_height = static_cast<float> (pause_info.size_y) / 2;

  //ポーズUI画像の幅の半分を設定する
  pause_ui_->SetHalfWidth(half_width);
  //ポーズUI画像の高さの半分を設定する
  pause_ui_->SetHalfHeight(half_height);

  //生成したインスタンスをタスクマネージャーに積む
  task_manager_->AddTask(field_);
  task_manager_->AddTask(block_);
  task_manager_->AddTask(pause_ui_);
  task_manager_->AddTask(start_ui_);

  //ゲームモードを生成する
  game_mode_ = new GameMode(Task::kGameMode);
  //生成したゲームモードを、タスクマネージャーに積む
  task_manager_->AddTask(game_mode_);

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();

  //ファイルマネージャーのインスタンスを取得
  FileManager* file_manager = FileManager::GetInstance();

  // 前回までのハイスコアを読み込む
  std::vector<int> score = file_manager->ReadDataFromFile(kHighScore);

  //ハイスコアをセットする
  high_score_ = score.front();
  field_->SetHighScore(high_score_);

  //設定のファイルを読み込む
  std::vector<int> setting = file_manager->ReadDataFromFile(kSettingCSV);
  //ゴーストの表示非表示の設定をセットする
  bool ghost_display = setting.front();
  block_->SetGhostDisplay(ghost_display);
  setting.erase(setting.begin());

  //音量の設定をセットする
  int sound_volume = setting.front();
  sound_volume_ = sound_volume;
  block_->SetSoundVolume(sound_volume);

  //サウンドを再生する
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), bgm_handle_);
  PlaySoundMem(bgm_handle_, DX_PLAYTYPE_LOOP);

  //Nextに表示するブロックを初期化する
  InitNextBlocks();

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name ="time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BattleLevel::ProcessingUpdate(float time) {
  //DEBUG_PRINT(BattleLevelの毎フレーム更新処理のフェーズ処理);

  //Fieldクラスが処理中フェーズになった時から、Blockクラスを処理中フェーズにする
  Field::FieldPhaseType field_phase = field_->GetFieldPhaseType();
  StartUi::PhaseType start_phase = start_ui_->GetPhaseType();
  if (field_phase == Field::kProcessing && field_phase != pre_field_phase_ && start_phase == StartUi::kFinish) {
    pre_field_phase_ = Field::kProcessing;
    block_->SetPhaseType(Block::kPlaying);
  }

    //入力管理を取得
  InputManager* input_manager = InputManager::GetInstance();

  //FieldクラスのFieldマップをBlockクラスのFieldマップにコピーする
  CopyMap();

  //ブロックの現在の状態を取得する
  Block::PhaseType block_phase = block_->GetPhaseType();

  //Cボタンが押されたら、ブロックをHoldする
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kC) && block_phase != Block::kStop) {
    HoldBlock();
  }

  //ゲームオーバー時の黒い画像フェードインフェーズの場合
  if (phase_type_ == kFadeIn) {
    block_->SetPhaseType(Block::kFinish);
    accumulation_time_ = accumulation_time_ + time;
    if (accumulation_time_ >= kFadeInTime) {
      accumulation_time_ = 0.0f;
      field_->SetFieldGameOver(true);
    }
    bool is_finished_fade = field_->IsFadeFinished();
    if (is_finished_fade) {
      phase_type_ = kGameOver;
    }
  }

  //ゲームオーバーフェーズの場合
  if (phase_type_ == kGameOver) {
    SetGameOver();
  }

  //ブロックがラインで揃い消された場合
  bool is_delete_line = field_->IsDeleteLine();
  if (is_delete_line) {
    //スコアとレベルを更新する
    UpdateScore();
    UpdateLevel();
    field_->SetScore(score_);
    field_->SetTotalLines(total_lines_);
    field_->SetLevel(level_);
    block_->SetLevel(level_);
    block_->SetPhaseType(Block::kPlaying);
    fix_accumulation_time_ = 0.0f;
    //次のブロックを生成する
    CreateNextBlock();
    block_->SetHitBottom(false);
    is_can_fix_blocks_ = false;
  }

  //準備中フェーズの場合
  if (phase_type_ == kPreparation) {
    //スタートUI表示フェーズに変更する
    phase_type_ = kStartUiDisplay;
  }
  //スタートUI表示フェーズの場合
  else if (phase_type_ == kStartUiDisplay) {
    //スタートUIを積む
    //task_manager_->AddTask(start_ui_);
    //スタートUI終了待機フェーズに変更する
    phase_type_ = kStartUiFinishWaiting;
  }
  //スタートUI待機フェーズの場合
  else if (phase_type_ == kStartUiFinishWaiting) {
    //プレイ中フェーズに変更する
    phase_type_ = kProcessing;
  }
  //ブロック固定処理中フェーズの場合
  else if (phase_type_ == kBlockFix) {

    //ブロックを固定する
    FixBlock();

    //ブロックがラインで揃っている行数をカウントする
    field_->CountDeleteLine();

    //ブロックがラインで揃っているかの有無を取得する
    bool is_block_line = field_->IsBlockLine();

    if (is_block_line) {
      PlaySoundMem(delete_sound_handle_, DX_PLAYTYPE_BACK);

      //ラインで揃った行数を取得する
      int line_num = field_->GetLineNum();

      //消したラインの合計を更新する
      total_lines_ = total_lines_ + line_num;
      DEBUG_PRINT_VAR(total_lines_);

      //スコアの種類を保存する
      score_type_ = static_cast<ScoreType>(line_num - 1);

      block_->SetPhaseType(Block::kWaiting);
    }

    if (!is_block_line && phase_type_ != kFadeIn && phase_type_ != kGameOver) {
      block_->SetPhaseType(Block::kPlaying);
      //次のブロックを生成する
      CreateNextBlock();
    }
    
    block_->SetHitBottom(false);
    is_can_fix_blocks_ = false;
    fix_accumulation_time_ = 0.0f;

    //プレイ中フェーズに変更する
    if (phase_type_ != kFadeIn) {
      phase_type_ = kProcessing;
    }
  }
  //フィニッシュUI表示フェーズの場合
  else if (phase_type_ == kFinishUiDisplay) {

  }
  //フィニッシュUI終了待機フェーズの場合
  else if (phase_type_ == kFinishUiFinishWaiting) {
    //バトル終了フェーズに遷移する
    phase_type_ = kBattleFinish;
  }
  //バトル終了フェーズの場合
  else if (phase_type_ == kBattleFinish) {
    //BattleLevelを終了できるようにする
    is_finish_ = true;
  }

  if (GetWindowUserCloseFlag()) {
    SetEndButton();
    is_finish_ = true;
    DEBUG_PRINT(×ボタン);
  }

  //Enterが押されたら、決定ボタンが押された時のイベントを呼び出す
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDecide)) {
    OnPushDecide();
  }

  //ポーズボタンが押されたら、ポーズボタンが押された時のイベントを呼び出す
  if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kPause) && block_phase != Block::kPreraration) {
    OnPushPause();
  }

  if (field_phase == Field::kProcessing) {
    //ブロック同士の衝突を判定
    CheckIsHitBlocksBottom();
    CheckIsHitBlocksRight();
    CheckIsHitBlocksLeft();
  }

  //ブロックが一番下と接した場合
  if (block_phase == Block::kFix) {
    
    //一定時間経過後、ブロックをFieldマップと合体させる
    fix_accumulation_time_ = fix_accumulation_time_ + time;
    //DEBUG_PRINT_VAR(fix_accumulation_time_);
    if (fix_accumulation_time_ >= kLimitTime) {
      //ブロックの二次元配列の左上のY位置を取得する
      int y_coordinate = block_->GetYPosition();
      //ブロックの最下部を取得する
      int piece_bottom = block_->GetPieceBottom();
      //ブロック同士を固定して良いか確認する
      CheckIsCanFixBlocks();
      if ((y_coordinate == ((kRow + kWallWidth) - (piece_bottom + 1))) || (is_can_fix_blocks_ == true)) { 
        //ブロック固定フェーズに変更する
        phase_type_ = kBlockFix;
      }
      else {
        block_->SetHitBottom(false);
        fix_accumulation_time_ = 0;
      }
    }
  }

  //積み上がっているブロックの一番上のY位置を確認する
  int top_y = CheckTopYPos();
  //BGMの周波数が高くなっていたが積みあがっているブロックのY位置がもうすぐ天井に付きそうな高さではなくなった時、周波数を元に戻す
  if (top_y >= kDangerousY && GetFrequencySoundMem(bgm_handle_) == kFastFrequency) {
    SetFrequencySoundMem(kFrequency, bgm_handle_);
    field_->SetDangerousY(false);
  }

  return is_finish_;
}

/// <summary>
/// 毎フレームの描画処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::ProcessingRender() {
  //DEBUG_PRINT(BattleLevelの毎フレームの描画処理);
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool BattleLevel::PhaseFinalize(float time) {
  DEBUG_PRINT(BattleLevelの終了処理);

  //描画をクリアする
  ClearDrawScreen();

  //画像のグラフィックハンドルを取得する
  //取得したグラフィックハンドルを使い、リソースを破棄する
  DeleteGraph(field_->GetBattleBackGrHandle());
  //DeleteGraph(field_->GetKeyInfoGrHandle());
  DeleteGraph(field_->GetBlackGrHandle());
  DeleteGraph(GetGameOverGrHandle());
  //DeleteGraph(player_->GetDamageGrHandle(0));
  DeleteGraph(start_ui_->GetGrHandle());
  DeleteGraph(pause_ui_->GetGrHandle());
  DeleteGraph(field_->GetNoneGrHandle());
  DeleteGraph(block_->GetLightBlueGrHandle());
  DeleteGraph(block_->GetBlueGrHandle());
  DeleteGraph(block_->GetEmeraldGrHandle());
  DeleteGraph(block_->GetYellowGrHandle());
  DeleteGraph(block_->GetOrangeGrHandle());
  DeleteGraph(block_->GetPurpleGrHandle());
  DeleteGraph(block_->GetRedGrHandle());
  DeleteGraph(field_->GetLightGrHandle());
  DeleteGraph(field_->GetScoreGrHandle());
  DeleteGraph(field_->GetNextGrHandle());
  DeleteGraph(field_->GetLevelUpGrHandle());
  DeleteGraph(field_->GetHoldGrHandle());
  DeleteGraph(field_->GetIMinoGrHandle());
  DeleteGraph(field_->GetOMinoGrHandle());
  DeleteGraph(field_->GetSMinoGrHandle());
  DeleteGraph(field_->GetZMinoGrHandle());
  DeleteGraph(field_->GetJMinoGrHandle());
  DeleteGraph(field_->GetLMinoGrHandle());
  DeleteGraph(field_->GetTMinoGrHandle());
  DeleteGraph(field_->GetSingleGrHandle());
  DeleteGraph(field_->GetDoubleGrHandle());
  DeleteGraph(field_->GetTripleGrHandle());
  DeleteGraph(field_->GetTetrisGrHandle());
  DeleteGraph(field_->GetMovieGrHandle());
  DeleteGraph(field_->GetBearGrHandle(0));
  DeleteGraph(field_->GetDuckGrHandle(0));
  DeleteGraph(field_->GetDamageBearGrHandle(0));
  DeleteGraph(field_->GetConfettiHandle(0));

  //サウンドのリソースを破棄する
  DeleteSoundMem(GetBgmHandle());
  DeleteSoundMem(block_->GetXMoveSoundHandle());
  DeleteSoundMem(GetGameOverSoundHandle());
  DeleteSoundMem(GetFixSoundHandle());
  DeleteSoundMem(GetHoldSoundHandle());
  DeleteSoundMem(block_->GetSpinSoundHandle());
  DeleteSoundMem(GetDeleteLineSoundHandle());

  if (end_type_ == kUnloadTask) {

    //タスクマネージャーに積んでいたタスクを解放するためにrelease_taskに格納する
    Task* field_release_task = task_manager_->UnloadTask(kField);
    Task* block_release_task = task_manager_->UnloadTask(kBlock);
    Task* gamemode_release_task = task_manager_->UnloadTask(kGameMode);
    Task* start_release_task = task_manager_->UnloadTask(kStartUi);
    Task* pause_release_task = task_manager_->UnloadTask(kPauseUi);

    //release_taskのメモリを解放する
    delete field_release_task;
    delete block_release_task;
    delete gamemode_release_task;
    delete start_release_task;
    delete pause_release_task;

    //フェーズを破棄フェーズに変更する
    end_type_ = kDelete;
  }
  else if (end_type_ == kDelete) {

    //リソースを破棄する

    delete field_;
    field_ = nullptr;

    delete block_;
    block_ = nullptr;

    delete game_mode_;
    game_mode_ = nullptr;

    delete start_ui_;
    start_ui_ = nullptr;

    delete pause_ui_;
    pause_ui_ = nullptr;

  }
  return true;
}

/// <summary>
/// ゲームオーバーを設定する処理
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetGameOver() {
  //DEBUG_PRINT(ゲームオーバー);

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();

  //今回のスコア、消したライン数、レベルをゲーム情報に保存する
  game_info->SetResultData(score_, total_lines_, level_);

  //サウンドを再生する
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), gameover_sound_handle_);
  PlaySoundMem(gameover_sound_handle_, DX_PLAYTYPE_BACK);
  //動画を再生する
  PlayMovie(kGameOverMp4, 1, DX_MOVIEPLAYTYPE_NORMAL);

  //フェードアウトでレベルを終了する
  FadeOut();
}

/// <summary>
/// UI終了のイベント
/// </summary>
/// <param name="task_id">終了するUIのタスクID</param>
/// <returns>なし</returns>
void BattleLevel::EndUi(TaskId task_id) {
  DEBUG_PRINT(UI終了のイベント);

  //引数のキャラのタスクを解放するためにtaskに格納する
  Task* task = task_manager_->UnloadTask(task_id);

  //release_taskのメモリを解放する
  delete task;

}

/// <summary>
/// LoadImage関数の定義
/// </summary>
/// <param = "filename">画像のファイル名</param>
/// <returns>ImageInfo構造体型のinfo</returns>
BattleLevel::ImageInfo BattleLevel::LoadImage(const char* filename) {
  BattleLevel::ImageInfo info;
  info.handle = LoadGraph(filename);
  GetGraphSize(info.handle, &info.size_x, &info.size_y);
  return info;
}

/// <summary>
/// フェードイン表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "handle">グラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void BattleLevel::FadeIn(int x, int y, int handle, bool is_transparent, int fade_value, int fade) {

  DEBUG_PRINT(フェードイン開始);

  int alpha = kPlusAlpha * fade;
  DEBUG_PRINT_VAR(alpha);

  SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
  DrawGraph(x, y, handle, is_transparent);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// StopAll関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::StopAll() {
  block_->SetPhaseType(Block::kStop);
  field_->SetFieldPhaseType(Field::kStop);
}

/// <summary>
/// SetPlayingAll関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetPlayingAll() {
  block_->SetPhaseType(Block::kPlaying);
  field_->SetFieldPhaseType(Field::kProcessing);
}

/// <summary>
/// フェードアウト表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "handle">グラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void BattleLevel::FadeOut() {

  //DEBUG_PRINT(フェードアウト開始);

  //アルファ値を少しずつ変化させて表示する
  for (int alpha = 0; alpha <= kFadeValue; alpha += kPlusAlpha) {
    SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, kScreenSizeX, kScreenSizeY, Cr, TRUE);

    if (alpha >= kFadeValue) {
      is_finish_ = true;
    }

    //DEBUG_PRINT_VAR(alpha);

    //アルファ値の変化に待ち時間を設ける
    WaitTimer(kPlusAlpha);
  }

  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// SetWhiteRectangleGrHandle関数の定義
/// </summary>
/// <param = "white_rectangle_handle">文字表示のグラフィックハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetWhiteRectangleGrHandle(int white_rectangle_handle) {
  white_rectangle_handle_ = white_rectangle_handle;
}

/// <summary>
/// GetWhiteRectangleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>文字表示のグラフィックハンドル</returns>
int BattleLevel::GetWhiteRectangleGrHandle() {
  return white_rectangle_handle_;
}

/// <summary>
/// SetBgmHandle関数の定義
/// </summary>
/// <param = "bgm_handle">BGMのサウンドハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetBgmHandle(int bgm_handle) {
  bgm_handle_ = bgm_handle;
}

/// <summary>
/// GetBgmHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BGMのサウンドハンドル</returns>
int BattleLevel::GetBgmHandle() {
  return bgm_handle_;
}

/// <summary>
/// SetGameOverSoundHandle関数の定義
/// </summary>
/// <param = "gameover_sound_handle">ゲームオーバー時のサウンドハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetGameOverSoundHandle(int gameover_sound_handle) {
  gameover_sound_handle_ = gameover_sound_handle;
}

/// <summary>
/// GetGameOverSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ゲームオーバー時のサウンドハンドル</returns>
int BattleLevel::GetGameOverSoundHandle() {
  return gameover_sound_handle_;
}

/// <summary>
/// SetFixSoundHandle関数の定義
/// </summary>
/// <param = "fix_sound_handle">ブロック固定時のサウンドハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetFixSoundHandle(int fix_sound_handle) {
  fix_sound_handle_ = fix_sound_handle;
}

/// <summary>
/// GetFixSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロック固定時のサウンドハンドル</returns>
int BattleLevel::GetFixSoundHandle() {
  return fix_sound_handle_;
}

/// <summary>
/// SetHoldSoundHandle関数の定義
/// </summary>
/// <param = "hold_sound_handle">Hold時のサウンドハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetHoldSoundHandle(int hold_sound_handle) {
  hold_sound_handle_ = hold_sound_handle;
}

/// <summary>
/// GetHoldSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Hold時のサウンドハンドル</returns>
int BattleLevel::GetHoldSoundHandle() {
  return hold_sound_handle_;
}

/// <summary>
/// SetDeleteLineSoundHandle関数の定義
/// </summary>
/// <param = "delete_sound_handle">ブロックがラインで消えた時のサウンドハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetDeleteLineSoundHandle(int delete_sound_handle) {
  delete_sound_handle_ = delete_sound_handle;
}

/// <summary>
/// GetDeleteLineSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックがラインで消えた時のサウンドハンドル</returns>
int BattleLevel::GetDeleteLineSoundHandle() {
  return delete_sound_handle_;
}

/// <summary>
/// SetGameOverGrHandle関数の定義
/// </summary>
/// <param = "gameover_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void BattleLevel::SetGameOverGrHandle(int gameover_handle) {
  gameover_handle_ = gameover_handle;
}

/// <summary>
/// GetGameOverGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int BattleLevel::GetGameOverGrHandle() {
  return gameover_handle_;
}

/// <summary>
/// ブロックを固定する関数
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void BattleLevel::FixBlock() {
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), fix_sound_handle_);
  PlaySoundMem(fix_sound_handle_, DX_PLAYTYPE_BACK);

  //現在のブロックの種類を取得する
  Block::BlockType block_type = block_->GetBlockType();

  //ブロックの二次元配列の左上の現在位置を取得する
  int x_coordinate = block_->GetXPosition();
  int y_coordinate = block_->GetYPosition();

  int piece_top = block_->GetPieceTop();
  if ((y_coordinate + piece_top) <= kWallWidth) {
    DEBUG_PRINT(ブロックが天井についた);
    //BGMを止める
    StopSoundMem(bgm_handle_);
    //前回までのハイスコアより今回のスコアが大きければ、ハイスコアを更新する
    if (high_score_ < score_) {
      WriteDataToFile(kHighScore, score_);
    }

    phase_type_ = kFadeIn;
  }

  for (int i = 0; i < kBlockRow; i++) {
    for (int j = 0; j < kBlockColumn; j++) {
      Block::BlockStatus current_block = block_->GetCurrentBlock(j,i);
      if (current_block == Block::kBlockExist) {

        //ブロックが存在している位置のFieldマップの種類を変更する時に使用するX位置とY位置の変数を用意する
        int change_x = x_coordinate + j;
        int change_y = y_coordinate + i;

        //ブロックの二次元配列の中でブロックが存在している位置のFieldマップの種類をブロックの種類ごとに変更する
        for (int i = 0; i < static_cast<int>(Block::kMinoMax); i++) {
          if (block_type == static_cast<Block::BlockType>(i)) {
            field_->SetMapType(change_x, change_y, static_cast<Field::MapType>(i));
            //DEBUG_PRINT(ブロックを固定);
            break;
          }
        }
      }
    }
  }
  //FieldクラスのFieldマップをBlockクラスのFieldマップにコピーする
  CopyMap();
  //積み上がっているブロックの一番上のY位置を確認する
  int top_y = CheckTopYPos();
  //積み上がっているブロックが天井まで近付いている場合、BGMの周波数を上げる
  if (top_y < kDangerousY) {
    SetFrequencySoundMem(kFastFrequency, bgm_handle_);
    field_->SetDangerousY(true);
  }

  is_can_hold_ = true;
}

/// <summary>
/// 次に落ちるブロックを生成する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::CreateNextBlock() {

  //next_blocks_の先頭を次のブロックとして設定する
  block_->SetBlockType(next_blocks_.front());
  next_blocks_.pop();
  field_->DeleteNextTop();

  //next_blocks_の末尾にブロックを追加
  SetBlockBack();

  for (int i = 0; i < static_cast<int>(Field::kNone) + 1; i++) {
    if (next_blocks_.back() == static_cast<Block::BlockType>(i)) {
      field_->SetBlockBack(static_cast<Field::MapType>(i));
      break;
    }
  }

  //現在のブロックの種類を取得する
  Block::BlockType block_type = block_->GetBlockType();
  DEBUG_PRINT_VAR(block_type);
  //Hold以外の通常のブロック生成の場合
  if (is_can_hold_) {
    //次のブロックのスタート位置を設定する
    block_->SetXPosition(kStartBlockX + kWallWidth);
    block_->SetYPosition(kStartBlockY + kWallWidth);
    if (block_type == Block::kMinoO || block_type == Block::kMinoI) {
      block_->SetYPosition(kStartBlockY + kWallWidth - 1);
    }
    block_->SetAngleType(Block::kAngle0);
  }
}

/// <summary>
/// 下に移動する時にブロック同士が衝突したかを確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::CheckIsHitBlocksBottom() {

  //ブロックの二次元配列の左上の現在位置を取得する
  int x_coordinate = block_->GetXPosition();
  int y_coordinate = block_->GetYPosition();

  for (int i = 0; i < kBlockRow; i++) {
    for (int j = 0; j < kBlockColumn; j++) {
      Block::BlockStatus current_block = block_->GetCurrentBlock(j, i);
      if (current_block == Block::kBlockExist) {

        //Fieldマップ上のブロックが存在する位置の真下のMapTypeを確認する
        Field::MapType map_type_bottom = field_->GetMapType(x_coordinate + j, y_coordinate + i + 1);

        //Fieldマップ上のブロックが存在する位置のMapTypeがkNoneでなければ、他のブロックと衝突したと判定する
        if (map_type_bottom == Field::kMinoI || map_type_bottom == Field::kMinoO || map_type_bottom == Field::kMinoS || map_type_bottom == Field::kMinoZ || map_type_bottom == Field::kMinoJ || map_type_bottom == Field::kMinoL || map_type_bottom == Field::kMinoT) {
          block_->SetHitBottom(true);
          //DEBUG_PRINT(下でBlock同士の衝突);
          break;
        }
      }
    }
  }
}

/// <summary>
/// 右に移動する時にブロック同士が衝突したかを確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::CheckIsHitBlocksRight() {

  //ブロックの二次元配列の左上の現在位置を取得する
  int x_coordinate = block_->GetXPosition();
  int y_coordinate = block_->GetYPosition();

  for (int i = 0; i < kBlockRow; i++) {
    for (int j = 0; j < kBlockColumn; j++) {
      Block::BlockStatus current_block = block_->GetCurrentBlock(j, i);
      if (current_block == Block::kBlockExist) {

        //Fieldマップ上のブロックが存在する位置の右のMapTypeを確認する
        Field::MapType map_type_right = field_->GetMapType(x_coordinate + j + 1, y_coordinate + i);

        //Fieldマップ上のブロックが存在する位置のMapTypeがkNoneでなければ、他のブロックと衝突したと判定する
        if (map_type_right == Field::kMinoI || map_type_right == Field::kMinoO || map_type_right == Field::kMinoS || map_type_right == Field::kMinoZ || map_type_right == Field::kMinoJ || map_type_right == Field::kMinoL || map_type_right == Field::kMinoT) {
          block_->SetHitRight();
          //DEBUG_PRINT(右でBlock同士の衝突);
          break;
        }
      }
    }
  }
}

/// <summary>
/// 左に移動する時にブロック同士が衝突したかを確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::CheckIsHitBlocksLeft() {

  //ブロックの二次元配列の左上の現在位置を取得する
  int x_coordinate = block_->GetXPosition();
  int y_coordinate = block_->GetYPosition();

  for (int i = 0; i < kBlockRow; i++) {
    for (int j = 0; j < kBlockColumn; j++) {
      Block::BlockStatus current_block = block_->GetCurrentBlock(j, i);
      if (current_block == Block::kBlockExist) {

        //Fieldマップ上のブロックが存在する位置の左のMapTypeを確認する
        Field::MapType map_type_left = field_->GetMapType(x_coordinate + j - 1, y_coordinate + i);

        //Fieldマップ上のブロックが存在する位置のMapTypeがkNoneでなければ、他のブロックと衝突したと判定する
        if (map_type_left == Field::kMinoI || map_type_left == Field::kMinoO || map_type_left == Field::kMinoS || map_type_left == Field::kMinoZ || map_type_left == Field::kMinoJ || map_type_left == Field::kMinoL || map_type_left == Field::kMinoT) {
          block_->SetHitLeft();
          //DEBUG_PRINT(左でBlock同士の衝突);
          break;
        }
      }
    }
  }
}

/// <summary>
/// 固定する前にブロックが下で衝突しているかを再確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::CheckIsCanFixBlocks() {

  //ブロックの二次元配列の左上の現在位置を取得する
  int x_coordinate = block_->GetXPosition();
  int y_coordinate = block_->GetYPosition();

  for (int i = 0; i < kBlockRow; i++) {
    for (int j = 0; j < kBlockColumn; j++) {
      Block::BlockStatus current_block = block_->GetCurrentBlock(j, i);
      if (current_block == Block::kBlockExist) {

        //Fieldマップ上のブロックが存在する位置の真下のMapTypeを確認する
        Field::MapType map_type_bottom = field_->GetMapType(x_coordinate + j, y_coordinate + i + 1);

        //Fieldマップ上のブロックが存在する位置の真下のMapTypeがkNoneでなければ、他のブロックと衝突したと判定する
        if (map_type_bottom == Field::kMinoI || map_type_bottom == Field::kMinoO || map_type_bottom == Field::kMinoS || map_type_bottom == Field::kMinoZ || map_type_bottom == Field::kMinoJ || map_type_bottom == Field::kMinoL || map_type_bottom == Field::kMinoT) {
          is_can_fix_blocks_ = true;
          DEBUG_PRINT(Block同士を固定する);
          break;
        }
      }
    }
  }
}

/// <summary>
/// FieldクラスのFieldマップをBlockクラスのFieldマップにコピーする
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::CopyMap() {
  //DEBUG_PRINT(CopyMap);
  for (int i = 0; i < kTotalRow; i++) {
    for (int j = 0; j < kTotalColumn; j++) {
      Field::MapType map_type = field_->GetMapType(j, i);

      for (int k = 0; k < static_cast<int>(Field::kNone) + 1; k++) {
        if (map_type == static_cast<Field::MapType>(k)) {
          block_->SetMapType(j, i, static_cast<Block::BlockType>(k));
          Block::BlockType block_type = block_->GetMapType(j, i);
          //DEBUG_PRINT_VAR(block_type);
          break;
        }
      }
    }
  }
  //DEBUG_PRINT(CopyMap終了);
}

/// <summary>
/// Fieldのブロックが全て消されたかを確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
bool BattleLevel::CheckIsAllClear() {

  bool is_all_clear = true;

  for (int i = 0; i < kTotalRow; i++) {
    for (int j = 0; j < kTotalColumn; j++) {
      Field::MapType map_type = field_->GetMapType(j, i);
      //Fieldの要素のうち１つでもkNoneでなければ、is_all_clearをfalseにする
      if (map_type != Field::kNone) {
        is_all_clear = false;
        break;
      }
    }
  }
  return is_all_clear;
}

/// <summary>
/// スコアを更新する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::UpdateScore() {

  //スコアの種類別のスコアの定数を格納する配列
  int scores[static_cast<int>(kFourLine) + 1] = { kOneLineScore, kTwoLineScore, kThreeLineScore, kFourLineScore};

  //スコアの種類別にスコアを加算する
  for (int i = 0; i < kFourLine; i++) {
    if (score_type_ == static_cast<ScoreType>(i)) {
      score_ = score_ + scores[i];
      break;
    }
  }

  //下キーを押して移動した回数を取得する
  int softdrop_num = block_->GetSoftDropNum();
  //下キーを押して移動した回数をスコアに加算する
  score_ = score_ + softdrop_num;

  //上キーを押して移動した回数を取得する
  int harddrop_num = block_->GetHardDropNum();
  //下キーを押して移動した回数をスコアに加算する
  score_ = score_ + (harddrop_num * kHardDropScore);

  //初期値に戻す
  score_type_ = kOneLine;
  block_->SetSoftDropNum(0);
  block_->SetHardDropNum(0);
  field_->SetDeleteLine(false);
  field_->SetLineNum(0);
  field_->SetBlockLine(false);

  DEBUG_PRINT_VAR(score_);
}

/// <summary>
/// レベルを更新する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::UpdateLevel() {

  level_ = (total_lines_ / kPlusAlpha) +1 ;

  DEBUG_PRINT_VAR(level_);
}

/// <summary>
/// ブロックをHOLDする
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::HoldBlock() {
  //現在のブロックの種類を取得する
  Block::BlockType block_type = block_->GetBlockType();

  if (is_can_hold_) {
    //一度Holdするとブロックが着地するまで次のHoldをできないので、is_can_hold_をfalseにする
    is_can_hold_ = false;
    //現在のブロックの種類を、Holdするブロックを一時的に格納する変数に保存する
    pre_hold_block_ = block_type;
    //Holdされているブロックがあれば、現在のブロックにHoldされているブロックをセットする
    if (hold_block_ != Block::kMinoMax) {
      block_->SetBlockType(hold_block_);
    }
    else {
      //Holdされているブロックが無ければ新しいブロックを生成する
      CreateNextBlock();
    }
    //変更後のブロックの種類と角度を取得する
    block_->DecideMino();
    //ブロックの二次元配列の左上の現在位置を取得する
    int x_coordinate = block_->GetXPosition();
    int y_coordinate = block_->GetYPosition();
    //変更後のブロックが他のブロックや壁と重なるか確認する
    block_->CheckIsPileBlocks(x_coordinate, y_coordinate);
    bool is_hit = block_->IsHit();
    if (is_hit) {
      DEBUG_PRINT(ぶつかった);
      //is_can_hold_をtrueに戻す
      is_can_hold_ = true;
      //Holdされているブロックが無かった場合、next_blocks_の要素が変更されているので元に戻す
      if (hold_block_ == Block::kMinoMax) {
        //next_blocks_の要素を一時的に格納するtemp_queue
        std::queue<Block::BlockType> temp_queue;
        //temp_queueの先頭に変更後のGetBlockTypeを格納する
        temp_queue.push(block_->GetBlockType());
        //temp_queueの2番目以降の要素に変更後のnext_blocks_の1～4番目を格納する
        for (int i = 0; i < kNextElementNum - 1; i++) {
          temp_queue.push(next_blocks_.front());
          next_blocks_.pop();
        }
        //next_blocks_を更新する
        next_blocks_ = temp_queue;

        //Fieldのnext_blocks_の要素を一時的に格納するtemp_blocks_
        Field::MapType temp_blocks_[kNextElementNum];
        //Field表示用のnext_blocks_の要素も元に戻す
        for (int i = 0; i < static_cast<int>(Field::kNone) + 1; i++) {
          if ((block_->GetBlockType()) == static_cast<Block::BlockType>(i)) {
            temp_blocks_[0] = static_cast<Field::MapType>(i);
            break;
          }
        }
        for (int i = 0; i < kNextElementNum - 1; i++) {
          temp_blocks_[i + 1] = field_->GetNextBlockElement(i);
        }
        for (int i = 0; i < kNextElementNum; i++) {
          field_->InitNextBlocks(temp_blocks_[i], i);
        }
      }

      //ブロックの変更を元に戻す
      block_->SetBlockType(pre_hold_block_);
    }
    else if (!is_hit) {
      //新しいHoldするブロックを保存する
      hold_block_ = pre_hold_block_;

      for (int i = 0; i < static_cast<int>(Field::kNone) + 1; i++) {
        if (hold_block_ == static_cast<Block::BlockType>(i)) {
          field_->SetHoldBlock(static_cast<Field::MapType>(i));
          break;
        }
      }
      //Hold時の効果音を再生する
      ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), hold_sound_handle_);
      PlaySoundMem(hold_sound_handle_, DX_PLAYTYPE_BACK);
    }
  }
  block_->SetHit(false);
}

/// <summary>
/// WriteDataToFile関数の定義
/// </summary>
/// <param="filename">ファイル名</param>
/// <param="num">データを書き込む整数</param>
/// <returns>なし</returns>
void BattleLevel::WriteDataToFile(std::string filename, int num) {
  // CSVファイルに書き込む
  std::ofstream output_file(filename);

  // ファイルが正しく開かれたか確認
  if (output_file.is_open()) {
    // スコアをCSVファイルに書き込む
    output_file << num << std::endl;

    // ファイルを閉じる
    output_file.close();

    std::cout << num << std::endl;
  }
  else {
    std::cerr << "ファイルを開くことができなかった" << std::endl;
  }
}

/// <summary>
/// Nextブロックを初期化する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void BattleLevel::InitNextBlocks() {

  for (int i = 0; i < kNextElementNum; i++) {
    //Nextブロックを格納する配列に5つ分、ブロックをセットする
    SetBlockBack();
    for (int j = 0; j < static_cast<int>(Field::kNone) + 1; j++) {
      if (next_blocks_.back() == static_cast<Block::BlockType>(j)) {
        field_->InitNextBlocks(static_cast<Field::MapType>(j), i);
        break;
      }
    }
  }
}

/// <summary>
/// next_blocks_の末尾にブロックを追加する
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void BattleLevel::SetBlockBack() {
  //現在のブロックの種類を取得する
  Block::BlockType block_type = block_->GetBlockType();

  while (true) {

    //乱数を生成する
    std::mt19937 gen(std::random_device{}());
    //ランダムに数字を出す
    std::uniform_int_distribution<int> dist(0, static_cast<int>(Block::kWall) - 1);

    int random_index = dist(gen);

    //ランダムに出した数字をBlockType型にキャストする
    Block::BlockType selected_block_type = static_cast<Block::BlockType>(random_index);
    DEBUG_PRINT_VAR(selected_block_type);

    //キューの末尾のBlockTypeとselected_block_typeが異なれば、キューにselected_block_typeを追加
    if ((block_type != selected_block_type) && (next_blocks_.empty() == true || (next_blocks_.back() != selected_block_type))) {
      next_blocks_.push(selected_block_type);
      break;
    }
  }
}

/// <summary>
/// 積み上がっているブロックの一番上のY位置を確認する
/// </summary>
/// <param name>なし</param>
/// <returns>積み上がっているブロックの一番上のY位置</returns>
int BattleLevel::CheckTopYPos() {

  for (int i = kWallWidth; i < (kRow + kWallWidth); i++) {
    for (int j = kWallWidth; j < (kColumn + kWallWidth); j++) {
      Field::MapType map_type = field_->GetMapType(j, i);
      //Fieldの要素のうちkNone以外の要素が見つかったY位置を返す
      if (map_type != Field::kNone) {
        return i;
      }
    }
  }
}