#pragma once
#include <queue>
#include "System/Level/Level.h"
#include "System/LogConsole.h"
#include "Game/Field.h"
#include "Game/Block.h"
#include "Game/GameMode.h"
#include "Game/StartUi.h"
//#include "Game/FinishUi.h"
#include "Game/PauseUi.h"

/// <summary>
/// 無名名前空間
/// </summary>
namespace {

}

/// <summary>
/// BattleLevelクラス
/// </summary>
class BattleLevel : public Level{
public:

  /// <summary>
  //ImageInfo構造体型を定義する
  /// <summary>
  struct ImageInfo {
    int handle; //画像のグラフィックハンドル
    int size_x; //画像の幅
    int size_y; //画像の高さ
  };

  /// <summary>
  //終了フェーズの種類の列挙型EndPhaseType型を定義する
  /// <summary>
  enum EndPhaseType {
    /// <summary>
    /// タスクを降ろすフェーズ
    /// </summary>
    kUnloadTask,

    /// <summary>
    /// 破棄フェーズ
    /// </summary>
    kDelete,
  };


  /// <summary>
  //フェーズの種類(処理中のフェーズ)
  /// <summary>
  enum ProcessingPhaseType {
    /// <summary>
    /// 準備中
    /// </summary>
    kPreparation,

    /// <summary>
    /// スタートUI表示
    /// </summary>
    kStartUiDisplay,

    /// <summary>
    /// スタートUI終了待機
    /// </summary>
    kStartUiFinishWaiting,

    /// <summary>
    /// ゲームオーバー
    /// </summary>
    kGameOver,

    /// <summary>
    /// フェードイン
    /// </summary>
    kFadeIn,

    /// <summary>
    /// フィニッシュUI表示
    /// </summary>
    kFinishUiDisplay,

    /// <summary>
    /// フィニッシュUI終了待機
    /// </summary>
    kFinishUiFinishWaiting,

    /// <summary>
    /// 処理中
    /// </summary>
    kProcessing,

    /// <summary>
    /// ブロック固定処理中
    /// </summary>
    kBlockFix,

    /// <summary>
    /// プレイ中断
    /// </summary>
    kStop,

    /// <summary>
    /// バトル終了
    /// </summary>
    kBattleFinish,

    /// <summary>
    /// レベル遷移
    /// </summary>
    kLevelTransition,

