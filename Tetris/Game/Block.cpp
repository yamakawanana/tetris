#include <iostream>
#include "Game/Block.h"
#include "System/LogConsole.h"
#include "Game/GameInfo.h"
#include "System/Input/InputManager.h"

/// <summary>
/// 無hh名名前空間
/// </summary>
namespace {
  /// <summary>
  /// リセット時間を変数limit_timeに格納する
  /// </summary>
  float limit_time = 0.0f;

  /// <summary>
  /// 初期のリセット時間を定数kFirstLimitTimeに格納する
  /// </summary>
  static const float kFirstLimitTime = 0.8f;

  /// <summary>
  /// レベル5以上のリセット時間を定数kLevelFiveLimitTimeに格納する
  /// </summary>
  static const float kLevelFiveLimitTime = 0.5f;

  /// <summary>
  /// レベル7以上のリセット時間を定数kLevelSevenLimitTimeに格納する
  /// </summary>
  static const float kLevelSevenLimitTime = 0.3f;

  /// <summary>
  /// レベル9以上のリセット時間を定数kLevelNineLimitTimeに格納する
  /// </summary>
  static const float kLevelNineLimitTime = 0.1f;

  /// <summary>
  /// 下キー入力の累積時間のリセット時間を定数kDownInputLimitTimeに格納する
  /// </summary>
  static const float kDownInputLimitTime = 0.1f;

  /// <summary>
  /// 左右キー入力の累積時間のリセット時間を定数kXInputLimitTimeに格納する
  /// </summary>
  static const float kXInputLimitTime = 0.1f;

  /// <summary>
  /// ブロックの二次元配列の左上のX座標の開始位置を定数kStartBlockXに格納する
  /// </summary>
  static const int kStartBlockX = 5;

  /// <summary>
  /// ブロックの二次元配列の左上のY座標の開始位置を定数kStartBlockYに格納する
  /// </summary>
  static const int kStartBlockY = 0;

  /// <summary>
  /// レベル5の整数を定数kLevelFiveに格納する
  /// </summary>
  static const int kLevelFive = 5;

  /// <summary>
  /// レベル7の整数を定数kLevelSevenに格納する
  /// </summary>
  static const int kLevelSeven = 7;

  /// <summary>
  /// レベル9以上の整数を定数kLevelNineに格納する
  /// </summary>
  static const int kLevelNine = 9;

  /// <summary>
  /// 座標の位置調整に使用する整数2を定数kTwoに格納する
  /// </summary>
  static const int kTwo = 2;

  /// <summary>
  /// 座標の位置調整に使用する整数3を定数kThreeに格納する
  /// </summary>
  static const int kThree = 3;

  /// <summary>
  /// 画像を透過させるαブレンドの値を定数kAlphaBlendに格納する
  /// </summary>
  static const int kAlphaBlend = 122;

  /// <summary>
  /// 効果音の最大音量を定数kVolumeに格納する
  /// </summary>
  static const int kMaxSoundEffectVolume = 255;

