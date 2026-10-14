# ヴイストン製ロボット用micro-ROS Arduinoライブラリ（ROS 2 Jazzy）

ヴイストン製の台車ロボットやAMIR 740で、ArduinoのスケッチからROS 2 Jazzyと通信するためのライブラリです。
[micro_ros_arduino v2.0.8-jazzy](https://github.com/micro-ROS/micro_ros_arduino/releases/tag/v2.0.8-jazzy)を基に、ヴイストン製ロボット用のメッセージ型を追加しています。

配布ZIPにはESP32・ESP32-S3向けの事前ビルド済みライブラリ、メッセージのヘッダー、サンプルスケッチを同梱しています。
ReleaseページからZIPをダウンロードし、Arduinoの`libraries`フォルダに配置してご利用ください。

台車の通信確認と使用方法は、台車の標準ライブラリおよび付属ドキュメントを参照してください。

## 目次

- [利用環境](#利用環境)
- [Arduino IDEへの導入](#arduino-ideへの導入)
- [スケッチでの使い方](#スケッチでの使い方)
- [PC側の準備](#pc側の準備)
- [同梱のメッセージとサンプル](#同梱のメッセージとサンプル)
- [お問い合わせ](#お問い合わせ)

## 利用環境

| 項目 | この配布物の対象環境 |
| --- | --- |
| マイコン | ESP32、ESP32-S3 |
| Arduino用ボードパッケージ | [Arduino-ESP32 2.0.13](https://github.com/espressif/arduino-esp32/releases/tag/2.0.13) |
| PC側のROS 2 | Jazzy |
| micro-ROS Agent | Jazzy |
| 標準シリアル通信 | 921600 bps |

Arduino-ESP32 3.xはこの配布物では未検証です。
ボードの選択や接続方法は、お使いのロボットの説明書も併せてご確認ください。

### 実機で確認した構成

以下の構成で、対応スケッチの再ビルド、実機への書き込み、接続テストの成功を確認しています（確認報告日: 2026-10-08）。

| ロボット | 制御基板 |
| --- | --- |
| メガローバーVer.3.0 | VS-WRC058 |
| メガローバーF120A | VS-WRC058 |

## Arduino IDEへの導入

1. [Releaseページ](https://github.com/vstoneofficial/micro_ros_arduino/releases)を開き、**Jazzy用**リリースのAssetsからArduino用の配布ZIPをダウンロードします。
2. ZIPを解凍し、中にある`micro_ros_arduino_jazzy`フォルダを取り出します。
3. Arduinoのスケッチブック内の`libraries`フォルダへ、そのフォルダを丸ごと配置します。`libraries`がない場合は作成してください。
4. Arduino IDEを起動し直します。

スケッチブックの場所はArduino IDEの設定画面で確認できます。
通常の配置例は次のとおりです。フォルダ名は`libraries`です。

```text
Arduino/
└─ libraries/
   └─ micro_ros_arduino_jazzy/
      ├─ library.properties
      ├─ examples/
      ├─ extras/
      └─ src/
         ├─ micro_ros_arduino_jazzy.h
         ├─ esp32/libmicroros.a
         └─ esp32s3/libmicroros.a
```

`micro_ros_arduino_jazzy`の直下に`library.properties`があることを確認してください。
ZIP内のフォルダをさらに別のフォルダで囲むと、Arduino IDEから正しく認識されない場合があります。
スケッチブックの場所の確認方法は[Arduino公式の案内](https://support.arduino.cc/hc/en-us/articles/4412950938514-Open-the-Sketchbook-folder)を参照してください。

### 既存ライブラリを更新する場合

Arduino IDEを閉じ、既存の同じROS 2版のライブラリフォルダを`libraries`の外へバックアップしてから、新しいフォルダを丸ごと配置してください。
古いフォルダへのファイルの上書きだけで更新すると、旧版だけに存在するヘッダーが残ることがあります。
Arduino IDEを起動し直し、対応スケッチを再ビルドして、USB/UARTで実機へ書き込んでください。

## スケッチでの使い方

スケッチの先頭で、Jazzy用の入口ヘッダーを読み込みます。台車のエンコーダーメッセージを使う場合の例です。

```cpp
#include <micro_ros_arduino_jazzy.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <vs_rdrover_interfaces/msg/encoder_stamped.h>
```

`micro_ros_arduino_jazzy.h`は、すべてのROSヘッダーより前に記述してください。
複数の`.cpp`に分ける場合は、ROSを使用する各ファイルで同じ入口ヘッダーを読み込みます。

### Humble版もインストールしている場合

Humble版は`Arduino/libraries/micro_ros_arduino_humble`、Jazzy版は`Arduino/libraries/micro_ros_arduino_jazzy`に配置して共存できます。
1つのスケッチでは1つのROS 2版を選び、PC側のROS 2とAgentも同じ版に合わせてください。
Jazzy用スケッチでは`micro_ros_arduino_jazzy.h`を使用します。
従来の`micro_ros_arduino.h`だけを読み込むスケッチは、版を明示する入口ヘッダーへ変更してください。
同じROS 2版の古いライブラリを別名で重複してインストールしている場合は、使用する版だけを残してください。

## PC側の準備

ROS 2 Jazzyとmicro-ROS Agentの動作環境を用意します。
ROS 2の導入は[ROS 2 Jazzyの公式案内](https://docs.ros.org/en/jazzy/Installation.html)を参照してください。

台車の`EncoderStamped`をPC側で読み取るには、独立した[`vs_rdrover_interfaces`リポジトリ](https://github.com/vstoneofficial/vs_rdrover_interfaces/tree/jazzy)から、PC側のROS 2ワークスペースへパッケージを導入します。


AMIRのメッセージを使う場合は、同梱の[`amir_interfaces`](extras/library_generation/extra_packages/amir_interfaces)をPC側へコピーし、`colcon build --packages-select amir_interfaces`でビルドします。

### micro-ROS Agentの起動

標準のシリアル通信は**921600 bps**です。Agent側も同じ速度に設定します。
Linux上のDockerでAgentを起動する例です。Dockerの利用環境を用意し、ボードをUSB/UARTで接続してから実行してください。

```bash
docker run -it --rm --net=host --device=/dev/ttyUSB0 \
  microros/micro-ros-agent:jazzy serial --dev /dev/ttyUSB0 -b 921600
```

`/dev/ttyUSB0`は、お使いのボードのシリアルポートに合わせて、上の2か所を変更してください。
例えば`/dev/ttyACM0`として認識されるボードもあります。
Agentと通信している間は、同じポートを使うArduino IDEのシリアルモニターを閉じてください。


## 同梱のメッセージとサンプル

| 用途 | ROS 2の型 | サンプル |
| --- | --- | --- |
| 研究開発用台車のエンコーダー | `vs_rdrover_interfaces/msg/EncoderStamped` | [micro-ros_encoder_stamped](examples/micro-ros_encoder_stamped/micro-ros_encoder_stamped.ino) |
| AMIR 740の指令・センサー値 | `amir_interfaces/msg/AmirCmd`、`amir_interfaces/msg/AmirSensor` | [micro-ros_amir](examples/micro-ros_amir/micro-ros_amir.ino) |

`EncoderStamped`は取得時刻と可変長配列のエンコーダーカウント値を持ちます。

AMIRの両メッセージは、`float32[6] angle`（mrad）と`float32[6] vel`（mrad/s）です。
`micro-ros_amir`は指令の受信とゼロ値の疑似センサー送信を行う通信例です。


## お問い合わせ

ヴイストン製ロボットをご購入のお客様からの不具合のご報告やご相談は、
[ヴイストンのお問い合わせ窓口](https://www.vstone.co.jp/contact/index.html)へお寄せください。
製品名、使用するROS 2版、ライブラリのバージョン、ボードとArduino-ESP32のバージョン、
発生状況・再現手順・エラーログをお知らせいただくと、確認がスムーズになります。