    /// <summary>
    /// 終了済み
    /// </summary>
    kFinished,
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
  };

  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  BattleLevel();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  BattleLevel(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~BattleLevel();

  /// <summary>
  /// 各方向キーが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushDirectionKey();

  /// <summary>
  /// 移動範囲をチェックする
  /// </summary>
  /// <param name ></param>
  /// <returns>なし</returns>
  void CheckWalkDistance();

  /// <summary>
  /// 決定ボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushDecide();

  /// <summary>
  /// 終了ボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushFinish();

  /// <summary>
  /// スペースボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushPause();

  /// <summary>
  /// BackSpaceボタンが押された時のイベント
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void OnPushBackSpace();

  /// <summary>
  /// ゲームオーバーを設定する処理
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetGameOver();

  /// <summary>
  /// UI終了のイベント
  /// </summary>
  /// <param name="task_id">終了するUIのタスクID</param>
  /// <returns>なし</returns>
  virtual void EndUi(TaskId task_id);

  /// <summary>
  /// LoadImage関数の宣言
  /// </summary>
  /// <param = "filename">画像のファイル名</param>
  /// <returns>ImageInfo構造体型のinfo</returns>
  ImageInfo LoadImage(const char* filename);

  /// <summary>
  /// フェードイン表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "handle">グラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void FadeIn(int x, int y, int handle, bool is_transparent, int fade_value, int fade);

  /// <summary>
  /// SetGameOverGrHandle関数の宣言
  /// </summary>
  /// <param = "gameover_handle">ゲームオーバーの画像のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetGameOverGrHandle(int gameover_handle);

  /// <summary>
  /// GetGameOverGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲームオーバーの画像のグラフィックハンドル</returns>
  int GetGameOverGrHandle();

  /// <summary>
  /// StopAll関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void StopAll();

  /// <summary>
  /// SetPlayingAll関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void SetPlayingAll();

  /// <summary>
  /// フェードアウト表示する関数の宣言
  /// </summary>
  /// <param = "x">X位置</param>
  /// <param = "y">Y位置</param>
  /// <param = "handle">グラフィックハンドル</param>
  /// <param = "is_transparent">透過の有無</param>
  /// <returns>なし</returns>
  void FadeOut();

  /// <summary>
  /// SetWhiteRectangleGrHandle関数の宣言
  /// </summary>
  /// <param = "white_rectangle_handle">文字表示のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetWhiteRectangleGrHandle(int white_rectangle_handle);

  /// <summary>
  /// GetWhiteRectangleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>文字表示のグラフィックハンドル</returns>
  int GetWhiteRectangleGrHandle();

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
  /// SetGameOverSoundHandle関数の宣言
  /// </summary>
  /// <param = "gameover_sound_handle">ゲームオーバー時のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetGameOverSoundHandle(int gameover_sound_handle);

  /// <summary>
  /// GetGameOverSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲームオーバー時のサウンドハンドル</returns>
  int GetGameOverSoundHandle();

  /// <summary>
  /// SetFixSoundHandle関数の宣言
  /// </summary>
  /// <param = "">サウンドハンドル</param>
  /// <returns>なし</returns>
  void SetFixSoundHandle(int fix_sound_handle);

  /// <summary>
  /// GetFixSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>サウンドハンドル</returns>
  int GetFixSoundHandle();

  /// <summary>
  /// SetHoldSoundHandle関数の宣言
  /// </summary>
  /// <param = "hold_sound_handle">サウンドハンドル</param>
  /// <returns>なし</returns>
  void SetHoldSoundHandle(int hold_sound_handle);

  /// <summary>
  /// GetHoldSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>サウンドハンドル</returns>
  int GetHoldSoundHandle();

  /// <summary>
  /// SetDeleteLineSoundHandle関数の宣言
  /// </summary>
  /// <param = "delete_sound_handle">サウンドハンドル</param>
  /// <returns>なし</returns>
  void SetDeleteLineSoundHandle(int delete_sound_handle);

  /// <summary>
  /// GetDeleteLineSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>サウンドハンドル</returns>
  int GetDeleteLineSoundHandle();

  /// <summary>
  /// ブロックを固定する関数
  /// </summary>
  /// <param = ""></param>
  /// <returns>なし</returns>
  void FixBlock();

  /// <summary>
  /// 次に落ちるブロックを生成する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void CreateNextBlock();

  /// <summary>
  /// 下に移動する時にブロック同士が衝突したかを確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void CheckIsHitBlocksBottom();

  /// <summary>
  /// 右に移動する時にブロック同士が衝突したかを確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void CheckIsHitBlocksRight();

  /// <summary>
  /// 左に移動する時にブロック同士が衝突したかを確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void CheckIsHitBlocksLeft();

  /// <summary>
  /// 固定する前にブロックが下で衝突しているかを再確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void CheckIsCanFixBlocks();

  /// <summary>
  /// FieldクラスのFieldマップをBlockクラスのFieldマップにコピーする
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void CopyMap();

  /// <summary>
  /// Fieldのブロックが全て消されたかを確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  bool CheckIsAllClear();

  /// <summary>
  /// スコアを更新する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void UpdateScore();

  /// <summary>
  /// レベルを更新する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void UpdateLevel();

  /// <summary>
  /// ブロックをHOLDする
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void HoldBlock();

  /// <summary>
  /// WriteDataToFile関数の宣言
  /// </summary>
  /// <param="filename">ファイル名</param>
  /// <param="initialdata">Fieldマップ初期化データ</param>
  /// <returns>ファイルが読み込めたかの有無</returns>
  void WriteDataToFile(std::string filename, int num);

  /// <summary>
  /// Nextブロックを初期化する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void InitNextBlocks();

  /// <summary>
  /// next_blocks_の末尾にブロックを追加する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void SetBlockBack();

  /// <summary>
  /// 積み上がっているブロックの一番上のY位置を確認する
  /// </summary>
  /// <param name>なし</param>
  /// <returns>積み上がっているブロックの一番上のY位置</returns>
  int CheckTopYPos();

protected:

  /// <summary>
  /// 初期化処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool InitializeUpdate(float time) override;

  /// <summary>
  /// 毎フレーム更新処理のフェーズ処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool ProcessingUpdate(float time) override;

  /// <summary>
  /// 毎フレームの描画処理
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void ProcessingRender() override;

  /// <summary>
  /// 終了処理
  /// </summary>
  /// <param name = "time">最後のフレームを完了するのに要した時間 (秒) </param>
  /// <returns>処理終了：true、処理継続：false</returns>
  bool PhaseFinalize(float time) override;

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// <summary>
  /// 終了の有無
  /// </summary>
  bool is_finish_;

  /// <summary>
  /// 累積時間（秒）
  /// </summary>
  float accumulation_time_;

  /// <summary>
  /// フィールド処理
  /// </summary>
  Field* field_;

  /// <summary>
  /// ブロック
  /// </summary>
  Block* block_;

  /// <summary>
  /// 終了フェーズの種類
  /// </summary>
  EndPhaseType end_type_;

  /// <summary>
  /// ゲームモード
  /// </summary>
  GameMode* game_mode_;

  /// <summary>
  /// フェーズの種類
  /// </summary>
  ProcessingPhaseType phase_type_;

  /// <summary>
  /// スタートUI
  /// </summary>
  StartUi* start_ui_;

  /// <summary>
  /// ポーズ情報UI
  /// </summary>
  PauseUi* pause_ui_;

  /// <summary>
  /// 終わったかの有無
  /// </summary>
  //bool last_render_;

  /// <summary>
  /// ブロック固定で使う累積時間（秒）
  /// </summary>
  float fix_accumulation_time_;

  /// <summary>
  /// ゲームオーバーの画像のグラフィックハンドル
  /// </summary>
  int gameover_handle_;

  /// <summary>
  /// ブロックがラインで揃ったかの有無
  /// </summary>
  bool block_line_;

  /// <summary>
  /// 文字表示の画像のグラフィックハンドル
  /// </summary>
  int white_rectangle_handle_;

  /// <summary>
  /// ゲームオーバー時の画像のフェードインが終わったかの有無
  /// </summary>
  bool gameover_fade_end_;

  /// <summary>
  /// BGMサウンドハンドル
  /// </summary>
  int bgm_handle_;

  /// <summary>
  /// ゲームオーバー時のサウンドハンドル
  /// </summary>
  int gameover_sound_handle_;

  /// <summary>
  /// ブロックが固定された時のサウンドハンドル
  /// </summary>
  int fix_sound_handle_;

  /// <summary>
  /// ホールドした時のサウンドハンドル
  /// </summary>
  int hold_sound_handle_;

  /// <summary>
  /// ブロックがラインで消えた時のサウンドハンドル
  /// </summary>
  int delete_sound_handle_;

  /// <summary>
  /// スコア
  /// </summary>
  int score_;

  /// <summary>
  /// ブロック同士を固定して良いかの有無
  /// </summary>
  bool is_can_fix_blocks_;

  /// <summary>
  /// スコアの種類
  /// </summary>
  ScoreType score_type_;

  /// <summary>
  /// 前回のブロック着地時にラインで揃ったかの有無
  /// </summary>
  bool is_lined_;

  /// <summary>
  /// コンボ回数
  /// </summary>
  int combo_;

  /// <summary>
  /// 消したラインの合計
  /// </summary>
  int total_lines_;

  /// <summary>
  /// レベル
  /// </summary>
  int level_;

  /// <summary>
  /// Holdできるかの有無
  /// </summary>
  bool is_can_hold_;

  /// <summary>
  /// Holdされているブロック
  /// </summary>
  Block::BlockType hold_block_;

  /// <summary>
  /// Holdされるブロックを一時的に格納する変数
  /// </summary>
  Block::BlockType pre_hold_block_;

  /// <summary>
  /// フェードイン・フェードアウトで使用する整数
  /// </summary>
  int fade_;

  /// <summary>
  /// 前回までのFieldクラスのフェーズ
  /// </summary>
  Field::FieldPhaseType pre_field_phase_;

  /// <summary>
  /// 前回までのハイスコア
  /// </summary>
  int high_score_;

  /// <summary>
  /// 画面に表示する次に降って来るblock
  /// </summary>
  std::queue<Block::BlockType> next_blocks_;

  /// <summary>
  /// 音量
  /// </summary>
  int sound_volume_;
};