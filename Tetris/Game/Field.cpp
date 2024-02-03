#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include "DxLib.h"
#include "Game/Field.h"
#include "Game/Level/BattleLevel.h"
#include "System/LogConsole.h"
#include "Game/GameInfo.h"
#include "Game/FadeManager.h"
#include "System/Math.h"
#include "System/FileManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {

  /// <summary>
  /// マップサイズの幅がマップチップ一つのドットサイズkMapSizeの何倍かを表す定数kMapSizeX
  /// </summary>
  static const int kMapSizeX = 18;

  /// <summary>
  /// マップサイズの長さがマップチップ一つのドットサイズkMapSizeの何倍かを表す定数kMapSizeY
  /// </summary>
  static const int kMapSizeY = 15;

  /// <summary>
  /// キー操作情報の画像のX位置を定数kKeyInfoXに格納する
  /// </summary>
  static const int kKeyInfoX = 0;

  /// <summary>
  /// キー操作情報の画像のY位置を定数kKeyInfoYに格納する
  /// </summary>
  static const int kKeyInfoY = 570;

  /// <summary>
  /// フェード値を定数kFadeValueに格納する
  /// </summary>
  static const int kFadeValue = 250;

  // <summary>
  //screen_handleの幅を定数kScreenHandleXに格納する
  /// <summary>
  static const int kScreenHandleX = 640;

  // <summary>
  //screen_handleの高さを定数kScreenHandleYに格納する
  /// <summary>
  static const int kScreenHandleY = 480;

  /// <summary>
  /// リセット時間を定数kLimitTimeに格納する
  /// </summary>
  static const float kLimitTime = 1.0f;

  /// <summary>
  /// アニメーション用のリセット時間を定数kAnimationLimitTimeに格納する
  /// </summary>
  static const float kAnimationLimitTime = 1.7f;

  /// <summary>
  /// ラインで揃った本数の表示リセット時間を定数kLineNumLimitTimeに格納する
  /// </summary>
  static const float kLineNumLimitTime = 0.6f;

  /// <summary>
  /// レベルアップした音のサウンドファイル名を定数kBgmMp3に格納する
  /// </summary>
  static const char* kBgmMp3 = "Assets/Sounds/get.mp3";

  /// <summary>
  /// フェードイン時間
  /// </summary>
  const float kFadeInTime = 0.1f;

  /// <summary>
  /// アルファ値に足しこむ値を定数kPlusAlphaに格納する
  /// </summary>
  static const int kPlusAlpha = 25;

  /// <summary>
  /// フェードインの待ち時間を定数kWaitTimeに格納する
  /// </summary>
  static const int kWaitTime = 100;

  /// <summary>
  /// ブロックがラインで揃った時の光の描画開始X位置を微調整するための定数kStartBlockLineX
  /// </summary>
  static const int kStartBlockLineX = (kMapSize * 2) - 7;

  /// <summary>
  /// ブロックがラインで揃った時の光の描画開始Y位置を微調整するための定数kStartBlockLineY
  /// </summary>
  static const int kStartBlockLineY = -5;

  /// <summary>
  /// スコア表示の描画X位置の定数kScoreX
  /// </summary>
  static const int kScoreX = 45;

  /// <summary>
  /// ハイスコア表示の描画Y位置の定数kHighScoreY
  /// </summary>
  static const int kHighScoreY = 270;

  /// <summary>
  /// 1つ目のスコア表示の描画Y位置の定数kFirstScoreY
  /// </summary>
  static const int kFirstScoreY = 330;

  /// <summary>
  /// 2つ目のスコア表示の描画Y位置の定数kSecondScoreY
  /// </summary>
  static const int kSecondScoreY = 390;

  /// <summary>
  /// 3つ目のスコア表示の描画Y位置の定数kThirdScoreY
  /// </summary>
  static const int kThirdScoreY = 450;

  /// <summary>
  /// 「HIGHSCORE」「SCORE」「LINES」「LEVEL」の文字表示の描画X位置の定数kStringX
  /// </summary>
  static const int kStringX = 62;

  /// <summary>
  /// 「HIGHSCORE」の文字表示の上段の描画Y位置の定数kHighScoreStringUpY
  /// </summary>
  static const int kHighScoreStringY = 282;

  /// <summary>
  /// 「HIGHSCORE」の文字表示の上段の描画Y位置の定数kHighScoreStringUpY
  /// </summary>
  static const int kHighScoreStringUpY = 273;

  /// <summary>
  /// 「HIGHSCORE」の文字表示の下段の描画Y位置の定数kHighScoreStringDownY
  /// </summary>
  static const int kHighScoreStringDownY = 293;

  /// <summary>
  /// 「SCORE」の文字表示の描画Y位置の定数kScoreStringY
  /// </summary>
  static const int kScoreStringY = 343;

  /// <summary>
  /// 「LINES」の文字表示の描画Y位置の定数kLinesStringY
  /// </summary>
  static const int kLinesStringY = 403;

  /// <summary>
  /// 「LEVEL」の文字表示の描画Y位置の定数kLevelStringY
  /// </summary>
  static const int kLevelStringY = 463;

  /// <summary>
  /// 「SCORE」「LINES」「LEVEL」の値の表示の描画X位置の定数kValueX
  /// </summary>
  static const int kValueX = 160;

  /// <summary>
  //白色の値を取得
  /// </summary>
  unsigned int WhiteCr = GetColor(255, 255, 255);

  /// <summary>
  //黒色の値を取得
  /// </summary>
  unsigned int BlackCr = GetColor(0, 0, 0);

  /// <summary>
  /// フォントサイズの定数kFontSize
  /// </summary>
  static const int kFontSize = 21;

  /// <summary>
  /// ハイスコアのフォントサイズの定数kHighScoreFontSize
  /// </summary>
  static const int kHighScoreFontSize = 11;

  /// <summary>
  /// フォントの太さの定数kFontThickness
  /// </summary>
  static const int kFontThickness = 10;

  /// <summary>
  /// レベルアップ表示の描画X位置の定数kLevelUpX
  /// </summary>
  static const int kLevelUpX = 15;

  /// <summary>
  /// レベルアップ表示の描画Y位置の定数kThirdLevelUpY
  /// </summary>
  static const int kThirdLevelUpY = 200;

  /// <summary>
  /// レベルアップ表示の描画Y位置の定数kSecondLevelUpY
  /// </summary>
  static const int kSecondLevelUpY = 250;

  /// <summary>
  /// レベルアップ表示の描画Y位置の定数kFirstLevelUpY
  /// </summary>
  static const int kFirstLevelUpY = 290;

  /// <summary>
  /// フォントを指定する文字列を定数kFontに格納する
  /// </summary>
  static const char* kFont = "Arial";

  /// <summary>
  /// 「HIGHSCORE」を指定する文字列を定数kHighScoreに格納する
  /// </summary>
  static const char* kHighScore = "HIGH";

  /// <summary>
  /// 「SCORE」を指定する文字列を定数kScoreに格納する
  /// </summary>
  static const char* kScore = "SCORE";

  /// <summary>
  /// 「LINES」を指定する文字列を定数kLinesに格納する
  /// </summary>
  static const char* kLines = "LINES";

  /// <summary>
  /// 「LEVEL」を指定する文字列を定数kLevelに格納する
  /// </summary>
  static const char* kLevel = "LEVEL";

  /// <summary>
  /// 「HOLD」を指定する文字列を定数kHoldに格納する
  /// </summary>
  static const char* kHold = "HOLD";

  /// <summary>
  /// 「Next」を指定する文字列を定数kNextに格納する
  /// </summary>
  static const char* kNext = "NEXT";

  /// <summary>
  /// 「%5d」を指定する文字列を定数kPercentFiveDに格納する
  /// </summary>
  static const char* kPercentFiveD = "%5d";

  /// <summary>
  /// Hold枠表示の描画X位置の定数kHoldX
  /// </summary>
  static const int kHoldX = 68;

  /// <summary>
  /// Hold枠表示の描画Y位置の定数kHoldY
  /// </summary>
  static const int kHoldY = 90;

  /// <summary>
  /// Next枠表示の描画X位置の定数kNextX
  /// </summary>
  static const int kNextX = 582;

  /// <summary>
  /// 2つ目以降のNext枠表示の描画X位置の定数kSecondNextX
  /// </summary>
  static const int kSecondNextX = 652;

  /// <summary>
  /// 2つ目のNext枠表示の描画Y位置の定数kSecondNextY
  /// </summary>
  static const int kSecondNextY = 200;

  /// <summary>
  /// 3つ目のNext枠表示の描画Y位置の定数kThirdNextY
  /// </summary>
  static const int kThirdNextY = 280;

  /// <summary>
  /// 4つ目のNext枠表示の描画Y位置の定数kForthNextY
  /// </summary>
  static const int kForthNextY = 360;

  /// <summary>
  /// 5つ目のNext枠表示の描画Y位置の定数kFifthNextY
  /// </summary>
  static const int kFifthNextY = 440;

  /// <summary>
  /// Hold文字表示の描画X位置の定数kHoldStringX
  /// </summary>
  static const int kHoldStringX = 115;

  /// <summary>
  /// Hold文字表示の描画Y位置の定数kHoldStringY
  /// </summary>
  static const int kHoldStringY = 70;

  /// <summary>
  /// Next文字表示の描画X位置の定数kNextStringX
  /// </summary>
  static const int kNextStringX = 630;

  /// <summary>
  /// Holdされたブロックの描画X位置の定数kHoldBlockX
  /// </summary>
  static const int kHoldBlockX = 105;

  /// <summary>
  /// Holdされたブロックの描画Y位置の定数kHoldBlockY
  /// </summary>
  static const int kHoldBlockY = 120;

  /// <summary>
  /// Nextのブロックの描画X位置の定数kHoldBlockX
  /// </summary>
  static const int kNextBlockX = 619;

  /// <summary>
  /// 2つ目以降のNextのブロックの描画X位置の定数kSecondNextBlockX
  /// </summary>
  static const int kSecondNextBlockX = 665;

  /// <summary>
  /// 2つ目のNextのブロックの描画Y位置の定数kSecondNextBlockY
  /// </summary>
  static const int kSecondNextBlockY = 215;

  /// <summary>
  /// 3つ目のNextのブロックの描画Y位置の定数kThirdNextBlockY
  /// </summary>
  static const int kThirdNextBlockY = 295;

  /// <summary>
  /// 4つ目のNextのブロックの描画Y位置の定数kForthNextBlockY
  /// </summary>
  static const int kForthNextBlockY = 375;

  /// <summary>
  /// 5つ目のNextのブロックの描画Y位置の定数kFifthNextBlockY
  /// </summary>
  static const int kFifthNextBlockY = 455;

  /// <summary>
  /// 効果音の最大音量を定数kVolumeに格納する
  /// </summary>
  static const int kMaxSoundEffectVolume = 255;

  /// <summary>
  /// 100％の分母を定数kHundredに格納する
  /// </summary>
  static const int kHundred = 100;

  /// <summary>
  /// 設定を保存するファイル名を定数kSettingCSVに格納する
  /// </summary>
  static const char* kSettingCSV = "setting.csv";

  /// <summary>
  /// 配列の次の要素に切り替える時間を定数の配列kChangeTimeに格納する
  /// </summary>
  static const float kChangeTime[] = { 0.4f , 0.8f ,1.2f };

  /// <summary>
  //アヒルのX座標を定数kDuckXcoordinateに格納する
  /// <summary>
  static const int kDuckXcoordinate = 452;

  /// <summary>
  //アヒルのY座標を定数kDuckYcoordinateに格納する
  /// <summary>
  static const int kDuckYcoordinate = 25;

  /// <summary>
  //クマのX座標を定数kBearXcoordinateに格納する
  /// <summary>
  static const int kBearXcoordinate = 300;

  /// <summary>
  //クマのY座標を定数kBearYcoordinateに格納する
  /// <summary>
  static const int kBearYcoordinate = 25;

  /// <summary>
  //ダメージを受けたクマのY座標を定数kDamageBearYcoordinateに格納する
  /// <summary>
  static const int kDamageBearYcoordinate = 10;

  /// <summary>
  //ダメージを受けたアヒルのX座標を定数kDamageDuckXcoordinateに格納する
  /// <summary>
  static const int kDamageDuckXcoordinate = 400;

  /// <summary>
  //ダメージを受けたアヒルのY座標を定数kDamageDuckYcoordinateに格納する
  /// <summary>
  static const int kDamageDuckYcoordinate = 10;

  /// <summary>
  //ゲームオーバーになってからキャラクターが消えるまでのfade_のカウントを定数kDeleteCharacterに格納する
  /// <summary>
  static const int kDeleteCharacter = 10;
}

