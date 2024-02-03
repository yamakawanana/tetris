#pragma once
#include "DxLib.h"
#include "System/Level/Level.h"
#include "System/LogConsole.h"

/// <summary>
/// TitleLevelクラス
/// </summary>
class TitleLevel : public Level{
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
    /// 破棄フェーズ
    /// </summary>
    kDelete,
  };

  /// <summary>
  // メニューの種類の列挙型MenuOption型を定義する
  /// <summary>
  enum MenuOption {
    /// <summary>
    /// ゲーム開始
    /// </summary>
    kStartGame,

    /// <summary>
    /// 設定
    /// </summary>
    kSetting,

    /// <summary>
    /// ゲーム終了
    /// </summary>
    kExit
  };

  /// <summary>
  // ブロックの角度の列挙型AngleType型を定義する
  /// <summary>
  enum AngleType {
    /// <summary>
    /// 0度
    /// </summary>
    kAngle0,

    /// <summary>
    /// 45度
    /// </summary>
    kAngle45,

    /// <summary>
    /// 90度
    /// </summary>
    kAngle90,

    /// <summary>
    /// 135度
    /// </summary>
    kAngle135,

    /// <summary>
    /// 180度
    /// </summary>
    kAngle180,

    /// <summary>
    /// 225度
    /// </summary>
    kAngle225,

    /// <summary>
    /// 270度
    /// </summary>
    kAngle270,

    /// <summary>
    /// 315度
    /// </summary>
    kAngle315,
  };

  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  TitleLevel();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  TitleLevel(TaskId task_id, TaskManager* task_manager);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  ~TitleLevel();

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
  /// SetTitleGrHandle関数の宣言
  /// </summary>
  /// <param = "title_handle">Titleのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTitleGrHandle(int title_handle);

  /// <summary>
  /// GetTitleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Titleのグラフィックハンドル</returns>
  int GetTitleGrHandle();

  /// <summary>
  /// SetWhiteRectangleGrHandle関数の宣言
  /// </summary>
  /// <param = "white_rectangle_handle">白い長方形のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetWhiteRectangleGrHandle(int white_rectangle_handle);

  /// <summary>
  /// GetWhiteRectangleGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>白い長方形のグラフィックハンドル</returns>
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
  /// フェードイン表示する関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  void FadeIn(int x, int y, int size_x, int size_y, int fade, int plus_alpha);

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
  /// SetStarBackGrHandle関数の宣言
  /// </summary>
  /// <param = "star_back_handle">星空背景のグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetStarBackGrHandle(int star_back_handle);

  /// <summary>
  /// GetStarBackGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>星空背景のグラフィックハンドル</returns>
  int GetStarBackGrHandle();

  /// <summary>
  /// SetTitleLogoGrHandle関数の宣言
  /// </summary>
  /// <param = "title_logo_handle">Titleロゴのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetTitleLogoGrHandle(int title_logo_handle);

  /// <summary>
  /// GetTitleLogoGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>Titleロゴのグラフィックハンドル</returns>
  int GetTitleLogoGrHandle();

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
  /// SetBlockGrHandle関数の宣言
  /// </summary>
  /// <param = "block_gr_handle">ブロックのグラフィックハンドル</param>
  /// <returns>なし</returns>
  void SetBlockGrHandle(int block_gr_handle);

  /// <summary>
  /// GetBlockGrHandle関数の宣言
  /// </summary>
  /// <param>なし</param>
  /// <returns>ブロックのグラフィックハンドル</returns>
  int GetBlockGrHandle();

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
  /// Title画面のグラフィックハンドル
  /// </summary>
  int title_handle_;

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
  /// メニューの種類
  /// </summary>
  MenuOption menu_type_;

  /// <summary>
  /// メニューの選択に使うインデックス
  /// </summary>
  int select_index_;

  /// <summary>
  /// 動画ハンドル
  /// </summary>
  int movie_handle_;

  /// <summary>
  /// 星空背景のグラフィックハンドル
  /// </summary>
  int star_back_handle_;

  /// <summary>
  /// Titleロゴのグラフィックハンドル
  /// </summary>
  int title_logo_handle_;

  /// <summary>
  /// 白い長方形のグラフィックハンドル
  /// </summary>
  int white_rectangle_handle_;

  /// <summary>
  /// 音量
  /// </summary>
  int sound_volume_;

  /// <summary>
  /// フェードイン・フェードアウトで使用する整数
  /// </summary>
  int fade_;

  /// <summary>
  /// エンターを押されたかの有無
  /// </summary>
  bool is_enter_;

  /// <summary>
  /// 選択されている項目を囲む枠のグラフィックハンドル
  /// </summary>
  int selected_button_handle_;

  /// <summary>
  /// ブロックの画像のグラフィックハンドル
  /// </summary>
  int block_gr_handle_;

  /// <summary>
  /// 角度情報
  /// </summary>
  AngleType angle_type_;
};