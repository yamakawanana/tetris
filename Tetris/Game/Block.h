#pragma once
#include "Game/Block.h"
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"
#include "Game/Field.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// ブロックの行数を定数kBlockRowに格納する
  /// </summary>
  static const int kBlockRow = 4;

  /// <summary>
  /// ブロックの列数を定数kBlockColumnに格納する
  /// </summary>
  static const int kBlockColumn = 4;
}

/// <summary>
/// Blockクラス
/// </summary>
class Block : public Task{
public:

  /// <summary>
  /// フェーズの種類
  /// </summary>
  enum PhaseType {
    /// <summary>
    /// 準備中
    /// </summary>
    kPreraration,

    /// <summary>
    /// プレイ中
    /// </summary>
    kPlaying,

    /// <summary>
    /// 固定中
    /// </summary>
    kFix,

    /// <summary>
    /// ブロックがラインで揃ってから次のブロックを生成するまでの待機中
    /// </summary>
    kWaiting,

    /// <summary>
    /// プレイ中断
    /// </summary>
    kStop,

    /// <summary>
    /// 終了フェーズ
    /// </summary>
    kFinish,

    /// <summary>
    /// フェーズの種類の最大数
    /// </summary>
    kMax,
  };


  /// <summary>
  //方向の種類の列挙型DirectionType型を定義する
  /// <summary>
  enum DirectionType {
    /// <summary>
    /// 下
    /// </summary>
    kDown,

    /// <summary>
    /// 右
    /// </summary>
    kRight,

    /// <summary>
    /// 左
    /// </summary>
    kLeft,

    /// <summary>
    /// 何もない
    /// </summary>
    kNone,
  };

  /// <summary>
  //ブロックの種類の列挙型BlockType型を定義する
  /// <summary>
  enum BlockType {
    /// <summary>
    /// I型
    /// </summary>
    kMinoI,

    /// <summary>
    /// O型
    /// </summary>
    kMinoO,

    /// <summary>
    /// S型
    /// </summary>
    kMinoS,

    /// <summary>
    /// Z型
    /// </summary>
    kMinoZ,

    /// <summary>
    /// J型
    /// </summary>
    kMinoJ,

    /// <summary>
    /// L型
    /// </summary>
    kMinoL,

    /// <summary>
    /// T型
    /// </summary>
    kMinoT,

    /// <summary>
    /// 壁
    /// </summary>
    kWall,

    /// <summary>
    /// ブロックの種類の最大数
    /// </summary>
    kMinoMax,
  };

  /// <summary>
  //回転した角度の種類の列挙型AngleType型を定義する
  /// <summary>
  enum AngleType {
    /// <summary>
    /// 0度
    /// </summary>
    kAngle0,

    /// <summary>
    /// 90度
    /// </summary>
    kAngle90,

    /// <summary>
    /// 180度
    /// </summary>
    kAngle180,

    /// <summary>
    /// 270度
    /// </summary>
    kAngle270,
  };

  /// <summary>
  //ブロックがあるかないかの列挙型BlockStatus型を定義する
  /// <summary>
  enum BlockStatus {
    /// <summary>
    /// ブロックがある
    /// </summary>
    kBlockExist,

    /// <summary>
    /// ブロックがない
    /// </summary>
    kBlockNone,
  };

  /// <summary>
  //回転のためにどのボタンを押されたかの列挙型RotationStatus型を定義する
  /// <summary>
  enum RotationStatus {
    /// <summary>
    /// Zキーあるいはスペースキー
    /// </summary>
    kZKey,

    /// <summary>
    /// Xキー
    /// </summary>
    kXKey,