/// <summary>
/// デフォルトコンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Field::Field()
  : task_manager_(nullptr)
  , map_type_(kNone)
  , field_phase_type_(kFieldInitialized)
  , now_phase_(kFieldInitialized)
  , none_handle_(0)
  , block_handle_(0)
  , battle_back_handle_(0)
  , direction_type_(kMax)
  , is_block_line_(false)
  , is_delete_line_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , sound_accumulation_time_(0)
  , key_info_handle_(0)
  , lightblue_gr_handle_(0)
  , blue_gr_handle_(0)
  , emerald_gr_handle_(0)
  , orange_gr_handle_(0)
  , yellow_gr_handle_(0)
  , purple_gr_handle_(0)
  , red_gr_handle_(0)
  , bgm_handle_(0)
  , line_y_list_{}
  , light_gr_handle_(0)
  , fade_(0)
  , gameover_fade_(0)
  , score_(0)
  , total_lines_(0)
  , level_(1)
  , score_gr_handle_(0)
  , levelup_gr_handle_(0)
  , pre_level_(1)
  , is_level_up_(false)
  , hold_gr_handle_(0)
  , i_gr_handle_(0)
  , o_gr_handle_(0)
  , s_gr_handle_(0)
  , z_gr_handle_(0)
  , j_gr_handle_(0)
  , l_gr_handle_(0)
  , t_gr_handle_(0)
  , hold_block_(kNone)
  , movie_handle_(0)
  , is_gameover_(false)
  , black_handle_(0)
  , is_finished_fade_(false)
  , high_score_(0)
  , single_gr_handle_(0)
  , double_gr_handle_(0)
  , triple_gr_handle_(0)
  , tetris_gr_handle_(0)
  , score_type_(kZeroLine)
  , next_gr_handle_(0)
  , line_num_(0)
  , sound_volume_(0)
  , standing_duck_handle_{}
  , standing_bear_handle_{}
  , damage_duck_handle_{}
  , damage_bear_handle_{}
  , index_(0)
  , is_dangerous_y_(false)
  , confetti_handle_{}
{
  DEBUG_PRINT(Fieldのデフォルトコンストラクタ);
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Field::Field(TaskId task_id, TaskManager* task_manager)
  : Task(task_id)
  , task_manager_(task_manager)
  , map_type_(kNone)
  , field_phase_type_(kFieldInitialized)
  , now_phase_(kFieldInitialized)
  , none_handle_(0)
  , block_handle_(0)
  , battle_back_handle_(0)
  , direction_type_(kMax)
  , is_block_line_(false)
  , is_delete_line_(false)
  , accumulation_time_(0.0f)
  , display_accumulation_time_(0.0f)
  , sound_accumulation_time_(0)
  , key_info_handle_(0)
  , lightblue_gr_handle_(0)
  , blue_gr_handle_(0)
  , emerald_gr_handle_(0)
  , orange_gr_handle_(0)
  , yellow_gr_handle_(0)
  , purple_gr_handle_(0)
  , red_gr_handle_(0)
  , bgm_handle_(0)
  , line_y_list_{}
  , light_gr_handle_(0)
  , fade_(0)
  , gameover_fade_(0)
  , score_(0)
  , total_lines_(0)
  , level_(1)
  , score_gr_handle_(0)
  , levelup_gr_handle_(0)
  , pre_level_(1)
  , is_level_up_(false)
  , hold_gr_handle_(0)
  , i_gr_handle_(0)
  , o_gr_handle_(0)
  , s_gr_handle_(0)
  , z_gr_handle_(0)
  , j_gr_handle_(0)
  , l_gr_handle_(0)
  , t_gr_handle_(0)
  , hold_block_(kNone)
  , movie_handle_(0)
  , is_gameover_(false)
  , black_handle_(0)
  , is_finished_fade_(false)
  , high_score_(0)
  , single_gr_handle_(0)
  , double_gr_handle_(0)
  , triple_gr_handle_(0)
  , tetris_gr_handle_(0)
  , score_type_(kZeroLine)
  , next_gr_handle_(0)
  , line_num_(0)
  , sound_volume_(0)
  , standing_duck_handle_{}
  , standing_bear_handle_{}
  , damage_duck_handle_{}
  , damage_bear_handle_{}
  , index_(0)
  , is_dangerous_y_(false)
  , confetti_handle_{}
{
  DEBUG_PRINT(Fieldのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Field::~Field() {
  DEBUG_PRINT(Fieldのデストラクタ);
}

/// <summary>
/// UpdateFrame関数の定義
/// </summary>
/// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
/// <returns>なし</returns>
void Field::UpdateFrame(float time) {

  //DEBUG_PRINT_VAR(line_num_);

  //ゲームオーバー中ではなく、ポーズ中でなければ、キャラクターアニメーション用の累積時間を更新
  if (is_gameover_ != true && field_phase_type_ != kStop) {
    accumulation_time_ = accumulation_time_ + time;
  }
  if (accumulation_time_ >= kAnimationLimitTime) {
    accumulation_time_ = 0.0f;
    index_ = 0;
  }

   //ゲームオーバーになった場合
  if (is_gameover_ == true) {
    display_accumulation_time_ = display_accumulation_time_ + time;
    if (display_accumulation_time_ >= kFadeInTime) {
      gameover_fade_++;
      display_accumulation_time_ = 0;
      //DEBUG_PRINT_VAR(fade_);
    }
  }

  for (int i = 0; i < static_cast<int>(ScoreType::kZeroLine); i++) {
    //ラインで揃った本数に応じて描画するScoreTypeを設定する
    if (line_num_ == (i + 1)) {
      score_type_ = static_cast<ScoreType>(i);
    }
    if (score_type_ == static_cast<ScoreType>(i)) {
      display_accumulation_time_ = display_accumulation_time_ + time;
      if (display_accumulation_time_ >= kLineNumLimitTime) {
        display_accumulation_time_ = 0;
        score_type_ = kZeroLine;
      }
    }
  }

  //前回のレベルよりもレベルが上がっている場合
  if (pre_level_ < level_) {
    score_type_ = kZeroLine;
    is_level_up_ = true;
  }

  if (is_level_up_ == true) {
    display_accumulation_time_ = display_accumulation_time_ + time;
    sound_accumulation_time_ = sound_accumulation_time_ + time;
    if (sound_accumulation_time_ >= kFadeInTime) {
      //レベルアップの効果音を再生する
      PlaySoundMem(bgm_handle_, DX_PLAYTYPE_BACK);
      sound_accumulation_time_ = 0.0f;
    }
    if (display_accumulation_time_ >= kLimitTime) {
      display_accumulation_time_ = 0.0f;
      is_level_up_ = false;
      pre_level_++;
    }
  }

  //DEBUG_PRINT(Fieldクラスの毎フレーム更新処理);
  if (now_phase_ != kStop) {

    bool result = false;

    switch (field_phase_type_) {

      //フェーズが初期化フェーズの場合
    case kFieldInitialized: {
      //mapdata_の初期化を行う
      result = PhaseInitialize(time);
      //初期化処理が終わったら、処理フェーズに遷移する
      if (result) {
        field_phase_type_ = kBlockInitialized;
        DEBUG_PRINT(ブロック初期化フェーズに遷移);
      }
      break;
    }

    //フェーズが初期化フェーズの場合
    case kBlockInitialized: {
      field_phase_type_ = kProcessing;
      //DEBUG_PRINT(処理フェーズに遷移);
      break;
    }
    //フェーズが処理フェーズの場合
    case FieldPhaseType::kProcessing: {
      //処理フェーズが終わったら、終了フェーズに遷移する
      result = PhaseUpdate(time);
      if (result) {
        field_phase_type_ = kEnding;
        DEBUG_PRINT(Fieldの終了フェーズに遷移);
      }
      break;
    }
                                    //フェーズが終了フェーズの場合
    case FieldPhaseType::kEnding: {
      //終了フェーズが終わったら、終了済みフェーズに遷移する
      result = PhaseFinalize(time);
      if (result) {
        field_phase_type_ = kEnded;
        DEBUG_PRINT(Fieldの終了済みフェーズに遷移);
      }
      break;
    }
                                //フェーズが終了済みの場合
    case FieldPhaseType::kEnded: {
      //DEBUG_PRINT(Fieldのフェーズが終了済み);
      break;
    }
    }

    //ブロックがラインで揃った
    if (is_block_line_ == true) {
      fade_++;
    }

  }
}

/// <summary>
/// RenderFrame関数の定義
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Field::RenderFrame() {
  //DEBUG_PRINT(Fieldクラスの毎フレーム描画処理);

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();

  //ゲーム情報からマップの左上の座標を取得する
  int map_left_x = game_info->GetMapLeftX();
  int map_left_y = game_info->GetMapLeftY();

  DrawGraph(0, 0, battle_back_handle_, TRUE);

  if (is_block_line_ == true || is_level_up_ == true) {
    //ブロックがラインで揃った時とレベルアップした時、紙吹雪のアニメーションを描画する
    for (int i = 0; i < 1; ++i) {
      DrawGraph(0, 0, confetti_handle_[i], TRUE);
    }
  }

  // 処理中かポーズ中の状態であれば、描画する
  if (field_phase_type_ == kProcessing || field_phase_type_ == kStop) {
    for (int i = 0; i < kTotalRow; i++)
    {
      for (int j = 0; j < kTotalColumn; j++)
      {
        if (i >= kWallWidth) {
          int gr_handles[static_cast<int>(kNone) + 1] = { lightblue_gr_handle_ , yellow_gr_handle_ , emerald_gr_handle_ , red_gr_handle_ , blue_gr_handle_ , orange_gr_handle_ , purple_gr_handle_ , none_handle_ };

          for (int k = 0; k < static_cast<int>(kNone) + 1; k++) {
            if (mapdata_[i][j] == static_cast<Field::MapType>(k)) {
              DrawGraph(map_left_x + (j * kMapSize), map_left_y + (i * kMapSize), gr_handles[k], TRUE);
              break;
            }
          }
        }
      }
    }
  }
  //スコア、消したライン数、レベルの表示を描画する
  ChangeFont(kFont);
  SetFontSize(kFontSize);
  SetFontThickness(kFontThickness);
  DrawGraph(kScoreX, kHighScoreY, score_gr_handle_, TRUE);
  DrawString(kStringX, kHighScoreStringUpY, kHighScore, BlackCr);
  DrawString(kStringX, kHighScoreStringDownY, kScore, BlackCr);
  DrawFormatString(kValueX, kHighScoreStringY, WhiteCr, kPercentFiveD, high_score_);
  DrawGraph(kScoreX, kFirstScoreY, score_gr_handle_, TRUE);
  DrawString(kStringX, kScoreStringY, kScore, BlackCr);
  DrawFormatString(kValueX, kScoreStringY, WhiteCr, kPercentFiveD, score_);
  DrawGraph(kScoreX, kSecondScoreY, score_gr_handle_, TRUE);
  DrawString(kStringX, kLinesStringY, kLines, BlackCr);
  DrawFormatString(kValueX, kLinesStringY, WhiteCr, kPercentFiveD, total_lines_);
  DrawGraph(kScoreX, kThirdScoreY, score_gr_handle_, TRUE);
  DrawString(kStringX, kLevelStringY, kLevel, BlackCr);
  DrawFormatString(kValueX, kLevelStringY, WhiteCr, kPercentFiveD, level_);

  //レベルアップ時の描画
  if (is_level_up_ == true) {
    DrawGraph(kLevelUpX, kThirdLevelUpY, levelup_gr_handle_, TRUE);
  }

  //ラインで揃った本数を描画
  int line_num_gr_handles[static_cast<int>(ScoreType::kZeroLine)] = { single_gr_handle_ , double_gr_handle_ , triple_gr_handle_ , tetris_gr_handle_ };
  for (int i = 0; i < static_cast<int>(ScoreType::kZeroLine); i++) {
    if (score_type_ == static_cast<ScoreType>(i)) {
      DrawGraph(kLevelUpX, kThirdLevelUpY, line_num_gr_handles[i], TRUE);
    }
  }

  //Hold表示を描画する
  DrawString(kHoldStringX, kHoldStringY, kHold, WhiteCr);
  DrawGraph(kHoldX, kHoldY, hold_gr_handle_, TRUE);
  int gr_handles[static_cast<int>(kNone)] = { i_gr_handle_ , o_gr_handle_ , s_gr_handle_ , z_gr_handle_ , j_gr_handle_ , l_gr_handle_ , t_gr_handle_ };
  for (int i = 0; i < static_cast<int>(kNone); i++) {
    if (hold_block_ == static_cast<Field::MapType>(i)) {
      DrawGraph(kHoldBlockX, kHoldBlockY, gr_handles[i], TRUE);
      break;
    }
  }

  //「NEXT」の文字を描画する
  DrawString(kNextStringX, kHoldStringY, kNext, WhiteCr);

  //先頭のNext表示を描画する
  DrawGraph(kNextX, kHoldY, hold_gr_handle_, TRUE);
  for (int i = 0; i < static_cast<int>(kNone); i++) {
    if (next_blocks_[0] == static_cast<Field::MapType>(i)) {
      DrawGraph(kNextBlockX, kHoldBlockY, gr_handles[i], TRUE);
      break;
    }
  }

  //2つ目以降のNextのブロックと枠の描画Y位置を配列に格納する
  int next_y[kNextElementNum - 1] = { kSecondNextY ,kThirdNextY ,kForthNextY ,kFifthNextY };
  int next_block_y[kNextElementNum - 1] = { kSecondNextBlockY ,kThirdNextBlockY ,kForthNextBlockY ,kFifthNextBlockY };

  //2つ目以降のNextを描画する
  for (int i = 1; i < kNextElementNum; i++) {
    DrawGraph(kSecondNextX, next_y[i - 1], next_gr_handle_, TRUE);
    for (int j = 0; j < static_cast<int>(kNone); j++) {
      if (next_blocks_[i] == static_cast<Field::MapType>(j)) {
        DrawGraph(kSecondNextBlockX, next_block_y[i - 1], gr_handles[j], TRUE);
        break;
      }
    }
  }

  //ブロックがラインで揃った時、該当するラインを光らせる描画
  for (auto& element : line_y_list_) {
    if (is_block_line_ == true) {
      if (fade_ < (kFadeValue / kPlusAlpha)) {
        FadeIn(map_left_x + kStartBlockLineX, map_left_y + (element * kMapSize) + kStartBlockLineY, light_gr_handle_, TRUE, kFadeValue, fade_, kPlusAlpha);
      }
      else {
        FadeOut(map_left_x + kStartBlockLineX, map_left_y + (element * kMapSize) + kStartBlockLineY, light_gr_handle_, TRUE, kFadeValue, fade_);
      }
    }
  }
  //ゲームオーバー時の黒い画像のフェードイン
  if (is_gameover_ == true) {
    if (gameover_fade_ <= (kFadeValue / kPlusAlpha)) {
      FadeIn(0, 0, black_handle_, TRUE, kFadeValue, gameover_fade_, kPlusAlpha);
    }
    else {
      DrawGraph(0, 0, black_handle_, TRUE);
      is_finished_fade_ = true;
    }
  }

  //キャラクター画像の配列のインデックスを累積時間によって変更する
  for (int i = 0; i < kDuckElementNumber; i++) {
    if (accumulation_time_ >= kChangeTime[i]) {
      index_ = i + 1;
    }
  }
  if (accumulation_time_ >= kChangeTime[kDuckElementNumber - 1] && accumulation_time_ < kAnimationLimitTime) {
    index_ = 1;
  }

  //キャラクターのアニメーションを表示する
  //ブロックが天井に付きそうではない場合
  if (is_dangerous_y_ == false) {
    DrawGraph(kBearXcoordinate, kBearYcoordinate, standing_bear_handle_[index_], TRUE);
    DrawGraph(kDuckXcoordinate, kDuckYcoordinate, standing_duck_handle_[index_], TRUE);
  }
  //ブロックがもうすぐ天井に付きそうな場合
  else if (is_dangerous_y_ == true && gameover_fade_ == 0) {
    DrawGraph(kBearXcoordinate, kDamageBearYcoordinate, damage_bear_handle_[index_], TRUE);
    DrawGraph(kDamageDuckXcoordinate, kDamageDuckYcoordinate, damage_duck_handle_[index_], TRUE);
  }
}

/// <summary>
/// SetBlockGrHandle関数の定義
/// </summary>
/// <param = "block_handle">ブロックのグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetBlockGrHandle(int block_handle) {
  block_handle_ = block_handle;
}

/// <summary>
/// GetBlockGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックのグラフィックハンドル</returns>
int Field::GetBlockGrHandle() {
  return block_handle_;
}

/// <summary>
/// SetNoneGrHandle関数の定義
/// </summary>
/// <param = "block_handle">何もない場合のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetNoneGrHandle(int none_handle) {
  none_handle_ = none_handle;
}

/// <summary>
/// GetNoneGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>何もない場合のグラフィックハンドル</returns>
int Field::GetNoneGrHandle() {
  return none_handle_;
}

/// <summary>
/// SetBattleBackGrHandle関数の定義
/// </summary>
/// <param = "battle_back_handle">BattleLevelの背景のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetBattleBackGrHandle(int battle_back_handle) {
  battle_back_handle_ = battle_back_handle;
}

