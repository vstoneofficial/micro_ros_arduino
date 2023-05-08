![banner](.images/banner-dark-theme.png#gh-dark-mode-only)
![banner](.images/banner-light-theme.png#gh-light-mode-only)

# Vstoneロボット用のmicro-ROSライブラリ

Vstoneロボット用のArduino IDEのmicro-ROSライブラリの改造版です。

- [Vstoneロボット用のmicro-ROSライブラリ](#vstoneロボット用のmicro-rosライブラリ)
  - [開発環境](#開発環境)
  - [Arduino IDEへのライブラリの追加](#arduino-ideへのライブラリの追加)
    - [ZIP形式の ライブラリをインストール](#zip形式の-ライブラリをインストール)

## 開発環境
[Arduino core for the ESP32 (v2.0.2)](https://github.com/espressif/arduino-esp32/releases/tag/2.0.2)

## Arduino IDEへのライブラリの追加
### ZIP形式の ライブラリをインストール
[こちらのリリース](https://github.com/vstoneofficial/micro_ros_arduino/releases) から、Arduino用micro-ROSライブラリの最新リリースをダウンロードしてください。

プロジェクトに追加してください `スケッチ -> Include library -> Add .ZIP Library...`

`examples`フォルダにあるmicro-ROSのスケッチを確認できます。

---

元のREADMEは[こちら](https://github.com/micro-ROS/micro_ros_arduino#readme)です。