  /// <summary>
  /// 100％の分母を定数kHundredに格納する
  /// </summary>
  static const int kHundred = 100;
}

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Block::Block(Task task_id, TaskManager* task_manager)
  : Task(task_id)
  , now_phase_(kPreraration)
  , task_manager_(task_manager)
  , lightblue_gr_handle_(0)
  , blue_gr_handle_(0)
  , emerald_gr_handle_(0)
  , orange_gr_handle_(0)
  , yellow_gr_handle_(0)
  , purple_gr_handle_(0)
  , red_gr_handle_(0)
  , block_type_(kMinoL)
  , x_coordinate_(kStartBlockX + kWallWidth)
  , y_coordinate_(kStartBlockY + kWallWidth)
  , width_(0)
  , height_(0)
  , half_width_(0.0f)
  , half_height_(0.0f)
  , now_direction_(kNone)
  , display_x_coordinate_(0.0f)
  , display_y_coordinate_(0.0f)
  , current_block_{}
  , mapdata_{ kMinoMax }
  , angle_type_(kAngle0)
  , accumulation_time_(0.0f)
  , keyinput_accumulation_time_(0.0f)
  , piece_bottom_(0)
  , piece_top_(0)
  , piece_left_(0)
  , piece_right_(0)
  , is_hit_bottom_(false)
  , is_hit_right_(false)
  , is_hit_left_(false)
  , is_hit_(false)
  , is_found_ghost_y_(false)
  , softdrop_num_(0)
  , level_(1)
  , harddrop_num_(0)
  , rotation_status_(kRotationNone)
  , ghost_y_coordinate_(0)
  , ghost_display_(true)
  , spin_sound_handle_(0)
  , move_handle_(0)
  , sound_volume_(0)
{
  DEBUG_PRINT(Blockのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Block::~Block() {
  DEBUG_PRINT(Blockのデストラクタ);
}

/// <summary>
/// 毎フレーム更新処理
/// </summary>
/// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
/// <returns>なし</returns>
void Block::UpdateFrame(float time) {
  if (now_phase_ != kStop && now_phase_ != kFinish && now_phase_ != kPreraration) {

    //DEBUG_PRINT(Blockの毎フレーム更新処理);

    //DEBUG_PRINT_VAR(softdrop_num_);

    //DEBUG_PRINT_VAR(now_phase_);
    //DEBUG_PRINT_VAR(is_hit_bottom_);

    //ブロックの種類と角度を取得
    DecideMino();

    //ブロックの最右部、最左部、最下部を取得する
    GetPiece();

    //入力管理を取得
    InputManager* input_manager = InputManager::GetInstance();

    //ブロックを真下に着地させる場合のY位置と現在のY位置の差を取得する
    int ghost_count = CheckGhostYCount();

    //ゴースト表示させるY位置を取得する
    ghost_y_coordinate_ = y_coordinate_ + ghost_count;
    //DEBUG_PRINT_VAR(ghost_count);

    //スペースボタンかZボタンが押されたら、ブロックを回転させる
    if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kSpace) || input_manager->IsPushThisFlame(InputManager::GameKeyKind::kZ)) {
      rotation_status_ = kZKey;
      SpinBlock();
    }

    //Xボタンが押されたら、逆方向にブロックを回転させる
    if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kX)) {
      rotation_status_ = kXKey;
      SpinBlock();
    }

    //ブロックの最右部、最左部、最下部を取得する
    GetPiece();

    //レベル別に、ブロックの落下速度を設定する
    if (level_ < kLevelFive) {
      limit_time = kFirstLimitTime;
    }
    else if (level_ >= kLevelFive && level_ < kLevelSeven) {
      limit_time = kLevelFiveLimitTime;
    }
    else if (level_ >= kLevelSeven && level_ < kLevelNine) {
      limit_time = kLevelSevenLimitTime;
    }
    else if (level_ >= kLevelNine) {
      limit_time = kLevelNineLimitTime;
    }

    //右ボタンが押されたら、ブロックの二次元配列の左上のX位置を増やす
    if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kRight)) {
      
      if (x_coordinate_ < ((kColumn + kWallWidth) - (piece_right_ + 1))) {
        //移動時の効果音を再生する
        if (is_hit_right_ == false) {
          ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), move_handle_);
          PlaySoundMem(move_handle_, DX_PLAYTYPE_BACK);
        }
        x_coordinate_++;
        if (is_hit_right_ == true) {
          x_coordinate_--;
          is_hit_right_ = false;
        }
      }
      //右ボタンが長押しされている場合
    }
    else if (input_manager->IsDown(InputManager::GameKeyKind::kRight)) {
      keyinput_accumulation_time_ = keyinput_accumulation_time_ + time;
      if (keyinput_accumulation_time_ >= kXInputLimitTime) {
        if (x_coordinate_ < ((kColumn + kWallWidth) - (piece_right_ + 1))) {
          x_coordinate_++;
          if (is_hit_right_ == true) {
            x_coordinate_--;
            is_hit_right_ = false;
          }
        }
        keyinput_accumulation_time_ = 0.0f;
      }
    }
    else if (input_manager->IsReleasedKeyThisFlame(InputManager::GameKeyKind::kRight)) {
      keyinput_accumulation_time_ = 0.0f;
    }

    //左ボタンが押されたら、ブロックの二次元配列の左上のX位置を減らす
    if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kLeft)) {
      if (x_coordinate_ >= (1 - piece_left_ + kWallWidth)) {
        //移動時の効果音を再生する
        if (is_hit_left_ == false) {
          ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), move_handle_);
          PlaySoundMem(move_handle_, DX_PLAYTYPE_BACK);
        }
        x_coordinate_--;
        if (is_hit_left_ == true) {
          x_coordinate_++;
          is_hit_left_ = false;
        }
      }
      //左ボタンが長押しされている場合
    }
    else if (input_manager->IsDown(InputManager::GameKeyKind::kLeft)) {
      keyinput_accumulation_time_ = keyinput_accumulation_time_ + time;
      if (keyinput_accumulation_time_ >= kXInputLimitTime) {
        if (x_coordinate_ >= (1 - piece_left_ + kWallWidth)) {
          x_coordinate_--;
          if (is_hit_left_ == true) {
            x_coordinate_++;
            is_hit_left_ = false;
          }
        }
        keyinput_accumulation_time_ = 0.0f;
      }
    }
    else if (input_manager->IsReleasedKeyThisFlame(InputManager::GameKeyKind::kLeft)) {
      keyinput_accumulation_time_ = 0.0f;
    }

    //下ボタンが押されたら、ブロックの二次元配列の左上のY位置を増やす
    if (input_manager->IsPushThisFlame(InputManager::GameKeyKind::kDown)) {
      if (y_coordinate_ < ((kRow + kWallWidth) - (piece_bottom_ + 1))) {
        //移動時の効果音を再生する
        if (is_hit_bottom_ == false) {
          ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), move_handle_);
          PlaySoundMem(move_handle_, DX_PLAYTYPE_BACK);
        }
        y_coordinate_++;
        softdrop_num_++;
        if (is_hit_bottom_ == true) {
          y_coordinate_--;
          softdrop_num_--;
          now_phase_ = kFix;
        }
      }
      else if (y_coordinate_ == ((kRow + kWallWidth) - (piece_bottom_ + 1))) {
        now_phase_ = kFix;
      }
      //下ボタンが長押しされている場合
    }
    else if (input_manager->IsDown(InputManager::GameKeyKind::kDown)) {
      keyinput_accumulation_time_ = keyinput_accumulation_time_ + time;
      if (keyinput_accumulation_time_ >= kDownInputLimitTime) {
        if (y_coordinate_ < ((kRow + kWallWidth) - (piece_bottom_ + 1))) {
          y_coordinate_++;
          softdrop_num_++;
          if (is_hit_bottom_ == true) {
            y_coordinate_--;
            softdrop_num_--;
            now_phase_ = kFix;
          }
        }
        else if (y_coordinate_ == ((kRow + kWallWidth) - (piece_bottom_ + 1))) {
          now_phase_ = kFix;
        }
        keyinput_accumulation_time_ = 0.0f;
      }
    }
    else if (input_manager->IsReleasedKeyThisFlame(InputManager::GameKeyKind::kDown)) {
      keyinput_accumulation_time_ = 0.0f;
    }

    //上キーが押された場合、一気に下に移動する
    if (input_manager->IsDown(InputManager::GameKeyKind::kUp)) {
      if ((y_coordinate_ < ((kRow + kWallWidth) - (piece_bottom_ + 1)))) {
        int harddrop_num = CheckIsHitBlocksBottom();
        //移動時の効果音を再生する
        if (harddrop_num > 0) {
          ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), move_handle_);
          PlaySoundMem(move_handle_, DX_PLAYTYPE_BACK);
        }
        harddrop_num_ = harddrop_num_ + harddrop_num;
        //DEBUG_PRINT_VAR(harddrop_num);
        //DEBUG_PRINT_VAR(harddrop_num_);
        y_coordinate_ = y_coordinate_ + harddrop_num;
        if (is_hit_bottom_ == true) {
          now_phase_ = kFix;
        }
      }
      else if (y_coordinate_ == ((kRow + kWallWidth) - (piece_bottom_ + 1))) {
        now_phase_ = kFix;
      }
    }

    //重力で落下する処理
    accumulation_time_ = accumulation_time_ + time;
    if (accumulation_time_ >= limit_time) {
      //DEBUG_PRINT_VAR(is_hit_bottom_);
      //ブロックの二次元配列の左上のY位置を増やす
      if ((y_coordinate_ < ((kRow + kWallWidth) - (piece_bottom_ + 1)))) {
        y_coordinate_++;
        if (is_hit_bottom_ == true) {
          y_coordinate_--;
          now_phase_ = kFix;
        }
      }
      else if (y_coordinate_ == ((kRow + kWallWidth) - (piece_bottom_ + 1))) {
        now_phase_ = kFix;
      }
      accumulation_time_ = 0.0f;
    }

    //ブロックの最右部、最左部、最下部を取得する
    GetPiece();
  }
}

