#pragma once
#include <map>
#include <array>
#include <queue>
#include "System/Task/Task.h"
#include "System/Task/TaskManager.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {
  /// <summary>
  /// フィールドの行数を定数kRowに格納する
  /// </summary>
  static const int kRow = 24;

  /// <summary>
  /// フィールドの列数を定数kColumnに格納する
  /// </summary>
  static const int kColumn = 14;

  /// <summary>
  /// 壁を含めたフィールドの行数を定数kRowに格納する
  /// </summary>
  static const int kTotalRow = 28;

  /// <summary>
  /// 壁を含めたフィールドの列数を定数kTotalColumnに格納する
  /// </summary>
  static const int kTotalColumn = 18;

  /// <summary>
  /// 壁の幅を定数kWallWidthに格納する
  /// </summary>
  static const int kWallWidth = 2;

  /// <summary>
  /// マップチップ一つのドットサイズを定数kMapSizeに格納する
  /// </summary>
  static const int kMapSize = 18;

  /// <summary>
  /// Nextに表示するブロックの個数を定数kNextElementNumに格納する
  /// </summary>
  static const int kNextElementNum = 5;

  /// <summary>
  /// アヒルのグラフィックハンドルの配列の要素数を定数kDuckElementNumberに格納する
  /// </summary>
  static const int kDuckElementNumber = 3;

  /// <summary>
  /// クマのグラフィックハンドルの配列の要素数を定数kBearElementNumberに格納する
  /// </summary>
  static const int kBearElementNumber = 3;

  /// <summary>
  /// ダメージを受けたアヒルのグラフィックハンドルの配列の要素数を定数kDamageDuckElementNumberに格納する
  /// </summary>
  static const int kDamageDuckElementNumber = 6;

  /// <summary>
  /// 紙吹雪の画像のグラフィックハンドルの配列の要素数を定数kConfettiElementNumberに格納する
  /// </summary>
  static const int kConfettiElementNumber = 36;
}

/// <summary>
/// Fieldクラス
/// </summary>
class Field : public Task {
public:

  /// <summary>
  //フェーズの種類の列挙型FieldPhaseType型を定義する
  /// <summary>
  enum FieldPhaseType {
    /// <summary>
    /// フィールド初期化フェーズ
    /// </summary>
    kFieldInitialized,

    /// <summary>
    /// ブロックの初期化フェーズ
    /// </summary>
    kBlockInitialized,

    /// <summary>
    /// 処理フェーズ
    /// </summary>
    kProcessing,

    /// <summary>
    /// 終了フェーズ
    /// </summary>
    kEnding,

    /// <summary>
    /// 終了済みフェーズ
    /// </summary>
    kEnded,

    /// <summary>
    /// 中断フェーズ
    /// </summary>
    kStop,
  };


  /// <summary>
  //マップの種類の列挙型MapType型を定義する
  /// <summary>
  enum MapType {
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
    /// 何もない
    /// </summary>
    kNone,

    /// <summary>
    /// 壁
    /// </summary>
    kWall,
  };

  /// <summary>
  //調べる方向の種類の列挙型DirectionType型を定義する
  /// <summary>
  enum DirectionType {

    /// <summary>
    /// 上
    /// </summary>
    kUp,

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
    /// 最大値
    /// </summary>
    kMax,
  };

  /// <summary>
  // スコアの種類
  /// <summary>
  enum ScoreType {
    /// <summary>
    /// 1ライン
    /// </summary>
    kOneLine,

    /// <summary>
    /// 2ライン
    /// </summary>
    kTwoLine,

    /// <summary>
    /// 3ライン
    /// </summary>
    kThreeLine,

    /// <summary>
    /// 4ライン
    /// </summary>
    kFourLine,

