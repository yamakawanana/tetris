#pragma once
#include <vector>
#include <fstream>
#include "System/LogConsole.h"

/// <summary>
/// FileManagerクラス
/// </summary>
class FileManager {
public:

  /// <summary>
  /// コンストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  FileManager();

  /// <summary>
  /// デストラクタ
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  virtual ~FileManager();

  /// <summary>
  /// インスタンスを生成する
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  static void CreateInstance();

  /// <summary>
  /// インスタンスを取得する
  /// </summary>
  /// <param>なし</param>
  /// <returns>ゲーム情報のインスタンス</returns>
  static FileManager* GetInstance();

  /// <summary>
  /// インスタンスを解放する
  /// </summary>
  /// <param>なし</param>
  /// <returns>なし</returns>
  static void ReleaseInstance();

  /// <summary>
  /// ReadDataFromFile関数の宣言
  /// </summary>
  /// <param="filename">ファイル名</param>
  /// <param="num">データを読み込む整数</param>
  /// <returns>なし</returns>
  std::vector<int> ReadDataFromFile(std::string filename);

private:
  /// <summary>
  /// メンバ変数
  /// </summary>

  /// </summary>
  //インスタンス
  /// </summary>
  static FileManager* file_info_;
};