/// <summary>
/// GetBattleBackGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BattleLevelの背景のグラフィックハンドル</returns>
int Field::GetBattleBackGrHandle() {
  return battle_back_handle_;
}

/// <summary>
/// 初期化処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::PhaseInitialize(float time) {

  //ゲーム情報のインスタンスを取得する
  GameInfo* game_info = GameInfo::GetInstance();
  //マップのサイズを設定する
  game_info->SetMapSize(kTotalColumn * kMapSize, kTotalRow * kMapSize);

  //mapdata_を初期化するための一時的な二次元配列を用意する
  int temp_initialdata[kTotalRow][kTotalColumn] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
  };

  //temp_initialdataの要素をmapdata_にコピーし、mapdata_を初期化する
  for (int i = 0; i < kTotalRow; i++) {
    for (int j = 0; j < kTotalColumn; j++) {
      int element_value = temp_initialdata[i][j];
      switch (element_value) {
      case 0:
        mapdata_[i][j] = MapType::kNone;
        break;
      case 1:
        mapdata_[i][j] = MapType::kWall;
        break;
      case 2:
        mapdata_[i][j] = MapType::kMinoI;
        break;
      }
    }
  }
  DEBUG_PRINT(mapdata_を初期化した);

  //サウンドデータをロードする
  int bgm_handle = LoadSoundMem(kBgmMp3);

  //サウンドハンドルを設定する
  SetBgmHandle(bgm_handle);

  //ファイルマネージャーのインスタンスを取得
  FileManager* file_manager = FileManager::GetInstance();

  //設定のファイルを読み込む
  std::vector<int> setting = file_manager->ReadDataFromFile(kSettingCSV);

  //音量の設定をセットする
  sound_volume_ = setting.at(1);
  DEBUG_PRINT_VAR(sound_volume_);

  //サウンドの音量を変える
  ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), bgm_handle_);

  return true;
}

