#include <iostream>
#include "System/FileManager.h"

//ファイル情報インスタンスの初期化
FileManager* FileManager::file_info_ = nullptr;

/// <summary>
/// コンストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
FileManager::FileManager()
{
  DEBUG_PRINT(FileManagerのコンストラクタ);
}

/// <summary>
/// デストラクタ
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
FileManager::~FileManager() {
  DEBUG_PRINT(FileManagerのデストラクタ);
}

/// <summary>
/// インスタンスを生成する
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void FileManager::CreateInstance() {
  //まだインスタンスが生成されていなければ、インスタンスを生成する
  if (file_info_ == nullptr) {
    file_info_ = new FileManager();
  }
}

/// <summary>
/// インスタンスを取得する
/// </summary>
/// <param>なし</param>
/// <returns>ゲーム情報のインスタンス</returns>
FileManager* FileManager::GetInstance() {
  return file_info_;
}

/// <summary>
/// インスタンスを解放する
/// </summary>
/// <param>なし</param>
/// <returns>なし</returns>
void FileManager::ReleaseInstance() {
  if (file_info_ != nullptr) {
    delete file_info_;
    file_info_ = nullptr;
  }
}

/// <summary>
/// ReadDataFromFile関数の定義
/// </summary>
/// <param="filename">ファイル名</param>
/// <param="num">データを読み込む整数</param>
/// <returns>なし</returns>
std::vector<int> FileManager::ReadDataFromFile(std::string filename) {

  std::vector<int> values;

  // CSVファイルを読み込む
  std::ifstream input_file(filename);

  // ファイルが正しく開かれたか確認
  if (input_file.is_open()) {

    int num;
    // 値をファイルから読み取る
    while (input_file >> num) {
      // 読み取り成功
      values.push_back(num);
      DEBUG_PRINT_VAR(num);
    }

    // ファイルを閉じる
    input_file.close();
  }
  else {
    std::cerr << "ファイルを開くことができなかった" << std::endl;
  }
  return values;
}