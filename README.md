# M5Dial firmware

M5Dial v1.1 用のホームメニューとアプリをまとめたファームウェアです。起動するとホームが表示され、ダイヤルでアプリを選び、ボタンを押して開きます。今後のアプリは `src/apps/` に追加できます。

## 操作

| 画面 | 回転 | 短押し | 約1秒の長押し |
| --- | --- | --- | --- |
| ホーム | QR ManagerとDevice Infoを巡回して選択 | 選んだアプリを開く | 選んだアプリを開く |
| QR Manager | X、GitHub、PeachTech、化身デモを切り替え | QRコードを拡大・元に戻す | ホームに戻る |
| Device Info | - | - | ホームに戻る |

アプリ内ではボタンを約1秒押し続けると、その時点でホームに戻ります。

QR Managerの登録内容:

| 名前 | URL |
| --- | --- |
| X | https://x.com/na2kera_0510 |
| GitHub | https://github.com/na2kera |
| PeachTech | https://x.com/PeachTech_0927 |
| 化身デモ | https://mobile-mr-keshin.na2kera.workers.dev/demos/ex9-1-keshin/ |

## ビルドと書き込み

PlatformIO CLI を使用します。

```sh
pio run
pio run -t upload
```

ボードは `platformio.ini` で M5Stack StampS3 に設定しています。M5Dial v1.1 は Stamp-S3A を搭載しています。

## ファイル構成

- `src/main.cpp`: 起動処理と画面間の操作
- `src/home/`: ホームメニュー
- `src/apps/qr_manager/`: QR Manager本体と埋め込みアイコン
- `src/apps/device_info/`: 端末情報画面
- `assets/source/`: 受け取った元画像
- `assets/icons/`: 画面向けの32×32 PNG
- `tools/embed_icons.py`: PNGから `src/apps/qr_manager/icons.h` を再生成するスクリプト

QRのURLや名前を変える場合は `src/apps/qr_manager/qr_manager.cpp` の `items` を編集します。アイコンを変えた場合は `assets/icons/` 内のPNGを差し替え、`python3 tools/embed_icons.py` を実行してください。