/// <summary>
/// 毎フレーム更新処理のフェーズ処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::PhaseUpdate(float time) {
  return false;
}

/// <summary>
/// 終了処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>処理終了：true、処理継続：false</returns>
bool Field::PhaseFinalize(float time) {

  //mapdata_を初期化する
  for (int i = 0; i < kTotalRow; i++) {
    for (int j = 0; j < kTotalColumn; j++) {
      mapdata_[i][j] = { kNone };
    }
  }
  DEBUG_PRINT(mapdata_をクリアした);

  //サウンドのリソースを破棄する
  int bgm_handle = DeleteSoundMem(GetBgmHandle());

  return true;
}

/// <summary>
/// SetFieldPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void Field::SetFieldPhaseType(FieldPhaseType type) {
  field_phase_type_ = type;
}

/// <summary>
/// GetFieldPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
Field::FieldPhaseType Field::GetFieldPhaseType() {
  return field_phase_type_;
}

/// <summary>
/// SetBgmHandle関数の定義
/// </summary>
/// <param = "bgm_handle">BGMのサウンドハンドル</param>
/// <returns>なし</returns>
void Field::SetBgmHandle(int bgm_handle) {
  bgm_handle_ = bgm_handle;
}

/// <summary>
/// GetBgmHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>BGMのサウンドハンドル</returns>
int Field::GetBgmHandle() {
  return bgm_handle_;
}

