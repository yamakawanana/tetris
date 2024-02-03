#pragma once
#include "System/Level/Level.h"
#include "System/LogConsole.h"

/// <summary>
/// ResultLevelクラス
/// </summary>
class ResultLevel : public Level{
public:
  /// <summary>
  //終了フェーズの種類の列挙型EndPhaseType型を定義する
  /// <summary>
  enum EndPhaseType {
    /// <summary>
    /// タスクを降ろすフェーズ
    /// </summary>
    kUnloadTask,

    /// <summary>
    /// フェーズ
    /// </summary>
    kDelete,
  };

  /// <summary>
// メニューの種類の列挙型MenuOption型を定義する
/// <summary>
  enum MenuOption {
    /// <summary>
    /// リトライ
    /// </summary>
    kRetry,

    /// <summary>
    /// タイトル画面に戻る
    /// </summary>
    kBackTitle,
  };


  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ResultLevel();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ResultLevel(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~ResultLevel();

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
  /// SetResultGrHandle関数の宣言
  /// </summary>
  /// <param = "title_handle">Resultのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetResultGrHandle(int title_handle);

  /// <summary>
  /// GetResultGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Resultのグラフィックハンドル</returns>
  int GetResultGrHandle();

  /// <summary>
  /// SetSelectedButtonGrHandle関数の宣言
  /// </summary>
  /// <param = "selected_button_handle">選択されたボタンを囲む枠のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetSelectedButtonGrHandle(int selected_button_handle);

  /// <summary>
  /// GetSelectedButtonGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>選択されたボタンを囲む枠のグラフィックハンドル</returns>
  int GetSelectedButtonGrHandle();

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
  /// SetEnterSoundHandle関数の宣言
  /// </summary>
  /// <param = "enter_handle">Enterを押した時のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetEnterSoundHandle(int enter_handle);

  /// <summary>
  /// GetEnterSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Enterを押した時のサウンドハンドル</returns>
  int GetEnterSoundHandle();

  /// <summary>
  /// フェードイン表示する関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void FadeIn(int x, int y, int size_x, int size_y, int fade, int plus_alpha);

  /// <summary>
  /// SetCursorSoundHandle関数の宣言
  /// </summary>
  /// <param = "cursor_handle">カーソル操作のサウンドハンドル</param>
  /// <returns>なし</returns>
  void SetCursorSoundHandle(int cursor_handle);

  /// <summary>
  /// GetCursorSoundHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>カーソル操作のサウンドハンドル</returns>
  int GetCursorSoundHandle();

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
  /// 累積時間（秒）
  /// </summary>
  float display_accumulation_time_;

  /// <summary>
  /// 終了フェーズの種類
  /// </summary>
  EndPhaseType end_type_;

  /// <summary>
  /// リザルト画面のグラフィックハンドル
  /// </summary>
  int result_handle_;

  /// <summary>
  /// 選択されている項目を囲む枠のグラフィックハンドル
  /// </summary>
  int selected_button_handle_;

  /// <summary>
  /// BGMサウンドハンドル
  /// </summary>
  int bgm_handle_;

  /// <summary>
  /// Enterを押した時のサウンドハンドル
  /// </summary>
  int enter_handle_;

  /// <summary>
  /// カーソル操作時のサウンドハンドル
  /// </summary>
  int cursor_handle_;

  /// <summary>
  /// 音量
  /// </summary>
  int sound_volume_;

  /// <summary>
  /// メニューの種類
  /// </summary>
  MenuOption menu_type_;

  /// <summary>
  /// 前回までのハイスコア
  /// </summary>
  int high_score_;

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
  /// メニューの選択に使うインデックス
  /// </summary>
  int select_index_;

  /// <summary>
  /// フェードイン・フェードアウトで使用する整数
  /// </summary>
  int fade_;

  /// <summary>
  /// エンターを押されたかの有無
  /// </summary>
  bool is_enter_;
};