/// 毎フレーム描画処理
/// </remarks>
/// <param>なし</param>
/// <returns>なし</returns>
void Block::RenderFrame() {
  //DEBUG_PRINT(Blockの毎フレーム描画処理);
  if (now_phase_ != kFinish && now_phase_ != kPreraration && now_phase_ != kWaiting) {
    //X位置を取得する
    int x_coordinate = GetXPosition();
    //DEBUG_PRINT_VAR(x_coordinate);
    //Y位置を取得する
    int y_coordinate = GetYPosition();
    //DEBUG_PRINT_VAR(y_coordinate);

    //幅を取得する
    int width = GetWidth();

    //高さを取得する
    int height = GetHeight();

    //半分の幅を取得する
    float half_width = GetHalfWidth();

    //半分の高さを取得する
    float half_height = GetHalfHeight();

    //ゲーム情報のインスタンスを取得する
    GameInfo* game_info = GameInfo::GetInstance();

    //ゲーム情報からマップの左上の座標を取得する
    int map_left_x = game_info->GetMapLeftX();
    int map_left_y = game_info->GetMapLeftY();

    //表示用の位置を使って描画する
    for (int i = 0; i < kBlockRow; i++)
    {
      for (int j = 0; j < kBlockColumn; j++)
      {
        int gr_handles[static_cast<int>(Block::kMinoMax)] = { lightblue_gr_handle_ , yellow_gr_handle_ , emerald_gr_handle_ , red_gr_handle_ , blue_gr_handle_ , orange_gr_handle_ , purple_gr_handle_  };
        if (current_block_[i][j] == kBlockExist && (y_coordinate_ + i) >= kWallWidth)
        {
          for (int k = 0; k < static_cast<int>(Block::kMinoMax); k++) {
            if (block_type_ == static_cast<Block::BlockType>(k)) {
              DrawGraph((x_coordinate_ * kMapSize) + map_left_x + (j * kMapSize), (y_coordinate_ * kMapSize) + map_left_y + (i * kMapSize), gr_handles[k], TRUE);
              SetDrawBlendMode(DX_BLENDMODE_ALPHA, kAlphaBlend);
              if (ghost_display_) {
                //ゴースト表示を描画する
                DrawGraph((x_coordinate_ * kMapSize) + map_left_x + (j * kMapSize), (ghost_y_coordinate_ * kMapSize) + map_left_y + (i * kMapSize), gr_handles[k], TRUE);
              }
              SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
              break;
            }
          }
        }
      }
    }
  }
}

/// <summary>
/// GetLightBlueGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Block::GetLightBlueGrHandle() {
  return lightblue_gr_handle_;
}

/// <summary>
/// SetLightBlueGrHandle関数の定義
/// </summary>
/// <param = "lightblue_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Block::SetLightBlueGrHandle(int lightblue_gr_handle) {
  lightblue_gr_handle_ = lightblue_gr_handle;
}

/// <summary>
/// GetBlueGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Block::GetBlueGrHandle() {
  return blue_gr_handle_;
}

/// <summary>
/// SetBlueGrHandle関数の定義
/// </summary>
/// <param = "blue_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Block::SetBlueGrHandle(int blue_gr_handle) {
  blue_gr_handle_ = blue_gr_handle;
}

/// <summary>
/// GetEmeraldGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Block::GetEmeraldGrHandle() {
  return emerald_gr_handle_;
}

/// <summary>
/// SetEmeraldGrHandle関数の定義
/// </summary>
/// <param = "emerald_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Block::SetEmeraldGrHandle(int emerald_gr_handle) {
  emerald_gr_handle_ = emerald_gr_handle;
}

/// <summary>
/// GetOrangeGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Block::GetOrangeGrHandle() {
  return orange_gr_handle_;
}

/// <summary>
/// SetOrangeGrHandle関数の定義
/// </summary>
/// <param = "orange_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Block::SetOrangeGrHandle(int orange_gr_handle) {
  orange_gr_handle_ = orange_gr_handle;
}

/// <summary>
/// GetYellowGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Block::GetYellowGrHandle() {
  return yellow_gr_handle_;
}

/// <summary>
/// SetYellowGrHandle関数の定義
/// </summary>
/// <param = "yellow_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Block::SetYellowGrHandle(int yellow_gr_handle) {
  yellow_gr_handle_ = yellow_gr_handle;
}

/// <summary>
/// GetPurpleGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Block::GetPurpleGrHandle() {
  return purple_gr_handle_;
}

/// <summary>
/// SetPurpleGrHandle関数の定義
/// </summary>
/// <param = "purple_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Block::SetPurpleGrHandle(int purple_gr_handle) {
  purple_gr_handle_ = purple_gr_handle;
}

/// <summary>
/// GetRedGrHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>グラフィックハンドル</returns>
int Block::GetRedGrHandle() {
  return red_gr_handle_;
}

/// <summary>
/// SetRedGrHandle関数の定義
/// </summary>
/// <param = "red_gr_handle">グラフィックハンドル</param>
/// <returns>なし</returns>
void Block::SetRedGrHandle(int red_gr_handle) {
  red_gr_handle_ = red_gr_handle;
}