    /// <summary>
    /// どちらも押されていない
    /// </summary>
    kRotationNone,
  };

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Block(Task task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~Block();

  /// <summary>
  /// 毎フレーム更新処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// 毎フレーム描画処理
  /// </remarks>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void RenderFrame() override;

  /// <summary>
  /// GetLightBlueGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>水色のグラフィックハンドル</returns>
  int GetLightBlueGrHandle();

  /// <summary>
  /// SetLightBlueGrHandle関数の宣言
  /// </summary>
  /// <param = "lightblue_gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetLightBlueGrHandle(int lightblue_gr_handle);

  /// <summary>
  /// GetBlueGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>青色のグラフィックハンドル</returns>
  int GetBlueGrHandle();

  /// <summary>
  /// SetBlueGrHandle関数の宣言
  /// </summary>
  /// <param = "blue_gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBlueGrHandle(int blue_gr_handle);

  /// <summary>
  /// GetEmeraldGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>黄緑色のグラフィックハンドル</returns>
  int GetEmeraldGrHandle();

  /// <summary>
  /// SetEmeraldGrHandle関数の宣言
  /// </summary>
  /// <param = "emerald_gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetEmeraldGrHandle(int emerald_gr_handle);

  /// <summary>
  /// GetOrangeGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>オレンジ色のグラフィックハンドル</returns>
  int GetOrangeGrHandle();

  /// <summary>
  /// SetOrangeGrHandle関数の宣言
  /// </summary>
  /// <param = "orange_gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetOrangeGrHandle(int orange_gr_handle);

  /// <summary>
  /// GetYellowGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>黄色のグラフィックハンドル</returns>
  int GetYellowGrHandle();

  /// <summary>
  /// SetYellowGrHandle関数の宣言
  /// </summary>
  /// <param = "yellow_gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetYellowGrHandle(int yellow_gr_handle);

  /// <summary>
  /// GetPurpleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>紫色のグラフィックハンドル</returns>
  int GetPurpleGrHandle();

  /// <summary>
  /// SetPurpleGrHandle関数の宣言
  /// </summary>
  /// <param = "purple_gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetPurpleGrHandle(int purple_gr_handle);

  /// <summary>
  /// GetRedGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>赤色のグラフィックハンドル</returns>
  int GetRedGrHandle();

  /// <summary>
  /// SetRedGrHandle関数の宣言
  /// </summary>
  /// <param = "red_gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetRedGrHandle(int red_gr_handle);

  /// <summary>
  /// SetXPosition関数の宣言
  /// </summary>
  /// <param = "x_coordinate">X座標</param>
  /// <returns>なし</returns>
  void SetXPosition(int x_coordinate);

  /// <summary>
  /// GetXPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>X座標</returns>
  int GetXPosition();

  /// <summary>
  /// SetYPosition関数の宣言
  /// </summary>
  /// <param = "y_coordinate">Y座標</param>
  /// <returns>なし</returns>
  void SetYPosition(int y_coordinate);

  /// <summary>
  /// GetYPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Y座標</returns>
  int GetYPosition();

  /// <summary>
  /// SetWidth関数の宣言
  /// </summary>
  /// <param>画像の幅</param>
  /// <returns>なし</returns>
  void SetWidth(int size_x);

  /// <summary>
  /// GetWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅</returns>
  int GetWidth();

  /// <summary>
  /// SetHeight関数の宣言
  /// </summary>
  /// <param>画像の高さ</param>
  /// <returns>なし</returns>
  void SetHeight(int size_y);

  /// <summary>
  /// GetHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さ</returns>
  int GetHeight();

  /// <summary>
  /// SetHalfWidth関数の宣言
  /// </summary>
  /// <param>画像の幅</param>
  /// <returns>なし</returns>
  void SetHalfWidth(float size_half_x);

  /// <summary>
  /// GetHalfWidth関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の幅の半分</returns>
  float GetHalfWidth();

  /// <summary>
  /// SetHalfHeight関数の宣言
  /// </summary>
  /// <param>画像の高さ</param>
  /// <returns>なし</returns>
  void SetHalfHeight(float size_half_y);

  /// <summary>
  /// GetHalfHeight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>画像の高さの半分</returns>
  float GetHalfHeight();

  /// <summary>
  /// SetBlockType関数の宣言
  /// </summary>
  /// <param = "character_type">ブロックの種類</param>
  /// <returns>なし</returns>
  void SetBlockType(BlockType block_type);

  /// <summary>
  /// GetBlockType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ブロックの種類</returns>
  BlockType GetBlockType();

  /// <summary>
  /// SetDirectionType関数の宣言
  /// </summary>
  /// <param = "direction">方向の種類</param>
  /// <returns>なし</returns>
  void SetDirectionType(DirectionType direction);

  /// <summary>
  /// GetDirectionType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>方向の種類</returns>
  DirectionType GetDirectionType();

  /// <summary>
  /// SetPhaseType関数の宣言
  /// </summary>
  /// <param = "type">フェーズの種類</param>
  /// <returns>なし</returns>
  void SetPhaseType(PhaseType type);

  /// <summary>
  /// GetPhaseType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フェーズの種類</returns>
  PhaseType GetPhaseType();

  /// <summary>
  /// SetDisplayXPosition関数の宣言
  /// </summary>
  /// <param = "display_x_coordinate">表示用のX座標</param>
  /// <returns>なし</returns>
  void SetDisplayXPosition(float display_x_coordinate);

  /// <summary>
  /// GetDisplayXPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>表示用のX座標</returns>
  float GetDisplayXPosition();

  /// <summary>
  /// SetDisplayYPosition関数の宣言
  /// </summary>
  /// <param = "display_y_coordinate">表示用のY座標</param>
  /// <returns>なし</returns>
  void SetDisplayYPosition(float display_y_coordinate);

  /// <summary>
  /// GetDisplayYPosition関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>表示用のY座標</returns>
  float GetDisplayYPosition();

  /// <summary>
  /// DecideMino関数の宣言
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void DecideMino();

  /// <summary>
  /// GetPieceTop関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ブロックの最上部の位置</returns>
  int GetPieceTop();

  /// <summary>
  /// GetPieceBottom関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ブロックの最下部の位置</returns>
  int GetPieceBottom();

  /// <summary>
  /// GetPieceLeft関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ブロックの最左部の位置</returns>
  int GetPieceLeft();

  /// <summary>
  /// GetPieceRight関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ブロックの最右部の位置</returns>
  int GetPieceRight();

  /// <summary>
  /// SpinBlock関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SpinBlock();

  /// <summary>
  /// RotateBlock関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void RotateBlock();

  /// <summary>
  /// RevertRotation関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void RevertRotation();

  /// <summary>
  /// GetCurrentBlock関数
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  BlockStatus GetCurrentBlock(int x, int y);

  /// <summary>
  /// SetHitBottom関数の宣言
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void SetHitBottom(bool is_hit_bottom);

  /// <summary>
  /// SetHitRight関数の宣言
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void SetHitRight();

  /// <summary>
  /// SetHitLeft関数の宣言
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void SetHitLeft();

  /// <summary>
  /// SetHit関数の宣言
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void SetHit(bool is_hit);

  /// <summary>
  /// IsHit関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ブロックが他のブロックと重なったかの有無</returns>
  bool IsHit();

  /// <summary>
  /// mapdata_の指定位置の要素を変更する関数
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "maptype">マップの種類</param>
  /// <returns>なし</returns>
  void SetMapType(int x, int y, BlockType maptype);

  /// <summary>
  /// mapdata_の指定位置の要素を返す関数
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <returns>マップの種類</returns>
  BlockType GetMapType(int x, int y);

  /// <summary>
  /// ブロック同士が重なっているかを確認する
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <returns>なし</returns>
  void CheckIsPileBlocks(int x, int y);

  /// <summary>
  /// SetSoftDropNum関数の宣言
  /// </summary>
  /// <param>下キーを押して移動した回数</param>
  /// <returns>なし</returns>
  void SetSoftDropNum(int softdrop_num);

  /// <summary>
  /// GetSoftDropNum関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>下キーを押して移動した回数</returns>
  int GetSoftDropNum();

  /// <summary>
  /// ブロックの角度を指定する関数
  /// </summary>
  /// <param = "angle_type">角度の種類</param>
  /// <returns>なし</returns>
  void SetAngleType(AngleType angle_type);

  /// <summary>
  /// SetLevel関数の宣言
  /// </summary>
  /// <param = "level">レベル</param>
  /// <returns>なし</returns>
  void SetLevel(int level);

  /// <summary>
  /// 下に移動する時にブロック同士が衝突するかを確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  int CheckIsHitBlocksBottom();

  /// <summary>
  /// SetHardDropNum関数の宣言
  /// </summary>
  /// <param>上キーを押して移動した回数</param>
  /// <returns>なし</returns>
  void SetHardDropNum(int harddrop_num);

  /// <summary>
  /// GetHardDropNum関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>上キーを押して移動した回数</returns>
  int GetHardDropNum();

  /// <summary>
  /// GetPiece関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void GetPiece();

  /// <summary>
  /// SuperRotateOneAndFour関数の宣言
  /// </summary>
  /// <param="x_coordinate">X位置</param>
  /// <returns>なし</returns>
  int SuperRotateOneAndFour(int x_coordinate);

  /// <summary>
  /// ブロックを真下に着地させる場合のY位置と現在のY位置の差を取得する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  int CheckGhostYCount();

  /// <summary>
  /// SetGhostDisplay関数の宣言
  /// </summary>
  /// <param = "ghost_display">ゴーストの表示非表示</param>
  /// <returns>なし</returns>
  void SetGhostDisplay(bool ghost_display);

  /// <summary>
  /// SetSpinSoundHandle関数の宣言
  /// </summary>
  /// <param = "spin_sound_handle">サウンドハンドル</param>
  /// <returns>なし</returns>
  void SetSpinSoundHandle(int spin_sound_handle);

  /// <summary>
  /// GetSpinSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>サウンドハンドル</returns>
  int GetSpinSoundHandle();

  /// <summary>
  /// SetXMoveSoundHandle関数の宣言
  /// </summary>
  /// <param = "move_handle">サウンドハンドル</param>
  /// <returns>なし</returns>
  void SetXMoveSoundHandle(int move_handle);

  /// <summary>
  /// GetXMoveSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>サウンドハンドル</returns>
  int GetXMoveSoundHandle();

  /// <summary>
  /// SetSoundVolume関数の宣言
  /// </summary>
  /// <param = "sound_volume">音量</param>
  /// <returns>なし</returns>
  void SetSoundVolume(int sound_volume);

protected:
  /// <summary>
  /// メンバ変数
  /// </summary>
  
  /// </summary>
  //現在のフェーズ
  /// </summary>
  PhaseType now_phase_;

  /// </summary>
  //タスクマネージャーのポインタ
  /// </summary>
  TaskManager* task_manager_;

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// 水色のグラフィックハンドル
  /// </summary>
  int lightblue_gr_handle_;

  /// <summary>
  /// 青色のグラフィックハンドル
  /// </summary>
  int blue_gr_handle_;

  /// <summary>
  /// 黄緑色のグラフィックハンドル
  /// </summary>
  int emerald_gr_handle_;

  /// <summary>
  /// オレンジ色のグラフィックハンドル
  /// </summary>
  int orange_gr_handle_;

  /// <summary>
  /// 黄色のグラフィックハンドル
  /// </summary>
  int yellow_gr_handle_;

  /// <summary>
  /// 紫色のグラフィックハンドル
  /// </summary>
  int purple_gr_handle_;

  /// <summary>
  /// 赤色のグラフィックハンドル
  /// </summary>
  int red_gr_handle_;

  /// <summary>
  /// 1フレームあたりのアニメーションの変化量
  /// </summary>
  //float change_amount_;

  /// </summary>
  //ブロックの種類
  /// </summary>
  BlockType block_type_;

  /// <summary>
  /// ブロックの二次元配列の左上のX座標
  /// </summary>
  int x_coordinate_;

  /// <summary>
  /// ブロックの二次元配列の左上のY座標
  /// </summary>
  int y_coordinate_;

  /// <summary>
  /// 画像の幅
  /// </summary>
  int width_;

  /// <summary>
  /// 画像の高さ
  /// </summary>
  int height_;

  /// <summary>
  /// 画像の幅の半分
  /// </summary>
  float half_width_;

  /// <summary>
  /// 画像の高さの半分
  /// </summary>
  float half_height_;

  /// </summary>
  //現在の向き
  /// </summary>
  DirectionType now_direction_;

  /// <summary>
  /// 表示用のX座標
  /// </summary>
  float display_x_coordinate_;

  /// <summary>
  /// 表示用のY座標
  /// </summary>
  float display_y_coordinate_;

  /// <summary>
  /// ブロック情報
  /// </summary>
  BlockStatus current_block_[kBlockRow][kBlockColumn];

  /// <summary>
  /// ブロック用のField情報
  /// </summary>
  BlockType mapdata_[kTotalRow][kTotalColumn];

  /// <summary>
  /// 角度情報
  /// </summary>
  AngleType angle_type_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// キー入力時の累積時間（秒）
  /// </summary>
  float keyinput_accumulation_time_;

  /// <summary>
  /// ブロックの最下部の位置
  /// </summary>
  int piece_bottom_;

  /// <summary>
  /// ブロックの最上部の位置
  /// </summary>
  int piece_top_;

  /// <summary>
  /// ブロックの最左部の位置
  /// </summary>
  int piece_left_;

  /// <summary>
  /// ブロックの最右部の位置
  /// </summary>
  int piece_right_;

  /// <summary>
  /// ブロックが下に移動する時に他のブロックとぶつかっているかの有無
  /// </summary>
  bool is_hit_bottom_;

  /// <summary>
  /// ブロックが右に移動する時に他のブロックとぶつかっているかの有無
  /// </summary>
  bool is_hit_right_;

  /// <summary>
  /// ブロックが左に移動する時に他のブロックとぶつかっているかの有無
  /// </summary>
  bool is_hit_left_;

  /// <summary>
  /// ブロックが他のブロックとぶつかっているかの有無
  /// </summary>
  bool is_hit_;

  /// <summary>
  /// ゴーストを表示する位置が見つかったかの有無
  /// </summary>
  bool is_found_ghost_y_;

  /// <summary>
  /// 下キーを押して移動した回数
  /// </summary>
  int softdrop_num_;

  /// <summary>
  /// レベル
  /// </summary>
  int level_;

  /// <summary>
  /// 上キーを押して移動した回数
  /// </summary>
  int harddrop_num_;

  /// <summary>
  /// 回転のキー押下の状態
  /// </summary>
  RotationStatus rotation_status_;

  /// <summary>
  /// ゴースト表示させるY座標
  /// </summary>
  int ghost_y_coordinate_;

  /// <summary>
  /// ゴーストの表示非表示
  /// </summary>
  bool ghost_display_;

  /// <summary>
  /// 回転した時のサウンドハンドル
  /// </summary>
  int spin_sound_handle_;

  /// <summary>
  /// 移動のサウンドハンドル
  /// </summary>
  int move_handle_;

  /// <summary>
  /// 音量
  /// </summary>
  int sound_volume_;
};