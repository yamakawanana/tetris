#pragma once

/// <summary>
/// フェードマネージャークラス
/// </summary>
class FadeManager {

public:

  /// <summary>
  /// FadeManagerのインスタンスを取得する
  /// （シングルトンデザインパターン）
  /// </summary>
  /// <returns>FadeManagerのインスタンス</returns>
  static FadeManager* GetInstance() {

    //生成されてないなら動的生成
    if (instance_ == nullptr) {
      instance_ = new FadeManager();
    }

    //FadeManagerのインスタンスを返す
    return instance_;
  }

  /// <summary>
  /// FadeManagerのインスタンスを削除
  /// ゲーム終了時に必ず呼ぶ
  /// </summary>
  static void Destroy() {

    //生成済みなら削除
    if (instance_ != nullptr) {
      delete instance_;
      instance_ = nullptr;
    }
  }

private:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  FadeManager();

  /// <summary>
  /// デストラクタ
  /// </summary>
  ~FadeManager();

  /// <summary>
  /// フェードの状態
  /// </summary>
  enum class FadeState {

    /// <summary>
    /// 状態無し（待機）
    /// </summary>
    kNone,

    /// <summary>
    /// フェードアウト待ち
    /// </summary>
    kWaitFadeOut,

    /// <summary>
    /// フェードイン待ち
    /// </summary>
    kWaitFadeIn,

  };

public:

  /// <summary>
  /// フェードマネージャーの初期化
  /// </summary>
  void InitFadeManager();

  /// <summary>
  /// フェードマネージャーの後処理
  /// </summary>
  void FinFadeManager();

  /// <summary>
  /// フェードマネージャーの更新
  /// </summary>
  /// <param name="delta_time">前回実行フレームからの経過時間（秒）</param>
  void UpdateFadeManager(float delta_time);

  /// <summary>
  /// フェードマネージャーの描画
  /// </summary>
  void RenderFadeManager();

  /// <summary>
  /// フェードアウト開始
  /// </summary>
  /// <param name="time">フェードアウトにかける時間</param>
  void BeginFadeOut(float time);

  /// <summary>
  /// フェードアウトは終了したか
  /// </summary>
  /// <returns>終了しているならtrue</returns>
  bool IsEndFadeOut();

  /// <summary>
  /// フェードイン開始
  /// </summary>
  /// <param name="time">フェードインにかける時間</param>
  void BeginFadeIn(float time);

  /// <summary>
  /// フェードインは終了したか
  /// </summary>
  /// <returns>終了しているならtrue</returns>
  bool IsEndFadeIn();

private:

  /// <summary>
  /// フェードマネージャーのインスタンス
  /// （シングルトン用の静的インスタンス）
  /// </summary>
  static FadeManager* instance_;

  /// <summary>
  /// フェードの状態
  /// </summary>
  FadeState fade_state_;

  /// <summary>
  /// フェード用黒画像のハンドル
  /// </summary>
  int black_image_handle_;

  /// <summary>
  /// 現在のフェード時間
  /// </summary>
  float current_fade_time_;

  /// <summary>
  /// 目標のフェード時間
  /// </summary>
  float target_fade_time_;

  /// <summary>
  /// 現在のフェード画像のアルファ値
  /// </summary>
  int current_fade_alpha_;

  /// <summary>
  /// フェード画像のX座標
  /// </summary>
  int fade_image_pos_x_;

  /// <summary>
  /// フェード画像のY座標
  /// </summary>
  int fade_image_pos_y_;
};
