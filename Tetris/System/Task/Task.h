#pragma once
#include <iostream>
#include "DxLib.h"

/// <summary>
/// Taskクラス
/// </summary>
class Task {
public:
  /// <summary>
  //列挙型TaskIdを定義する
  /// <summary>
  enum TaskId {
    /// <summary>
    /// 何もない
    /// </summary>
    kNone,

    /// <summary>
    /// ブートレベル
    /// </summary>
    kBootLevelTask,

    /// <summary>
    /// タイトルレベル
    /// </summary>
    kTitleLevelTask,

    /// <summary>
    /// 設定レベル
    /// </summary>
    kSettingLevelTask,

    /// <summary>
    /// バトルレベル
    /// </summary>
    kBattleLevelTask,

    /// <summary>
    /// リザルトレベル
    /// </summary>
    kResultLevelTask,

    /// <summary>
    /// フィールドタスク
    /// </summary>
    kField,

    /// <summary>
    /// ブロックタスク
    /// </summary>
    kBlock,

    /// <summary>
    /// ゲームモードタスク
    /// </summary>
    kGameMode,

    /// <summary>
    /// スタートUIタスク
    /// </summary>
    kStartUi,

    /// <summary>
    /// フィニッシュUIタスク
    /// </summary>
    kFinishUi,

    /// <summary>
    /// バトル情報UIタスク
    /// </summary>
    kInfoUi,

    /// <summary>
    /// ポーズUIタスク
    /// </summary>
    kPauseUi,
  };

  /// <summary>
  /// デフォルトコンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Task();

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  Task(TaskId task_id);

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~Task();

  /// <summary>
  /// GetId関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>id_</returns>
  TaskId GetId();

  /// <summary>
  /// SetId関数の宣言
  /// </summary>
  /// <param name = "id">TaskId型のid</param>
  /// <returns>なし</returns>
  void SetId(TaskId id);

  /// <summary>
  /// GetTaskUnload関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>task_unload_</returns>
  bool GetTaskUnload();

  /// <summary>
  /// SetTaskUnload関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void SetTaskUnload();

  /// <summary>
  /// ResetTaskUnload関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  void ResetTaskUnload();

  /// <summary>
  /// UpdateFrame関数の宣言
  /// </summary>
  /// <param name = "time">前回のフレームでメインループ処理に掛かった時間（小数）（秒)</param>
  /// <returns>なし</returns>
  virtual void UpdateFrame(float time);

  /// <summary>
  /// RenderFrame関数の宣言
  /// </summary>
  /// <param name>なし</param>
  /// <returns>なし</returns>
  virtual void RenderFrame();

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //タスクID
  /// </summary>
  TaskId id_;

  /// </summary>
  //タスクを下ろしたかの有無
  /// </summary>
  bool task_unload_;
};