/// <summary>
/// SetXPosition関数の定義
/// </summary>
/// <param = "x_coordinate">X座標</param>
/// <returns>なし</returns>
void Block::SetXPosition(int x_coordinate) {
  x_coordinate_ = x_coordinate;
}

/// <summary>
/// GetXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>X座標</returns>
int Block::GetXPosition() {
  return x_coordinate_;
}

/// <summary>
/// SetYPosition関数の定義
/// </summary>
/// <param = "y_coordinate">Y座標</param>
/// <returns>なし</returns>
void Block::SetYPosition(int y_coordinate) {
  y_coordinate_ = y_coordinate;
}

/// <summary>
/// GetYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>Y座標</returns>
int Block::GetYPosition() {
  return y_coordinate_;
}

/// <summary>
/// SetWidth関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void Block::SetWidth(int size_x) {
  width_ = size_x;
}

/// <summary>
/// GetWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int Block::GetWidth() {
  return width_;
}

/// <summary>
/// SetHeight関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void Block::SetHeight(int size_y) {
  height_ = size_y;
}

/// <summary>
/// GetHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さ</returns>
int Block::GetHeight() {
  return height_;
}

/// <summary>
/// SetHalfWidth関数の定義
/// </summary>
/// <param>画像の幅の半分</param>
/// <returns>なし</returns>
void Block::SetHalfWidth(float size_half_x) {
  half_width_ = size_half_x;
}

/// <summary>
/// GetHalfWidth関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅の半分</returns>
float Block::GetHalfWidth() {
  return half_width_;
}

/// <summary>
/// SetHalfHeight関数の定義
/// </summary>
/// <param>画像の高さの半分</param>
/// <returns>なし</returns>
void Block::SetHalfHeight(float size_half_y) {
  half_height_ = size_half_y;
}

/// <summary>
/// GetHalfHeight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の高さの半分</returns>
float Block::GetHalfHeight() {
  return half_height_;
}

/// <summary>
/// SetBlockType関数の定義
/// </summary>
/// <param = "character_type">ブロックの種類</param>
/// <returns>なし</returns>
void Block::SetBlockType(BlockType block_type) {
  block_type_ = block_type;
}

/// <summary>
/// GetBlockType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>キャラクターの種類</returns>
Block::BlockType Block::GetBlockType() {
  return block_type_;
}

/// <summary>
/// SetDirectionType関数の定義
/// </summary>
/// <param = "direction">方向の種類</param>
/// <returns>なし</returns>
void Block::SetDirectionType(DirectionType direction) {
  now_direction_ = direction;
}

/// <summary>
/// GetDirectionType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
Block::DirectionType Block::GetDirectionType() {
  return now_direction_;
}

/// <summary>
/// SetPhaseType関数の定義
/// </summary>
/// <param = "type">方向の種類</param>
/// <returns>なし</returns>
void Block::SetPhaseType(PhaseType type) {
  now_phase_ = type;
}

/// <summary>
/// GetPhaseType関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>方向の種類</returns>
Block::PhaseType Block::GetPhaseType() {
  return now_phase_;
}

/// <summary>
/// SetDisplayXPosition関数の定義
/// </summary>
/// <param = "display_x_coordinate">表示用のX座標</param>
/// <returns>なし</returns>
void Block::SetDisplayXPosition(float display_x_coordinate) {
  display_x_coordinate_ = display_x_coordinate;
}

/// <summary>
/// GetDisplayXPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>表示用のX座標</returns>
float Block::GetDisplayXPosition() {
  return display_x_coordinate_;
}

/// <summary>
/// SetDisplayYPosition関数の定義
/// </summary>
/// <param = "display_y_coordinate">表示用のY座標</param>
/// <returns>なし</returns>
void Block::SetDisplayYPosition(float display_y_coordinate) {
  display_y_coordinate_ = display_y_coordinate;
}

/// <summary>
/// GetDisplayYPosition関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>表示用のY座標</returns>
float Block::GetDisplayYPosition() {
  return display_y_coordinate_;
}