/// <summary>
/// mapdata_の指定位置の要素を変更する関数
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "maptype">マップの種類</param>
/// <returns>なし</returns>
void Field::SetMapType(int x, int y, MapType maptype) {
  mapdata_[y][x] = maptype;
}

/// <summary>
/// mapdata_の指定位置の要素を返す関数
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <returns>マップの種類</returns>
Field::MapType Field::GetMapType(int x, int y) {
  return mapdata_[y][x];
}

/// <summary>
/// GetLightBlueGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Field::GetLightBlueGrHandle() {
  return lightblue_gr_handle_;
}

/// <summary>
/// SetLightBlueGrHandle関数の定義
/// </summary>
/// <param = "lightblue_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetLightBlueGrHandle(int lightblue_gr_handle) {
  lightblue_gr_handle_ = lightblue_gr_handle;
}

/// <summary>
/// GetBlueGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Field::GetBlueGrHandle() {
  return blue_gr_handle_;
}

/// <summary>
/// SetBlueGrHandle関数の定義
/// </summary>
/// <param = "blue_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetBlueGrHandle(int blue_gr_handle) {
  blue_gr_handle_ = blue_gr_handle;
}

/// <summary>
/// GetEmeraldGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Field::GetEmeraldGrHandle() {
  return emerald_gr_handle_;
}