    /// <summary>
    /// 0ライン
    /// </summary>
    kZeroLine,
  };

  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Field();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Field(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~Field();

  /// <summary>
  /// UpdateFrame関数の宣言
  /// </summary>
  /// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
  /// <returns>なし</returns>
  void UpdateFrame(float time) override;

  /// <summary>
  /// RenderFrame関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void RenderFrame() override;

  /// <summary>
  /// SetBlockGrHandle関数の宣言
  /// </summary>
  /// <param = "block_handle">ブロックのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBlockGrHandle(int block_handle);

  /// <summary>
  /// GetBlockGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ブロックのグラフィックハンドル</returns>
  int GetBlockGrHandle();

  /// <summary>
  /// SetNoneGrHandle関数の宣言
  /// </summary>
  /// <param = "none_handle">何もない場合のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetNoneGrHandle(int none_handle);

  /// <summary>
  /// GetNoneGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>何もない場合のグラフィックハンドル</returns>
  int GetNoneGrHandle();

  /// <summary>
  /// SetBattleBackGrHandle関数の宣言
  /// </summary>
  /// <param = "battle_back_handle">BattleLevelの背景のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBattleBackGrHandle(int battle_back_handle);

  /// <summary>
  /// GetBattleBackGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>BattleLevelの背景のグラフィックハンドル</returns>
  int GetBattleBackGrHandle();

  /// <summary>
  /// SetFieldPhaseType関数の宣言
  /// </summary>
  /// <param = "type">フェーズの種類</param>
  /// <returns>なし</returns>
  void SetFieldPhaseType(FieldPhaseType type);

  /// <summary>
  /// GetFieldPhaseType関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>フェーズの種類</returns>
  FieldPhaseType GetFieldPhaseType();

  /// <summary>
  /// SetBgmHandle関数の宣言
  /// </summary>
  /// <param = "bgm_handle">BGMのサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetBgmHandle(int bgm_handle);

  /// <summary>
  /// GetBgmHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>BGMのサウンドハンドル</returns>
  int GetBgmHandle();

  /// <summary>
  /// mapdata_の指定位置の要素を変更する関数
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "maptype">マップの種類</param>
  /// <returns>なし</returns>
  void SetMapType(int x, int y, MapType maptype);

  /// <summary>
  /// mapdata_の指定位置の要素を返す関数
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <returns>マップの種類</returns>
  MapType GetMapType(int x, int y);

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
  /// CountDeleteLine関数の宣言
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void CountDeleteLine();

  /// <summary>
  /// DeleteLine関数の宣言
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void DeleteLine();

  /// <summary>
  /// GetLightGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>グラフィックハンドル</returns>
  int GetLightGrHandle();

  /// <summary>
  /// SetLightGrHandle関数の宣言
  /// </summary>
  /// <param = "light_gr_handle">グラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetLightGrHandle(int light_gr_handle);

  /// <summary>
  /// フェードイン表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "handle">グラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void FadeIn(int x, int y, int handle, bool is_transparent, int fade_value, int fade, int plus_alpha);

  /// <summary>
  /// フェードアウト表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "handle">グラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void FadeOut(int x, int y, int handle, bool is_transparent, int fade_value, int fade);

  /// <summary>
  /// IsDeleteLine関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ブロックが揃った行を消したかの有無</returns>
  bool IsDeleteLine();

  /// <summary>
  /// SetDeleteLine関数の宣言
  /// </summary>
  /// <param= "is_delete_line">ブロックが揃った行を消したかの有無</param>
  /// <returns></returns>
  void SetDeleteLine(bool is_delete_line);

  /// <summary>
  /// IsBlockLine関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ブロックがラインで揃ったかの有無</returns>
  bool IsBlockLine();

  /// <summary>
  /// SetBlockLine関数の宣言
  /// </summary>
  /// <param= "is_block_line">ブロックが揃ったかの有無</param>
  /// <returns></returns>
  void SetBlockLine(bool is_block_line);

  /// <summary>
  /// SetLineNum関数の宣言
  /// </summary>
  /// <param= "line_num">揃ったラインの数</param>
  /// <returns></returns>
  void SetLineNum(int line_num);

  /// <summary>
  /// GetLineNum関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>揃ったラインの数</returns>
  int GetLineNum();

  /// <summary>
  /// SetScore関数の宣言
  /// </summary>
  /// <param = "score">スコア</param>
  /// <returns>なし</returns>
  void SetScore(int score);

  /// <summary>
  /// SetTotalLines関数の宣言
  /// </summary>
  /// <param = "total_lines">消したラインの合計</param>
  /// <returns>なし</returns>
  void SetTotalLines(int total_lines);

  /// <summary>
  /// SetLevel関数の宣言
  /// </summary>
  /// <param = "level">レベル</param>
  /// <returns>なし</returns>
  void SetLevel(int level);

  /// <summary>
  /// SetScoreGrHandle関数の宣言
  /// </summary>
  /// <param = "score_gr_handle">スコア表示のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetScoreGrHandle(int score_gr_handle);

  /// <summary>
  /// GetScoreGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>スコア表示のグラフィックハンドル</returns>
  int GetScoreGrHandle();

  /// <summary>
  /// SetLevelUpGrHandle関数の宣言
  /// </summary>
  /// <param = "levelup_gr_handle">レベルアップ表示のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetLevelUpGrHandle(int levelup_gr_handle);

  /// <summary>
  /// GetLevelUpGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>レベルアップ表示のグラフィックハンドル</returns>
  int GetLevelUpGrHandle();

  /// <summary>
  /// SetHoldGrHandle関数の宣言
  /// </summary>
  /// <param = "hold_gr_handle">Hold表示のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetHoldGrHandle(int hold_gr_handle);

  /// <summary>
  /// GetHoldGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Hold表示のグラフィックハンドル</returns>
  int GetHoldGrHandle();

  /// <summary>
  /// SetIMinoGrHandle関数の宣言
  /// </summary>
  /// <param = "i_gr_handle">I型ブロック画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetIMinoGrHandle(int i_gr_handle);

  /// <summary>
  /// GetIMinoGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>I型ブロック画像のグラフィックハンドル</returns>
  int GetIMinoGrHandle();

  /// <summary>
  /// SetOMinoGrHandle関数の宣言
  /// </summary>
  /// <param = "o_gr_handle">O型ブロック画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetOMinoGrHandle(int o_gr_handle);

  /// <summary>
  /// GetOMinoGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>O型ブロック画像のグラフィックハンドル</returns>
  int GetOMinoGrHandle();

  /// <summary>
  /// SetSMinoGrHandle関数の宣言
  /// </summary>
  /// <param = "s_gr_handle">S型ブロック画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetSMinoGrHandle(int s_gr_handle);

  /// <summary>
  /// GetSMinoGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>S型ブロック画像のグラフィックハンドル</returns>
  int GetSMinoGrHandle();

  /// <summary>
  /// SetZMinoGrHandle関数の宣言
  /// </summary>
  /// <param = "z_gr_handle">Z型ブロック画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetZMinoGrHandle(int z_gr_handle);

  /// <summary>
  /// GetZMinoGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Z型ブロック画像のグラフィックハンドル</returns>
  int GetZMinoGrHandle();

  /// <summary>
  /// SetJMinoGrHandle関数の宣言
  /// </summary>
  /// <param = "j_gr_handle">J型ブロック画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetJMinoGrHandle(int j_gr_handle);

  /// <summary>
  /// GetJMinoGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>J型ブロック画像のグラフィックハンドル</returns>
  int GetJMinoGrHandle();

  /// <summary>
  /// SetLMinoGrHandle関数の宣言
  /// </summary>
  /// <param = "l_gr_handle">L型ブロック画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetLMinoGrHandle(int l_gr_handle);

  /// <summary>
  /// GetLMinoGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>L型ブロック画像のグラフィックハンドル</returns>
  int GetLMinoGrHandle();

  /// <summary>
  /// SetTMinoGrHandle関数の宣言
  /// </summary>
  /// <param = "t_gr_handle">T型ブロック画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTMinoGrHandle(int t_gr_handle);

  /// <summary>
  /// GetTMinoGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>T型ブロック画像のグラフィックハンドル</returns>
  int GetTMinoGrHandle();

  /// <summary>
  /// SetHoldBlock関数
  /// </summary>
  /// <param = "hold_block">Holdされたブロックの種類</param>
  /// <returns>なし</returns>
  void SetHoldBlock(MapType hold_block);

  /// <summary>
  /// SetMovieGrHandle関数の宣言
  /// </summary>
  /// <param = "movie_handle">動画のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetMovieGrHandle(int movie_handle);

  /// <summary>
  /// GetMovieGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>動画のグラフィックハンドル</returns>
  int GetMovieGrHandle();

  /// <summary>
  /// PlayMovie関数の宣言
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void PlayMovie(int movie_handle);

  /// <summary>
  /// SetFieldGameOver関数の宣言
  /// </summary>
  /// <param= "is_gameover">ゲームオーバーしたかの有無</param>
  /// <returns></returns>
  void SetFieldGameOver(bool is_gameover);

  /// <summary>
  /// SetBlackGrHandle関数の宣言
  /// </summary>
  /// <param = "black_handle">黒い画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBlackGrHandle(int black_handle);

  /// <summary>
  /// GetBlackGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>黒い画像のグラフィックハンドル</returns>
  int GetBlackGrHandle();

  /// <summary>
  /// IsFadeFinished関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲームオーバー時のフェードインが終わったかの有無</returns>
  bool IsFadeFinished();

  /// <summary>
  /// SplitString関数の宣言
  /// </summary>
  /// <param="input">読み込んだ文字列</param>
  /// <param="delimiter">区切り</param>
  /// <returns>分割後の</returns>
  std::vector<std::string> SplitString(std::string& input, char delimiter);

  /// <summary>
  /// SetHighScore関数の宣言
  /// </summary>
  /// <param = "score">スコア</param>
  /// <returns>なし</returns>
  void SetHighScore(int high_score);

  /// <summary>
  /// SetSingleGrHandle関数の宣言
  /// </summary>
  /// <param= "single_gr_handle">「SINGLE」表示用画像のグラフィックハンドル></param>
  /// <returns></returns>
  void SetSingleGrHandle(int single_gr_handle);

  /// <summary>
  /// GetSingleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>「SINGLE」表示用画像のグラフィックハンドル</returns>
  int GetSingleGrHandle();

  /// <summary>
  /// SetDoubleGrHandle関数の宣言
  /// </summary>
  /// <param= "double_gr_handle">「DOUBLE」表示用画像のグラフィックハンドル></param>
  /// <returns></returns>
  void SetDoubleGrHandle(int double_gr_handle);

  /// <summary>
  /// GetDoubleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>「DOUBLE」表示用画像のグラフィックハンドル</returns>
  int GetDoubleGrHandle();

  /// <summary>
  /// SetTripleGrHandle関数の宣言
  /// </summary>
  /// <param= "triple_gr_handle"「TRIPLE」表示用画像のグラフィックハンドル></param>
  /// <returns></returns>
  void SetTripleGrHandle(int triple_gr_handle);

  /// <summary>
  /// GetTripleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>「TRIPLE」表示用画像のグラフィックハンドル</returns>
  int GetTripleGrHandle();

  /// <summary>
  /// SetTetrisGrHandle関数の宣言
  /// </summary>
  /// <param= "tetris_gr_handle"「TETRIS」表示用画像のグラフィックハンドル></param>
  /// <returns></returns>
  void SetTetrisGrHandle(int tetris_gr_handle);

  /// <summary>
  /// GetTetrisGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>「TETRIS」表示用画像のグラフィックハンドル</returns>
  int GetTetrisGrHandle();

  /// <summary>
  /// SetNextGrHandle関数の宣言
  /// </summary>
  /// <param = "next_gr_handle">Next表示のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetNextGrHandle(int next_gr_handle);

  /// <summary>
  /// GetNextGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Next表示のグラフィックハンドル</returns>
  int GetNextGrHandle();

  /// <summary>
  /// next_blocks_を初期化する
  /// </summary>
  /// <param name = "next_block">追加するブロック</param>
  /// <returns>なし</returns>
  void InitNextBlocks(MapType next_block, int i);

  /// <summary>
  /// next_blocks_の末尾にブロックを追加する
  /// </summary>
  /// <param name = "next_block">末尾に追加するブロック</param>
  /// <returns>なし</returns>
  void SetBlockBack(MapType next_block);

  /// <summary>
  /// GetNextBlockElement関数の宣言
  /// </summary>
  /// <param = "element">なし</param>
  /// <returns>next_blockのi番目の要素</returns>
  MapType GetNextBlockElement(int element);

  /// <summary>
  /// next_blocks_の先頭のブロックを削除する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void DeleteNextTop();

  /// <summary>
  /// SetDuckGrHandle関数の宣言
  /// </summary>
  /// <param = "duck_handle">アヒルのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetDuckGrHandle(std::array<int, kDuckElementNumber> duck_handle);

  /// <summary>
  /// GetDuckGrHandle関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>アヒルのグラフィックハンドル</returns>
  int GetDuckGrHandle(int element_num);

  /// <summary>
  /// SetDamageDuckGrHandle関数の宣言
  /// </summary>
  /// <param = "damage_duck_handle">ダメージを受けたアヒルのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetDamageDuckGrHandle(std::array<int, kDamageDuckElementNumber> damage_duck_handle);

  /// <summary>
  /// GetDamageDuckGrHandle関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>ダメージを受けたアヒルのグラフィックハンドル</returns>
  int GetDamageDuckGrHandle(int element_num);

  /// <summary>
  /// SetBearGrHandle関数の宣言
  /// </summary>
  /// <param = "bear_handle">クマのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBearGrHandle(std::array<int, kBearElementNumber> bear_handle);

  /// <summary>
  /// GetBearGrHandle関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>クマのグラフィックハンドル</returns>
  int GetBearGrHandle(int element_num);

  /// <summary>
  /// SetDamageBearGrHandle関数の宣言
  /// </summary>
  /// <param = "damage_bear_handle">ダメージを受けたクマのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetDamageBearGrHandle(std::array<int, kBearElementNumber> damage_bear_handle);

  /// <summary>
  /// GetDamageBearGrHandle関数の宣言
  /// </summary>
  /// <param>要素番号</param>
  /// <returns>ダメージを受けたクマのグラフィックハンドル</returns>
  int GetDamageBearGrHandle(int element_num);

  /// <summary>
  /// IsDangerousY関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ブロックがもうすぐ天井に付きそうかの有無</returns>
  bool IsDangerousY();

  /// <summary>
  /// SetDangerousY関数の宣言
  /// </summary>
  /// <param= "is_dangerous_y">ブロックがもうすぐ天井に付きそうかの有無</param>
  /// <returns></returns>
  void SetDangerousY(bool is_dangerous_y);


  /// <summary>
  /// SetConfettiHandle関数の宣言
  /// </summary>
  /// <param = "confetti_handle">紙吹雪のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetConfettiHandle(std::array<int, kConfettiElementNumber> confetti_handle);

  /// <summary>
  /// GetConfettiHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>紙吹雪のグラフィックハンドル</returns>
  int GetConfettiHandle(int element_num);

protected:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //タスクマネージャーのポインタ
  /// </summary>
  TaskManager* task_manager_;

private:

  /// <summary>
  /// 初期化処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseInitialize(float time);

  /// <summary>
  /// 毎フレーム更新処理のフェーズ処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseUpdate(float time);

  /// <summary>
  /// 終了処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseFinalize(float time);

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //マップの種類
  /// </summary>
  MapType map_type_;

  /// </summary>
  //フェーズの種類
  /// </summary>
  FieldPhaseType field_phase_type_;

  /// </summary>
  //現在のフェーズ
  /// </summary>
  FieldPhaseType now_phase_;

  /// <summary>
  /// 何もない場合のグラフィックハンドル
  /// </summary>
  int none_handle_;

  /// <summary>
  /// ブロックのグラフィックハンドル
  /// </summary>
  int block_handle_;

  /// <summary>
  /// BattleLevelの背景のグラフィックハンドル
  /// </summary>
  int battle_back_handle_;

  /// <summary>
  /// キー操作情報の画像のグラフィックハンドル
  /// </summary>
  int key_info_handle_;

  /// <summary>
  /// フィールド情報
  /// </summary>
  MapType mapdata_[kTotalRow][kTotalColumn];

  /// <summary>
  /// フィールドのブロック情報
  /// </summary>
  //MapType field_block_info_[kRow][kColumn];

  /// </summary>
  //調べる方向の種類
  /// </summary>
  DirectionType direction_type_;

  /// </summary>
  //ブロックが揃っているかの有無を受け取る変数
  /// </summary>
  bool is_block_line_;

  /// </summary>
  //ブロックが揃ったラインを消したかの有無を受け取る変数
  /// </summary>
  bool is_delete_line_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float display_accumulation_time_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float sound_accumulation_time_;

  /// <summary>
  /// BGMサウンドハンドル
  /// </summary>
  int bgm_handle_;

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
  /// ラインで揃ったブロックのY位置のリスト
  /// </summary>
  std::vector<int> line_y_list_;

  /// <summary>
  /// 発光したブロックのグラフィックハンドル
  /// </summary>
  int light_gr_handle_;

  /// <summary>
  /// フェードイン・フェードアウトで使用する整数
  /// </summary>
  int fade_;

  /// <summary>
  /// ゲームオーバー時のフェードイン・フェードアウトで使用する整数
  /// </summary>
  int gameover_fade_;

  /// <summary>
  /// 揃ったライン数
  /// </summary>
  int line_num_;

  /// <summary>
  /// スコア
  /// </summary>
  int score_;

  /// <summary>
  /// 消したラインの合計
  /// </summary>
  int total_lines_;

  /// <summary>
  /// レベル
  /// </summary>
  int level_;

  /// <summary>
  /// スコア表示用画像のグラフィックハンドル
  /// </summary>
  int score_gr_handle_;

  /// <summary>
  /// レベルアップ表示用画像のグラフィックハンドル
  /// </summary>
  int levelup_gr_handle_;

  /// <summary>
  /// 前回フレームでのレベル
  /// </summary>
  int pre_level_;

  /// </summary>
  // レベルアップしたかの有無を受け取る変数
  /// </summary>
  bool is_level_up_;

  /// <summary>
  /// Hold表示の枠のグラフィックハンドル
  /// </summary>
  int hold_gr_handle_;

  /// <summary>
  /// I型ブロック画像のグラフィックハンドル
  /// </summary>
  int i_gr_handle_;

  /// <summary>
  /// O型ブロック画像のグラフィックハンドル
  /// </summary>
  int o_gr_handle_;

  /// <summary>
  /// S型ブロック画像のグラフィックハンドル
  /// </summary>
  int s_gr_handle_;

  /// <summary>
  /// Z型ブロック画像のグラフィックハンドル
  /// </summary>
  int z_gr_handle_;

  /// <summary>
  /// J型ブロック画像のグラフィックハンドル
  int j_gr_handle_;

  /// <summary>
  /// L型ブロック画像のグラフィックハンドル
  /// </summary>
  int l_gr_handle_;

  /// <summary>
  /// T型ブロック画像のグラフィックハンドル
  /// </summary>
  int t_gr_handle_;

  /// <summary>
  /// Holdされているブロックの種類
  /// </summary>
  MapType hold_block_;

  /// <summary>
  /// 動画ハンドル
  /// </summary>
  int movie_handle_;

  /// </summary>
  // ゲームオーバーであるかの有無を受け取る変数
  /// </summary>
  bool is_gameover_;

  /// <summary>
  /// 黒い画像のグラフィックハンドル
  /// </summary>
  int black_handle_;

  /// </summary>
  // ゲームオーバー時の黒い画像のフェードインが終わったかの有無を受け取る変数
  /// </summary>
  bool is_finished_fade_;

  /// <summary>
  /// 前回までのハイスコア
  /// </summary>
  int high_score_;

  /// <summary>
  /// 「SINGLE」表示用画像のグラフィックハンドル
  /// </summary>
  int single_gr_handle_;

  /// <summary>
  /// 「DOUBLE」表示用画像のグラフィックハンドル
  /// </summary>
  int double_gr_handle_;

  /// <summary>
  /// 「TRIPLE」表示用画像のグラフィックハンドル
  /// </summary>
  int triple_gr_handle_;

  /// <summary>
  /// 「TETRIS」表示用画像のグラフィックハンドル
  /// </summary>
  int tetris_gr_handle_;

  /// <summary>
  /// スコアの種類
  /// </summary>
  ScoreType score_type_;

  /// <summary>
  /// Next表示用画像のグラフィックハンドル
  /// </summary>
  int next_gr_handle_;

  /// <summary>
  /// Nextに表示されているブロックの種類
  /// </summary>
  MapType next_blocks_[kNextElementNum];

  /// <summary>
  /// 音量
  /// </summary>
  int sound_volume_;

  /// <summary>
  /// アヒルのグラフィックハンドル
  /// </summary>
  std::array<int, kDuckElementNumber> standing_duck_handle_;

  /// <summary>
  /// クマのグラフィックハンドル
  /// </summary>
  std::array<int, kBearElementNumber> standing_bear_handle_;

  /// <summary>
  /// 慌てているアヒルのグラフィックハンドル
  /// </summary>
  std::array<int, kDamageDuckElementNumber> damage_duck_handle_;

  /// <summary>
  /// 慌てているクマのグラフィックハンドル
  /// </summary>
  std::array<int, kBearElementNumber> damage_bear_handle_;

  /// <summary>
  /// インデックス
  /// </summary>
  int index_;

  /// </summary>
  // ブロックがもうすぐ天井に付きそうかの有無を受け取る変数
  /// </summary>
  bool is_dangerous_y_;

  /// <summary>
  /// 紙吹雪のグラフィックハンドル
  /// </summary>
  std::array<int, kConfettiElementNumber> confetti_handle_;
};