/// <summary>
/// DecideMino関数の定義
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void Block::DecideMino() {
  //ブロックの種類ごとに分ける

  for (int i = 0; i < kBlockRow; i++) {
    for (int j = 0; j < kBlockColumn; j++) {

      switch (block_type_) {

        //I型
      case kMinoI:
        //ブロックの角度ごとに分ける
        switch (angle_type_) {
        case kAngle0:
          current_block_[i][j] = (i == 1) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle90:
          current_block_[i][j] = (j == 1) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle180:
          current_block_[i][j] = (i == kTwo) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle270:
          current_block_[i][j] = (j == kTwo) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;
        }
        break;

        //O型
      case kMinoO:
          current_block_[i][j] = ((i == 1 || i == kTwo) && (j == 1 || j == kTwo)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
        break;

        //S型
      case kMinoS:
        switch (angle_type_) {
        case kAngle0:
          current_block_[i][j] = ((i == 0 && (j == 1 || j == kTwo)) || (i == 1 && (j == 0 || j == 1))) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle90:
          current_block_[i][j] = ((i == 0 && j == 0) || (i == 1 && (j == 0 || j == 1)) || (i == kTwo && j == 1)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle180:
          current_block_[i][j] = ((i == 1 && (j == 1 || j == kTwo)) || (i == kTwo && (j == 0 || j == 1))) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle270:
          current_block_[i][j] = ((i == 0 && j == 1) || (i == 1 && (j == 1 || j == kTwo)) || (i == kTwo && j == kTwo)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;
        }
        break;

        //Z型
      case kMinoZ:
        switch (angle_type_) {

        case kAngle0:
          current_block_[i][j] = ((i == 0 && (j == 0 || j == 1)) || (i == 1 && (j == 1 || j == kTwo))) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle90:
          current_block_[i][j] = ((j == 0 && (i == kTwo || i == 1)) || (j == 1 && (i == 1 || i == 0))) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle180:
          current_block_[i][j] = ((i == 1 && (j == 0 || j == 1)) || (i == kTwo && (j == 1 || j == kTwo))) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle270:
          current_block_[i][j] = ((j == 1 && (i == kTwo || i == 1)) || (j == kTwo && (i == 1 || i == 0))) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;
        }
        break;

        //J型
      case kMinoJ:
        switch (angle_type_) {
        case kAngle0:
          current_block_[i][j] = ((i == 1 && j != kThree) || (j == 0 && i == 0)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle90:
          current_block_[i][j] = ((j == 1 && i != kThree) || (j == 0 && i == kTwo)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle180:
          current_block_[i][j] = ((i == 1 && j != kThree) || (j == kTwo && i == kTwo)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle270:
          current_block_[i][j] = ((j == 1 && i != kThree) || (j == kTwo && i == 0)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;
        }
        break;

        //L型
      case kMinoL:
        switch (angle_type_) {
        case kAngle0:
          current_block_[i][j] = ((i == 1 && j != kThree) || (j == kTwo && i == 0)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle90:
          current_block_[i][j] = ((j == 1 && i != kThree) || (j == 0 && i == 0)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle180:
          current_block_[i][j] = ((i == 1 && j != kThree) || (j == 0 && i == kTwo)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle270:
          current_block_[i][j] = ((j == 1 && i != kThree) || (j == kTwo && i == kTwo)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;
        }
        break;

        //T型
      case kMinoT:
        switch (angle_type_) {
        case kAngle0:
          current_block_[i][j] = ((i == 1 && j != kThree) || (j == 1 && i == 0)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle90:
          current_block_[i][j] = ((j == 1 && i != kThree) || (j == 0 && i == 1)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle180:
          current_block_[i][j] = ((i == 1 && j != kThree) || (j == 1 && i == kTwo)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;

        case kAngle270:
          current_block_[i][j] = ((j == 1 && i != kThree) || (j == kTwo && i == 1)) ? BlockStatus::kBlockExist : BlockStatus::kBlockNone;
          break;
        }
        break;
      }
    }
  }
}

/// <summary>
/// GetPieceTop関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックの最上部の位置</returns>
int Block::GetPieceTop() {
  int x, y;
  for (y = 0; y < kBlockRow; y++) {
    for (x = 0; x < kBlockColumn; x++) {
      if (current_block_[y][x] == kBlockExist) {
        return y;
      }
    }
  }
  return 0;
}

/// <summary>
/// GetPieceBottom関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックの最下部の位置</returns>
int Block::GetPieceBottom() {
  int x, y;
  for (y = kBlockRow - 1; y >= 0; y--) {
    for (x = 0; x < kBlockColumn; x++) {
      if (current_block_[y][x] == kBlockExist) {
        return y;
      }
    }
  }
  return 0;
}

/// <summary>
/// GetPieceLeft関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックの最左部の位置</returns>
int Block::GetPieceLeft() {
  int x, y;

  for (x = 0; x < kBlockColumn; x++) {
    for (y = 0; y < kBlockRow; y++) {
      if (current_block_[y][x] == kBlockExist) {
        return x;
      }
    }
  }
  return 0;
}

/// <summary>
/// GetPieceRight関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックの最右部の位置</returns>
int Block::GetPieceRight() {
  int x, y;
  for (x = kBlockColumn - 1; x >= 0; x--) {
    for (y = 0; y < kBlockRow; y++) {
      if (current_block_[y][x] == kBlockExist) {
        return x;
      }
    }
  }
  return 0;
}

/// <summary>
/// SpinBlock関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Block::SpinBlock() {

  //X位置とY位置を一時的に別の変数に格納する
  int x_coordinate = x_coordinate_;
  int y_coordinate = y_coordinate_;

  //ブロックを回転させる
  if (rotation_status_ == kZKey) {
    //Zかスペースキーを押された場合
    RotateBlock();
  }
  else {
    //Xキーを押された場合
    RevertRotation();
  }

  //ブロックの最右部、最左部、最下部を取得する
  GetPiece();

  //ブロック同士が重なるか確認する
  CheckIsPileBlocks(x_coordinate, y_coordinate);

  //Iブロック以外の場合
  if (block_type_ != kMinoI) {
    //重なる場合、スーパーローテーションの第一法則
    x_coordinate = SuperRotateOneAndFour(x_coordinate);

    //ブロック同士が重なるか確認する
    CheckIsPileBlocks(x_coordinate, y_coordinate);

    //重なる場合、スーパーローテーションの第二法則
    if (is_hit_ == true) {
      DEBUG_PRINT(スーパーローテーションの第二法則);
      switch (angle_type_) {

      case kAngle0:
      case kAngle180:
        //下に１つ移動
        y_coordinate++;
        break;

      case kAngle90:
      case kAngle270:
        //上に１つ移動
        y_coordinate--;
        break;
      }
      is_hit_ = false;
    }

    //ブロック同士が重なるか確認する
    CheckIsPileBlocks(x_coordinate, y_coordinate);

    //重なる場合、スーパーローテーションの第三法則
    if (is_hit_ == true) {
      DEBUG_PRINT(スーパーローテーションの第三法則);
      switch (angle_type_) {

      case kAngle0:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、左に１つ移動、上に３つ移動
          x_coordinate--;
        }
        else {
          //Xキーを押された場合、右に１つ移動、上に３つ移動
          x_coordinate++;
        }
        y_coordinate = y_coordinate - kThree;
        break;

      case kAngle90:
        //左に１つ移動、下に３つ移動
        x_coordinate--;
        y_coordinate = y_coordinate + kThree;
        break;

      case kAngle180:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、右に１つ移動、上に３つ移動
          x_coordinate++;
        }
        else {
          //Xキーを押された場合、左に１つ移動、上に３つ移動
          x_coordinate--;
        }
        y_coordinate = y_coordinate - kThree;
        break;

      case kAngle270:
        //右に１つ移動、下に３つ移動
        x_coordinate++;
        y_coordinate = y_coordinate + kThree;
        break;
      }
      is_hit_ = false;
    }

    //ブロック同士が重なるか確認する
    CheckIsPileBlocks(x_coordinate, y_coordinate);

    //重なる場合、スーパーローテーションの第四法則
    x_coordinate = SuperRotateOneAndFour(x_coordinate);
  }

  if (block_type_ == kMinoI) {
    //重なる場合、スーパーローテーションの第一法則
    if (is_hit_ == true) {
      DEBUG_PRINT(スーパーローテーションの第一法則);
      switch (angle_type_) {

      case kAngle0:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、右に２つ移動
          x_coordinate = x_coordinate + kTwo;
        }
        else {
          //Xキーを押された場合、左に２つ移動
          x_coordinate = x_coordinate - kTwo;
        }
        break;

      case kAngle90:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、左に１つ移動
          x_coordinate--;
        }
        else {
          //Xキーを押された場合、右に２つ移動
          x_coordinate = x_coordinate + kTwo;
        }
        break;

      case kAngle180:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、右に１つ移動
          x_coordinate++;
        }
        else {
          //Xキーを押された場合、左に１つ移動
          x_coordinate--;
        }
        break;

      case kAngle270:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、右に１つ移動
          x_coordinate++;
        }
        else {
          //Xキーを押された場合、左に２つ移動
          x_coordinate = x_coordinate - kTwo;
        }
        break;
      }
      is_hit_ = false;
    }

    //ブロック同士が重なるか確認する
    CheckIsPileBlocks(x_coordinate, y_coordinate);

    //重なる場合、スーパーローテーションの第二法則
    if (is_hit_ == true) {
      DEBUG_PRINT(スーパーローテーションの第二法則);
      switch (angle_type_) {

      case kAngle0:
      case kAngle180:
      case kAngle270:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、左に３つ移動
          x_coordinate = x_coordinate - kThree;
        }
        else {
          //Xキーを押された場合、右に３つ移動
          x_coordinate = x_coordinate + kThree;
        }
        break;

      case kAngle90:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、右に３つ移動
          x_coordinate = x_coordinate + kThree;
        }
        else {
          //Xキーを押された場合、左に３つ移動
          x_coordinate = x_coordinate - kThree;
        }
        break;
      }
      is_hit_ = false;
    }

    //ブロック同士が重なるか確認する
    CheckIsPileBlocks(x_coordinate, y_coordinate);

    //重なる場合、スーパーローテーションの第三法則
    if (is_hit_ == true) {
      DEBUG_PRINT(スーパーローテーションの第三法則);
      switch (angle_type_) {

      case kAngle0:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、右に３つ移動、上に１つ移動
          x_coordinate = x_coordinate + kThree;
          y_coordinate--;
        }
        else {
          //Xキーを押された場合、右に２つ移動
          y_coordinate = y_coordinate + kTwo;
        }
        break;

      case kAngle90:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、左に３つ移動、上に２つ移動
          x_coordinate = x_coordinate - kThree;
          y_coordinate = y_coordinate - kTwo;
        }
        else {
          //Xキーを押された場合、右に３つ移動、上に１つ移動
          x_coordinate = x_coordinate + kThree;
          y_coordinate--;
        }
        break;

      case kAngle180:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、右に１つ移動
          y_coordinate++;
        }
        else {
          //Xキーを押された場合、左に３つ移動、上に２つ移動
          x_coordinate = x_coordinate - kThree;
          y_coordinate = y_coordinate - kTwo;
        }
        break;

      case kAngle270:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、右に３つ移動、下に２つ移動
          x_coordinate = x_coordinate + kThree;
          y_coordinate = y_coordinate + kTwo;
        }
        else {
          //Xキーを押された場合、左に３つ移動、下に１つ移動
          x_coordinate = x_coordinate - kThree;
          y_coordinate++;
        }
        break;
      }
      is_hit_ = false;
    }

    //ブロック同士が重なるか確認する
    CheckIsPileBlocks(x_coordinate, y_coordinate);

    //重なる場合、スーパーローテーションの第四法則
    if (is_hit_ == true) {
      DEBUG_PRINT(スーパーローテーションの第四法則);
      switch (angle_type_) {

      case kAngle0:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、左に３つ移動、下に３つ移動
          x_coordinate = x_coordinate - kThree;
          y_coordinate = y_coordinate + kThree;
        }
        else {
          //Xキーを押された場合、左に３つ移動、上に３つ移動
          x_coordinate = x_coordinate - kThree;
          y_coordinate = y_coordinate - kThree;
        }
        break;

      case kAngle90:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、右に３つ移動、下に３つ移動
          x_coordinate = x_coordinate + kThree;
          y_coordinate = y_coordinate + kThree;
        }
        else {
          //Xキーを押された場合、左に３つ移動、下に３つ移動
          x_coordinate = x_coordinate - kThree;
          y_coordinate = y_coordinate + kThree;
        }
        break;

      case kAngle180:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、右に３つ移動、上に３つ移動
          x_coordinate = x_coordinate + kThree;
          y_coordinate = y_coordinate - kThree;
        }
        else {
          //Xキーを押された場合、右に３つ移動、下に３つ移動
          x_coordinate = x_coordinate + kThree;
          y_coordinate = y_coordinate + kThree;
        }
        break;

      case kAngle270:
        if (rotation_status_ == kZKey) {
          //Zかスペースキーを押された場合、左に３つ移動、上に３つ移動
          x_coordinate = x_coordinate - kThree;
          y_coordinate = y_coordinate - kThree;
        }
        else {
          //Xキーを押された場合、右に３つ移動、上に３つ移動
          x_coordinate = x_coordinate + kThree;
          y_coordinate = y_coordinate - kThree;
        }
        break;
      }
      is_hit_ = false;
    }
  }

  //ブロック同士が重なるか確認する
  CheckIsPileBlocks(x_coordinate, y_coordinate);

  //回転の効果音を再生する
  if (is_hit_ == false && block_type_ != kMinoO) {
    ChangeVolumeSoundMem(static_cast<int>(kMaxSoundEffectVolume * (static_cast<float>(sound_volume_) / static_cast<float>(kHundred))), spin_sound_handle_);
    PlaySoundMem(spin_sound_handle_, DX_PLAYTYPE_BACK);
  }

  if (is_hit_ == true) {
    DEBUG_PRINT(回転できない);
    //回転を元に戻す
    if (rotation_status_ == kZKey) {
      //Zかスペースキーを押された場合
      RevertRotation();
    }
    else {
      //Xキーを押された場合
      RotateBlock();
    }
    //位置を元の位置に戻す
    x_coordinate = x_coordinate_;
    y_coordinate = y_coordinate_;
    is_hit_ = false;
  }
  x_coordinate_ = x_coordinate;
  y_coordinate_ = y_coordinate;
  rotation_status_ = kRotationNone;
  //ブロックの種類と角度を取得
  DecideMino();

  //ブロックを真下に着地させる場合のY位置と現在のY位置の差を取得する
  int ghost_count = CheckGhostYCount();

  //ゴースト表示させるY位置を取得する
  ghost_y_coordinate_ = y_coordinate_ + ghost_count;

}