/// <summary>
/// SetEmeraldGrHandle関数の定義
/// </summary>
/// <param = "emerald_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetEmeraldGrHandle(int emerald_gr_handle) {
  emerald_gr_handle_ = emerald_gr_handle;
}

/// <summary>
/// GetOrangeGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Field::GetOrangeGrHandle() {
  return orange_gr_handle_;
}

/// <summary>
/// SetOrangeGrHandle関数の定義
/// </summary>
/// <param = "orange_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetOrangeGrHandle(int orange_gr_handle) {
  orange_gr_handle_ = orange_gr_handle;
}

/// <summary>
/// GetYellowGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Field::GetYellowGrHandle() {
  return yellow_gr_handle_;
}

/// <summary>
/// SetYellowGrHandle関数の定義
/// </summary>
/// <param = "yellow_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetYellowGrHandle(int yellow_gr_handle) {
  yellow_gr_handle_ = yellow_gr_handle;
}

/// <summary>
/// GetPurpleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Field::GetPurpleGrHandle() {
  return purple_gr_handle_;
}

/// <summary>
/// SetPurpleGrHandle関数の定義
/// </summary>
/// <param = "purple_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetPurpleGrHandle(int purple_gr_handle) {
  purple_gr_handle_ = purple_gr_handle;
}

/// <summary>
/// GetRedGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Field::GetRedGrHandle() {
  return red_gr_handle_;
}

/// <summary>
/// SetRedGrHandle関数の定義
/// </summary>
/// <param = "red_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetRedGrHandle(int red_gr_handle) {
  red_gr_handle_ = red_gr_handle;
}

/// <summary>
/// GetLightGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Field::GetLightGrHandle() {
  return light_gr_handle_;
}

/// <summary>
/// SetLightGrHandle関数の定義
/// </summary>
/// <param = "light_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetLightGrHandle(int light_gr_handle) {
  light_gr_handle_ = light_gr_handle;
}

/// <summary>
/// CountDeleteLine関数の定義
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void Field::CountDeleteLine() {
  DEBUG_PRINT(削除する行を数える);

  //削除された行の数を格納する変数
  int deleted_num = 0;

  for (int i = (kRow + kWallWidth) - 1; i >= kWallWidth; i--) {
    bool fill_line = true;

    // 行にkNoneが1つでもある場合、消去しない
    for (int j = kWallWidth; j < (kColumn + kWallWidth); j++) {
      if (mapdata_[i][j] == kNone) {
        fill_line = false;
        break;
      }
    }

    // 一列がブロックで埋まっている場合、その行をカウントする
    if (fill_line) {
      deleted_num++;
      line_y_list_.push_back(i);

      //揃ったラインの数を保存する
      line_num_ = static_cast<int>(line_y_list_.size());
      //DEBUG_PRINT_VAR(deleted_num);
      //DEBUG_PRINT_VAR(i);
    }
    else if (deleted_num > 0) {
      //DEBUG_PRINT_VAR(deleted_num);
      is_block_line_ = true;
    }

  }
}

/// <summary>
/// DeleteLine関数の定義
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void Field::DeleteLine() {

  //line_y_list_の要素の個数を取得する
  std::size_t deleted_num = line_y_list_.size();
  DEBUG_PRINT_VAR(deleted_num);

  for (auto it = line_y_list_.rbegin(); it != line_y_list_.rend(); ++it) {
    int element = *it;
    // 削除された行の上の行を下に詰める
    for (int i = element; i > kWallWidth; i--) {
      if (deleted_num > 0) {
        for (int j = kWallWidth; j < (kColumn + kWallWidth); j++) {
          mapdata_[i ][j] = mapdata_[i -1][j];
          //DEBUG_PRINT_VAR(i);
        }
      }
    }
    DEBUG_PRINT_VAR(element);
    DEBUG_PRINT(行を詰めた);
  }

  // 削除された行数だけフィールドの上部の行をkNoneにする
  for (int i = kWallWidth; i < deleted_num; i++) {
    for (int j = kWallWidth; j < (kColumn + kWallWidth); j++) {
      mapdata_[i][j] = kNone;
    }
  }

  //line_y_list_を初期化する
  line_y_list_ = {};

  is_delete_line_ = true;

}

/// <summary>
/// フェードイン表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "handle">グラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void Field::FadeIn(int x, int y, int handle, bool is_transparent, int fade_value, int fade, int plus_alpha) {

  //DEBUG_PRINT(フェードイン開始);

  int alpha = plus_alpha * fade;
  //DEBUG_PRINT_VAR(alpha);

  SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
  DrawGraph(x, y, handle, is_transparent);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

}

/// <summary>
/// フェードアウト表示する関数の定義
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "handle">グラフィックハンドル</param>
/// <param = "is_transparent">透過の有無</param>
/// <returns>なし</returns>
void Field::FadeOut(int x, int y, int handle, bool is_transparent, int fade_value, int fade) {

  DEBUG_PRINT(フェードアウト開始);

  int alpha = kPlusAlpha * fade;
  DEBUG_PRINT_VAR(alpha);
  int minus_alpha = alpha - kFadeValue;
  DEBUG_PRINT_VAR(minus_alpha);

  SetDrawBlendMode(DX_BLENDMODE_ALPHA, kFadeValue - minus_alpha);
  DrawGraph(x, y, handle, is_transparent);
  SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

  if ((kFadeValue - minus_alpha) < 0) {
    is_block_line_ = false;
    //display_accumulation_time_ = 0.0f;
    fade_ = 0;
    DeleteLine();
  }

}

/// <summary>
/// IsDeleteLine関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックが揃った行を消したかの有無</returns>
bool Field::IsDeleteLine() {
  return is_delete_line_;
}

/// <summary>
/// SetDeleteLine関数の宣言
/// </summary>
/// <param= "is_delete_line">ブロックが揃った行を消したかの有無</param>
/// <returns></returns>
void Field::SetDeleteLine(bool is_delete_line) {
  is_delete_line_ = is_delete_line;
}

/// <summary>
/// IsBlockLine関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックが揃ったかの有無</returns>
bool Field::IsBlockLine() {
  return is_block_line_;
}

/// <summary>
/// SetBlockLine関数の宣言
/// </summary>
/// <param= "is_delete_line">ブロックが揃ったかの有無</param>
/// <returns></returns>
void Field::SetBlockLine(bool is_block_line) {
  is_block_line_ = is_block_line;
}

/// <summary>
/// SetLineNum関数の宣言
/// </summary>
/// <param= "line_num">揃ったラインの数</param>
/// <returns></returns>
void Field::SetLineNum(int line_num) {
  line_num_ = line_num;
}

