# ヴイストン研究開発用台車のエンコーダーメッセージ

`vs_rdrover_interfaces`は、ヴイストン製の研究開発用台車ロボットで共通利用するROS 2 Jazzyインターフェースパッケージです。現在はエンコーダー値のメッセージ型を提供します。
Arduino側のスケッチから送信した値を、PC側のROS 2ノードで受信し、台車の状態確認や走行距離・姿勢の計算に利用できます。

ヴイストン版micro-ROS Arduinoライブラリの配布ZIPに、Arduino向けの生成済みヘッダー・ライブラリと、このPC向けソースパッケージを同梱しています。
PC側への導入元は、独立した[`vs_rdrover_interfaces`リポジトリ](https://github.com/vstoneofficial/vs_rdrover_interfaces/tree/jazzy)です。

台車の通信確認と使用方法は、台車の標準ライブラリおよび付属ドキュメントを参照してください。

旧開発版の`vstone_rdrover_interfaces`から名称を変更しています。旧名称とはROS 2上の型名が異なるため、Arduino側とPC側の両方を新名称に揃えてビルドし直してください。

## 目次

- [Arduinoライブラリの導入](#arduinoライブラリの導入)
- [PC側への導入](#pc側への導入)
- [メッセージの内容](#メッセージの内容)
- [Arduino側での実装](#arduino側での実装)
- [お問い合わせ](#お問い合わせ)

## Arduinoライブラリの導入

1. [Releaseページ](https://github.com/vstoneofficial/micro_ros_arduino/releases)のJazzy用リリースから、Arduino用の配布ZIPをダウンロードします。
2. ZIPを解凍し、`micro_ros_arduino_jazzy`フォルダをArduinoスケッチブック内の`libraries`へ丸ごと配置します。
3. Arduino IDEを起動し直します。

```text
Arduino/libraries/micro_ros_arduino_jazzy/
├─ library.properties
├─ examples/micro-ros_encoder_stamped/
├─ extras/library_generation/extra_packages/vs_rdrover_interfaces/
└─ src/vs_rdrover_interfaces/msg/encoder_stamped.h
```

ライブラリの配置方法は、[ライブラリ全体の導入案内](../../../../README.md#arduino-ideへの導入)を参照してください。

## PC側への導入

エンコーダー値を受信するPCに、Git、ROS 2 Jazzy、`colcon`、初期設定済みの`rosdep`を用意します。
このパッケージのビルドには`ament_cmake`・`rosidl_default_generators`・`std_msgs`を使用します。

独立した[`vs_rdrover_interfaces`リポジトリ](https://github.com/vstoneofficial/vs_rdrover_interfaces/tree/jazzy)をPC側のROS 2ワークスペースへ取得します。
このArduinoライブラリと同じメッセージ定義を持つ公開コミットは[`b3c0c8e`](https://github.com/vstoneofficial/vs_rdrover_interfaces/commit/b3c0c8e2c0fae8dbcfd822b37063b41e3afca427)です。以下ではそのコミットを使用します。

以下はLinuxで新しいワークスペースを用意する例です。
既存のワークスペースを使う場合はパスを読み替え、同じパッケージを重複して配置しないでください。

```bash
source /opt/ros/jazzy/setup.bash
mkdir -p ~/rover_ws/src
cd ~/rover_ws/src
git clone --branch jazzy https://github.com/vstoneofficial/vs_rdrover_interfaces.git
git -C vs_rdrover_interfaces checkout --detach b3c0c8e2c0fae8dbcfd822b37063b41e3afca427
cd ~/rover_ws
rosdep install --from-paths src/vs_rdrover_interfaces --ignore-src --rosdistro jazzy -y
colcon build --packages-select vs_rdrover_interfaces
source install/setup.bash
ros2 interface show vs_rdrover_interfaces/msg/EncoderStamped
```

出力に`std_msgs/Header header`と`int32[] counts`が表示されれば、メッセージ定義を利用できます。
新しいターミナルを開いたときも、ROS 2とワークスペースの環境を読み込んでください。

```bash
source /opt/ros/jazzy/setup.bash
source ~/rover_ws/install/setup.bash
```

Arduino側とPC側は同じメッセージ定義を使用します。
配布物の`src/vs_rdrover_interfaces`はArduino向けの生成済みヘッダーです。PC側では、上記の独立リポジトリから取得したソースパッケージをビルドしてください。

## メッセージの内容

ROS 2の型名は`vs_rdrover_interfaces/msg/EncoderStamped`です。

```text
std_msgs/Header header
int32[] counts
```

| フィールド | 内容 |
| --- | --- |
| `header.stamp` | 1回の取得処理で全エンコーダーの読取りを完了した、ROSと同期した時刻 |
| `header.frame_id` | 初期構成では空文字列 |
| `counts` | 各モーターの生の符号付き32 bitエンコーダーカウント値。単位はcount |

`counts`の要素数がエンコーダー数を表します。現在の2輪メガローバーは`counts[0]`が左、`counts[1]`が右です。
他の機種では、その機種のスケッチと説明に従って車輪・モーターとの対応を確認してください。
同じ機種の通常運転中は、配列の順序と要素数を維持します。

角度や距離へ変換する際は、お使いの機種のエンコーダー分解能や車輪径などを使って計算します。
このメッセージの値には、角度・距離変換、符号反転、カウンタの周回補正は含まれません。
32 bitカウンタの周回やモーター再起動時のリセットがあるため、受信側でカウントの差分を扱う際はこれらを考慮してください。

順次読み取る場合、`header.stamp`は全要素を完全に同時取得した時刻を意味しません。
送信側では、全読取りに成功し、ROSとの時刻同期ができた回だけを送信します。
読取りに失敗した要素を配列から削除したり、前回の値を今回の値として送信したりしないでください。
受信側ではデータの途絶も検出し、最後に受信した値の取得時刻を確認してください。

## Arduino側での実装

スケッチの先頭でJazzy用の入口ヘッダーと、メッセージのヘッダーを読み込みます。

```cpp
#include <micro_ros_arduino_jazzy.h>
#include <rcl/rcl.h>
#include <rclc/rclc.h>
#include <vs_rdrover_interfaces/msg/encoder_stamped.h>
```

Publisherの型指定には次を使用します。

```cpp
ROSIDL_GET_MSG_TYPE_SUPPORT(vs_rdrover_interfaces, msg, EncoderStamped)
```

[micro-ros_encoder_stamped](../../../../examples/micro-ros_encoder_stamped/micro-ros_encoder_stamped.ino)を参考に、疑似値の取得処理を機種に合ったエンコーダーの読取り処理へ置き換えてください。
同梱サンプルの配列長は`ENCODER_COUNT`で指定し、既定値は2です。
メッセージ型は可変長配列であり、2・4・8要素などの固定長や最大8要素という制限はありません。
実際に扱う要素数に合わせて、メモリ容量とシリアライズ後のサイズ・通信設定を確認してください。

### 配列と時刻の扱い

- `counts.data`の領域を用意し、送信する要素数を`counts.size`、確保した要素数を`counts.capacity`に設定します。常に`size <= capacity`を守ってください。
- 同梱サンプルは静的な配列と、空の`frame_id`用の1 byteバッファを使用します。このメッセージに生成関数の`__init`・`__fini`・`__destroy`や`free()`を呼ばず、サンプルと同じ方法で手動で設定してください。静的バッファは解放不要です。
- 動的確保を使う場合は、初期化時に必要な容量を確保し、対応する解放処理を使用してください。周期処理中の配列の確保・再確保は避けてください。
- サンプルは`rclc_executor_prepare()`でexecutorのwait setも初期化時に確保します。独自の周期処理でも、初回の遅延確保が発生しないよう同じ構成を参考にしてください。
- 時刻は全エンコーダーの読取り直後に設定します。サンプルは起動時に時刻同期します。実機のスケッチでは、運転中の同期の維持・喪失検出、再同期とAgentへの再接続を実装してください。同期フラグの確認だけでは、長時間の時刻精度や再接続は保証されません。
- Agentのepoch同期はPCのシステム時刻を使用します。`/clock`によるシミュレーション時刻を使う構成では、取得時刻の付け方を別途合わせてください。

## お問い合わせ

製品の利用に関するご相談は、[ヴイストンのお問い合わせ窓口](https://www.vstone.co.jp/contact/index.html)へお寄せください。
製品名、ROS 2版、ライブラリのバージョン、使用するボード、再現手順とエラーログをお知らせください。