/// <summary>
/// RotateBlock関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Block::RotateBlock() {

  switch (angle_type_) {

  case kAngle0:

    angle_type_ = kAngle90;
    break;

  case kAngle90:

    angle_type_ = kAngle180;
    break;

  case kAngle180:

    angle_type_ = kAngle270;
    break;

  case kAngle270:

    angle_type_ = kAngle0;
    break;
  }

  //ブロックの種類と角度を取得
  DecideMino();
}

/// <summary>
/// RevertRotation関数の宣言
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Block::RevertRotation() {

  switch (angle_type_) {

  case kAngle0:

    angle_type_ = kAngle270;
    break;

  case kAngle90:

    angle_type_ = kAngle0;
    break;

  case kAngle180:

    angle_type_ = kAngle90;
    break;

  case kAngle270:

    angle_type_ = kAngle180;
    break;
  }

  //ブロックの種類と角度を取得
  DecideMino();
}

/// <summary>
/// GetCurrentBlock関数
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
Block::BlockStatus Block::GetCurrentBlock(int x, int y) {
  return current_block_[y][x];
}

/// <summary>
/// SetHitBottom関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void Block::SetHitBottom(bool is_hit_bottom) {
  is_hit_bottom_ = is_hit_bottom;
}

/// <summary>
/// SetHitRight関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void Block::SetHitRight() {
  is_hit_right_ = true;
}

