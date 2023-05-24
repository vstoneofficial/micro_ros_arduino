# Vstoneロボット用のmicro-ROSライブラリ

[micro_ros_arduino](https://github.com/micro-ROS/micro_ros_arduino)をベースに、Vstone製ロボット用の機能を追加したArduinoライブラリです。

# 目次
- [動作確認環境](#動作確認環境)
- [Arduino IDEへのライブラリの追加](#arduino-ideへのライブラリの追加)
  - [ZIP形式の ライブラリをインストール](#zip形式の-ライブラリをインストール)
- [追加機能](#追加機能)

## 動作確認環境
[Arduino core for the ESP32 (v2.0.2)](https://github.com/espressif/arduino-esp32/releases/tag/2.0.2)

## Arduino IDEへのライブラリの追加
### ZIP形式の ライブラリをインストール
[こちらのリリース](https://github.com/vstoneofficial/micro_ros_arduino/releases) から、Arduino用micro-ROSライブラリの最新リリースをダウンロードしてください。

プロジェクトに追加してください `スケッチ -> Include library -> Add .ZIP Library...`

`examples`フォルダにあるmicro-ROSのスケッチを確認できます。

## 追加機能
- [AMIR 740](https://www.vstone.co.jp/products/amir740/index.html)用の専用メッセージ型を追加。

---

元のREADMEは[こちら](https://github.com/micro-ROS/micro_ros_arduino#readme)です。