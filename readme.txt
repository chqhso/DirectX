KIB説明書

開発者
  姜榮輝(カンヨンフィ)

概要
  3D ゲーム用のライブラリ

開発・動作環境
  C++、DirectX9

機能
  XMLデータparse
    DCCツールでXML化して出力したファイルを内部でParsing
  モデル描画
    Parsingしたデータを利用してモデルを描画
  衝突判定
    簡単な形状の衝突判定
  Heightmap(LOD機能付き)
    HeightMapを利用して地形を生成、QuadTreeとFrustumを利用したCULLとLODとFixedCrackを実装
  Input
    Dinputを利用してKeyBoard, Mouse, XBoxPadからのinputに対応
  Sound Output
    DSoundを利用してSound出力

Sample Demo 操作説明
  W,A,S,D カメラ移動
  ENTER　アニメーションを最初から再生

今後の課題
  BSP, 物理現在未実装のため、実装が必要
  DirectX9から最新のDirectXに変更
  OpenGL追加