/// <summary>
/// SetHitLeft関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void Block::SetHitLeft() {
  is_hit_left_ = true;
}

/// <summary>
/// SetHit関数の宣言
/// </summary>
/// <param = ""></param>
/// <returns>なし</returns>
void Block::SetHit(bool is_hit) {
  is_hit_ = is_hit;
}

/// <summary>
/// IsHit関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>ブロックが他のブロックと重なったかの有無</returns>
bool Block::IsHit() {
  return is_hit_;
}

/// <summary>
/// mapdata_の指定位置の要素を変更する関数
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <param = "maptype">マップの種類</param>
/// <returns>なし</returns>
void Block::SetMapType(int x, int y, BlockType maptype) {
  mapdata_[y][x] = maptype;
}

/// <summary>
/// mapdata_の指定位置の要素を返す関数
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <returns>マップの種類</returns>
Block::BlockType Block::GetMapType(int x, int y) {
  return mapdata_[y][x];
}


/// <summary>
/// ブロック同士が重なっているかを確認する
/// </summary>
/// <param = "x">X位置</param>
/// <param = "y">Y位置</param>
/// <returns>なし</returns>
void Block::CheckIsPileBlocks(int x, int y) {

  for (int i = 0; i < kBlockRow; i++) {
    for (int j = 0; j < kBlockColumn; j++) {
      Block::BlockStatus current_block = GetCurrentBlock(j, i);
      if (current_block == Block::kBlockExist) {

        //Fieldマップ上のブロックが存在する位置のMapTypeを確認する
        BlockType map_type = GetMapType(x + j, y + i);
        //DEBUG_PRINT_VAR(map_type);

        //Fieldマップ上のブロックが存在する位置のMapTypeがkNoneでなければ、他のブロックと衝突したと判定する
        if (map_type == kMinoI || map_type == kMinoO || map_type == kMinoS || map_type == kMinoZ || map_type == kMinoJ || map_type == kMinoL || map_type == kMinoT) {
          //SetHit(true);
          is_hit_ = true;
          DEBUG_PRINT(Block同士が重なった);
          break;
        }
      }
    }
  }
}

/// <summary>
/// SetSoftDropNum関数の定義
/// </summary>
/// <param>画像の幅</param>
/// <returns>なし</returns>
void Block::SetSoftDropNum(int softdrop_num) {
  softdrop_num_ = softdrop_num;
}

/// <summary>
/// GetSoftDropNum関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>画像の幅</returns>
int Block::GetSoftDropNum() {
  return softdrop_num_;
}

/// <summary>
/// ブロックの角度を指定する関数
/// </summary>
/// <param = "angle_type">角度の種類</param>
/// <returns>なし</returns>
void Block::SetAngleType(AngleType angle_type) {
  angle_type_ = angle_type;
}

/// <summary>
/// SetLevel関数の定義
/// </summary>
/// <param = "level">レベル</param>
/// <returns>なし</returns>
void Block::SetLevel(int level) {
  level_ = level;
}

/// <summary>
/// 下に移動する時にブロック同士が衝突したかを確認する
/// </summary>
/// <param name>なし</param>
/// <returns>なし</returns>
int Block::CheckIsHitBlocksBottom() {

  int harddrop_num = 0;
  int x_coordinate = x_coordinate_;
  int y_coordinate = y_coordinate_;

  while (is_hit_bottom_ == false)
  {
    for (int i = 0; i < kBlockRow; i++) {
      for (int j = 0; j < kBlockColumn; j++) {
        BlockStatus current_block = GetCurrentBlock(j, i);
        if (current_block == Block::kBlockExist) {

          //Fieldマップ上のブロックが存在する位置の真下のMapTypeを確認する
          BlockType map_type_bottom = GetMapType(x_coordinate + j, y_coordinate + i + 1);
          (map_type_bottom);

          //Fieldマップ上のブロックが存在する位置のMapTypeがkNoneでなければ、他のブロックと衝突したと判定する
          if (map_type_bottom == kMinoI || map_type_bottom == kMinoO || map_type_bottom == kMinoS || map_type_bottom == kMinoZ || map_type_bottom == kMinoJ || map_type_bottom == kMinoL || map_type_bottom == kMinoT) {
            SetHitBottom(true);
            DEBUG_PRINT(下でBlock同士の衝突);
            break;
          }
        }
      }
    }
    if (is_hit_bottom_ == false) {
      y_coordinate++;
    }
  }
  harddrop_num = y_coordinate - y_coordinate_;
  return harddrop_num;
}