/// <summary>
/// GetLineNum関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックが揃ったかの有無</returns>
int Field::GetLineNum() {
  return line_num_;
}

/// <summary>
/// SetScore関数の定義
/// </summary>
/// <param = "score">スコア</param>
/// <returns>なし</returns>
void Field::SetScore(int score) {
  score_ = score;
}

/// <summary>
/// SetTotalLines関数の定義
/// </summary>
/// <param = "total_lines">消したラインの合計</param>
/// <returns>なし</returns>
void Field::SetTotalLines(int total_lines) {
  total_lines_ = total_lines;
}

/// <summary>
/// SetLevel関数の定義
/// </summary>
/// <param = "level">レベル</param>
/// <returns>なし</returns>
void Field::SetLevel(int level) {
  level_ = level;
}

/// <summary>
/// SetScoreGrHandle関数の定義
/// </summary>
/// <param = "score_gr_handle">スコア表示のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetScoreGrHandle(int score_gr_handle) {
  score_gr_handle_ = score_gr_handle;
}

/// <summary>
/// GetScoreGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>スコア表示のグラフィックハンドル</returns>
int Field::GetScoreGrHandle() {
  return score_gr_handle_;
}

/// <summary>
/// SetLevelUpGrHandle関数の定義
/// </summary>
/// <param = "levelup_gr_handle">レベルアップ表示のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetLevelUpGrHandle(int levelup_gr_handle) {
  levelup_gr_handle_ = levelup_gr_handle;
}

/// <summary>
/// GetLevelUpGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>レベルアップ表示のグラフィックハンドル</returns>
int Field::GetLevelUpGrHandle() {
  return levelup_gr_handle_;
}

/// <summary>
/// SetHoldGrHandle関数の定義
/// </summary>
/// <param = "hold_gr_handle">Hold表示のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetHoldGrHandle(int hold_gr_handle) {
  hold_gr_handle_ = hold_gr_handle;
}

/// <summary>
/// GetHoldGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Hold表示のグラフィックハンドル</returns>
int Field::GetHoldGrHandle() {
  return hold_gr_handle_;
}

/// <summary>
/// SetIMinoGrHandle関数の定義
/// </summary>
/// <param = "i_gr_handle">I型ブロック画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetIMinoGrHandle(int i_gr_handle) {
  i_gr_handle_ = i_gr_handle;
}

/// <summary>
/// GetIMinoGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>I型ブロック画像のグラフィックハンドル</returns>
int Field::GetIMinoGrHandle() {
  return i_gr_handle_;
}

/// <summary>
/// SetOMinoGrHandle関数の定義
/// </summary>
/// <param = "o_gr_handle">O型ブロック画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetOMinoGrHandle(int o_gr_handle) {
  o_gr_handle_ = o_gr_handle;
}

/// <summary>
/// GetOMinoGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>O型ブロック画像のグラフィックハンドル</returns>
int Field::GetOMinoGrHandle() {
  return o_gr_handle_;
}

/// <summary>
/// SetSMinoGrHandle関数の定義
/// </summary>
/// <param = "s_gr_handle">S型ブロック画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetSMinoGrHandle(int s_gr_handle) {
  s_gr_handle_ = s_gr_handle;
}

/// <summary>
/// GetSMinoGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>S型ブロック画像のグラフィックハンドル</returns>
int Field::GetSMinoGrHandle() {
  return s_gr_handle_;
}

/// <summary>
/// SetZMinoGrHandle関数の定義
/// </summary>
/// <param = "z_gr_handle">Z型ブロック画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetZMinoGrHandle(int z_gr_handle) {
  z_gr_handle_ = z_gr_handle;
}

/// <summary>
/// GetZMinoGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Z型ブロック画像のグラフィックハンドル</returns>
int Field::GetZMinoGrHandle() {
  return z_gr_handle_;
}

/// <summary>
/// SetJMinoGrHandle関数の定義
/// </summary>
/// <param = "j_gr_handle">J型ブロック画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetJMinoGrHandle(int j_gr_handle) {
  j_gr_handle_ = j_gr_handle;
}

/// <summary>
/// GetJMinoGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>J型ブロック画像のグラフィックハンドル</returns>
int Field::GetJMinoGrHandle() {
  return j_gr_handle_;
}

/// <summary>
/// SetLMinoGrHandle関数の定義
/// </summary>
/// <param = "l_gr_handle">L型ブロック画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetLMinoGrHandle(int l_gr_handle) {
  l_gr_handle_ = l_gr_handle;
}

/// <summary>
/// GetLMinoGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>L型ブロック画像のグラフィックハンドル</returns>
int Field::GetLMinoGrHandle() {
  return l_gr_handle_;
}

/// <summary>
/// SetTMinoGrHandle関数の定義
/// </summary>
/// <param = "t_gr_handle">T型ブロック画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetTMinoGrHandle(int t_gr_handle) {
  t_gr_handle_ = t_gr_handle;
}

/// <summary>
/// GetTMinoGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>T型ブロック画像のグラフィックハンドル</returns>
int Field::GetTMinoGrHandle() {
  return t_gr_handle_;
}

/// <summary>
/// SetHoldBlock関数の定義
/// </summary>
/// <param = "hold_block">Holdされたブロックの種類</param>
/// <returns>なし</returns>
void Field::SetHoldBlock(MapType hold_block) {
  hold_block_ = hold_block;
}


/// <summary>
/// SetMovieGrHandle関数の定義
/// </summary>
/// <param = "movie_handle">動画のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetMovieGrHandle(int movie_handle) {
  movie_handle_ = movie_handle;
}

/// <summary>
/// GetMovieGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>動画のグラフィックハンドル</returns>
int Field::GetMovieGrHandle() {
  return movie_handle_;
}

/// <summary>
/// PlayMovie関数の定義
/// </summary>
/// <param>動画のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::PlayMovie(int movie_handle) {
  DEBUG_PRINT(PlayMovie);
  PlayMovieToGraph(movie_handle);
}

/// <summary>
/// SetFieldGameOver関数の宣言
/// </summary>
/// <param= "is_gameover">ゲームオーバーしたかの有無</param>
/// <returns></returns>
void Field::SetFieldGameOver(bool is_gameover) {
  is_gameover_ = is_gameover;
}

/// <summary>
/// SetBlackGrHandle関数の定義
/// </summary>
/// <param = "black_handle">黒い画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetBlackGrHandle(int black_handle) {
  black_handle_ = black_handle;
}

/// <summary>
/// GetBlackGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>黒い画像のグラフィックハンドル</returns>
int Field::GetBlackGrHandle() {
  return black_handle_;
}

/// <summary>
/// IsFadeFinished関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ゲームオーバー時のフェードインが終わったかの有無</returns>
bool Field::IsFadeFinished() {
  return is_finished_fade_;
}