/// <summary>
/// SetHardDropNum関数の定義
/// </summary>
/// <param>上キーを押して移動した回数</param>
/// <returns>なし</returns>
void Block::SetHardDropNum(int harddrop_num) {
  harddrop_num_ = harddrop_num;
}

/// <summary>
/// GetHardDropNum関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>上キーを押して移動した回数</returns>
int Block::GetHardDropNum() {
  return harddrop_num_;
}

/// <summary>
/// GetPiece関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void Block::GetPiece() {
  //ブロックの最下部を取得
  piece_bottom_ = GetPieceBottom();
  //DEBUG_PRINT_VAR(piece_bottom_);

  //ブロックの最右部を取得
  piece_right_ = GetPieceRight();
  //DEBUG_PRINT_VAR(piece_right_);

  //ブロックの最左部を取得
  piece_left_ = GetPieceLeft();
  //DEBUG_PRINT_VAR(piece_left_);
}

/// <summary>
/// SuperRotateOneAndFour関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
int Block::SuperRotateOneAndFour(int x_coordinate) {
  if (is_hit_ == true) {
    DEBUG_PRINT(スーパーローテーションの第一法則);
    switch (angle_type_) {

    case kAngle0:
      if (rotation_status_ == kZKey) {
        //Zかスペースキーを押された場合、右に１つ移動
        x_coordinate++;
      }
      else {
        //Xキーを押された場合、左に１つ移動
        x_coordinate--;
      }
      break;

    case kAngle90:
      x_coordinate++;
      break;

    case kAngle180:
      if (rotation_status_ == kZKey) {
        //Zかスペースキーを押された場合、左に１つ移動
        x_coordinate--;
      }
      else {
        //Xキーを押された場合、右に１つ移動
        x_coordinate++;
      }
      break;

    case kAngle270:
      x_coordinate--;
      break;
    }

    is_hit_ = false;
  }
  return x_coordinate;
}

/// <summary>
/// ブロックを真下に着地させる場合のY位置と現在のY位置の差を取得する
/// </summary>
/// <param name>なし</param>
/// <returns="ghost_num">ブロックを真下に着地させる場合のY位置と現在のY位置の差</returns>
int Block::CheckGhostYCount() {

  int ghost_num = 0;
  int x_coordinate = x_coordinate_;
  int y_coordinate = y_coordinate_;

  while (is_found_ghost_y_ == false)
  {
    for (int i = 0; i < kBlockRow; i++) {
      for (int j = 0; j < kBlockColumn; j++) {
        BlockStatus current_block = GetCurrentBlock(j, i);
        if (current_block == Block::kBlockExist) {

          //Fieldマップ上のブロックが存在する位置の真下のMapTypeを確認する
          BlockType map_type_bottom = GetMapType(x_coordinate + j, y_coordinate + i + 1);
          //DEBUG_PRINT_VAR(map_type_bottom);

          //Fieldマップ上のブロックが存在する位置のMapTypeがkNoneでなければ、他のブロックと衝突したと判定する
          if (map_type_bottom == kMinoI || map_type_bottom == kMinoO || map_type_bottom == kMinoS || map_type_bottom == kMinoZ || map_type_bottom == kMinoJ || map_type_bottom == kMinoL || map_type_bottom == kMinoT || y_coordinate >= ((kRow + kWallWidth) - (piece_bottom_ + 1))) {
            is_found_ghost_y_ = true;
            //DEBUG_PRINT(ghost位置);
            break;
          }
        }
      }
    }
    if (is_found_ghost_y_ == false) {
      y_coordinate++;
    }
  }
  ghost_num = y_coordinate - y_coordinate_;
  is_found_ghost_y_ = false;
  //DEBUG_PRINT_VAR(y_coordinate);
  //DEBUG_PRINT_VAR(ghost_num);
  return ghost_num;
}

/// <summary>
/// SetGhostDisplay関数の宣言
/// </summary>
/// <param = "ghost_display">ゴーストの表示非表示</param>
/// <returns>なし</returns>
void Block::SetGhostDisplay(bool ghost_display) {
  ghost_display_ = ghost_display;
}

/// <summary>
/// SetSpinSoundHandle関数の定義
/// </summary>
/// <param = "spin_sound_handle">回転時のサウンドハンドル</param>
/// <returns>なし</returns>
void Block::SetSpinSoundHandle(int spin_sound_handle) {
  spin_sound_handle_ = spin_sound_handle;
}

/// <summary>
/// GetSpinSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>回転時のサウンドハンドル</returns>
int Block::GetSpinSoundHandle() {
  return spin_sound_handle_;
}

/// <summary>
/// SetXMoveSoundHandle関数の定義
/// </summary>
/// <param = "move_handle">左右移動時のサウンドハンドル</param>
/// <returns>なし</returns>
void Block::SetXMoveSoundHandle(int move_handle) {
  move_handle_ = move_handle;
}

/// <summary>
/// GetXMoveSoundHandle関数の定義
/// </summary>
/// <param>なし</param>
/// <returns>左右移動時のサウンドハンドル</returns>
int Block::GetXMoveSoundHandle() {
  return move_handle_;
}

/// <summary>
/// SetSoundVolume関数の定義
/// </summary>
/// <param = "sound_volume">音量</param>
/// <returns>なし</returns>
void Block::SetSoundVolume(int sound_volume) {
  sound_volume_ = sound_volume;
}