/// <summary>
/// SplitString関数の定義
/// </summary>
/// <param="input">読み込んだ文字列</param>
/// <param="delimiter">区切り</param>
/// <returns>分割後の</returns>
std::vector<std::string> Field::SplitString(std::string& input, char delimiter) {
  std::istringstream stream(input);
  std::string field;
  std::vector<std::string> result;
  while (getline(stream, field, delimiter)) result.push_back(field);
  return result;
}

/// <summary>
/// SetHighScore関数の定義
/// </summary>
/// <param = "score">スコア</param>
/// <returns>なし</returns>
void Field::SetHighScore(int high_score) {
  high_score_ = high_score;
}

/// <summary>
/// SetSingleGrHandle関数の定義
/// </summary>
/// <param = "single_gr_handle"> 「SINGLE」表示用画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetSingleGrHandle(int single_gr_handle) {
  single_gr_handle_ = single_gr_handle;
}

/// <summary>
/// GetSingleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns> 「SINGLE」表示用画像のグラフィックハンドル</returns>
int Field::GetSingleGrHandle() {
  return single_gr_handle_;
}

/// <summary>
/// SetDoubleGrHandle関数の定義
/// </summary>
/// <param = "double_gr_handle"> 「DOUBLE」表示用画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetDoubleGrHandle(int double_gr_handle) {
  double_gr_handle_ = double_gr_handle;
}

/// <summary>
/// GetDoubleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns> 「DOUBLE」表示用画像のグラフィックハンドル</returns>
int Field::GetDoubleGrHandle() {
  return double_gr_handle_;
}

/// <summary>
/// SetTripleGrHandle関数の定義
/// </summary>
/// <param = "triple_gr_handle"> 「TRIPLE」表示用画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetTripleGrHandle(int triple_gr_handle) {
  triple_gr_handle_ = triple_gr_handle;
}

/// <summary>
/// GetTripleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns> 「TRIPLE」表示用画像のグラフィックハンドル</returns>
int Field::GetTripleGrHandle() {
  return triple_gr_handle_;
}

/// <summary>
/// SetTetrisGrHandle関数の定義
/// </summary>
/// <param = "tetris_gr_handle"> 「TETRIS」表示用画像のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetTetrisGrHandle(int tetris_gr_handle) {
  tetris_gr_handle_ = tetris_gr_handle;
}

/// <summary>
/// GetTetrisGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns> 「TETRIS」表示用画像のグラフィックハンドル</returns>
int Field::GetTetrisGrHandle() {
  return tetris_gr_handle_;
}

/// <summary>
/// SetNextGrHandle関数の定義
/// </summary>
/// <param = "next_gr_handle">Next表示のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetNextGrHandle(int next_gr_handle) {
  next_gr_handle_ = next_gr_handle;
}

/// <summary>
/// GetNextGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Next表示のグラフィックハンドル</returns>
int Field::GetNextGrHandle() {
  return next_gr_handle_;
}

/// <summary>
/// next_blocks_を初期化する
/// </summary>
/// <paramparam name = "next_block">追加するブロック</param>
/// <returns>なし</returns>
void Field::InitNextBlocks(MapType next_block, int i) {
  next_blocks_[i] = next_block;
}

/// <summary>
/// next_blocks_の末尾にブロックを追加する
/// </summary>
/// <paramparam name = "next_block">末尾に追加するブロック</param>
/// <returns>なし</returns>
void Field::SetBlockBack(MapType next_block) {
  next_blocks_[kNextElementNum - 1] = next_block;
}

/// <summary>
/// GetNextBlockElement関数の宣言
/// </summary>
/// <param = "element">なし</param>
/// <returns>next_blockのi番目の要素</returns>
Field::MapType Field::GetNextBlockElement(int element) {
  return next_blocks_[element];
}

/// <summary>
/// next_blocks_の先頭のブロックを削除する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
void Field::DeleteNextTop() {
  for (int i = 0; i < kNextElementNum - 1; i++) {
    next_blocks_[i] = next_blocks_[i + 1];
  }
  next_blocks_[kNextElementNum -1] = kNone;
  
}

/// <summary>
/// SetDuckGrHandle関数の定義
/// </summary>
/// <param = "duck_handle">アヒルのグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetDuckGrHandle(std::array<int, kDuckElementNumber> duck_handle) {
  standing_duck_handle_ = duck_handle;
}

/// <summary>
/// GetDuckGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>アヒルのグラフィックハンドル</returns>
int Field::GetDuckGrHandle(int element_num) {
  return standing_duck_handle_[element_num];
}

/// <summary>
/// SetDamageDuckGrHandle関数の定義
/// </summary>
/// <param = "damage_duck_handle">アヒルのグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetDamageDuckGrHandle(std::array<int, kDamageDuckElementNumber> damage_duck_handle) {
  damage_duck_handle_ = damage_duck_handle;
}

/// <summary>
/// GetDamageDuckGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>アヒルのグラフィックハンドル</returns>
int Field::GetDamageDuckGrHandle(int element_num) {
  return damage_duck_handle_[element_num];
}

/// <summary>
/// SetBearGrHandle関数の定義
/// </summary>
/// <param = "bear_handle">クマのグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetBearGrHandle(std::array<int, kBearElementNumber> bear_handle) {
  standing_bear_handle_ = bear_handle;
}

/// <summary>
/// GetBearGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>クマのグラフィックハンドル</returns>
int Field::GetBearGrHandle(int element_num) {
  return standing_bear_handle_[element_num];
}

/// <summary>
/// SetDamageBearGrHandle関数の定義
/// </summary>
/// <param = "damage_bear_handle">クマのグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetDamageBearGrHandle(std::array<int, kBearElementNumber> damage_bear_handle) {
  damage_bear_handle_ = damage_bear_handle;
}

/// <summary>
/// GetDamageBearGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>クマのグラフィックハンドル</returns>
int Field::GetDamageBearGrHandle(int element_num) {
  return damage_bear_handle_[element_num];
}

/// <summary>
/// IsDangerousY関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックがもうすぐ天井に付きそうかの有無</returns>
bool Field::IsDangerousY() {
  return is_dangerous_y_;
}

/// <summary>
/// SetDangerousY関数の宣言
/// </summary>
/// <param= "is_dangerous_y">ブロックがもうすぐ天井に付きそうかの有無</param>
/// <returns></returns>
void Field::SetDangerousY(bool is_dangerous_y) {
  is_dangerous_y_ = is_dangerous_y;
}

/// <summary>
/// GetConfettiHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Field::GetConfettiHandle(int element_num) {
  return confetti_handle_[element_num];
}

/// <summary>
/// SetConfettiHandle関数の定義
/// </summary>
/// <param = "confetti_handle">紙吹雪のグラフィックハンドル</param>
/// <returns>なし</returns>
void Field::SetConfettiHandle(std::array<int, kConfettiElementNumber> confetti_handle) {
  confetti_handle_ = confetti_handle;
}