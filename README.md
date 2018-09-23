# elph_g4

## 概要
ELPHでのEMT性能チェックに向けたGeant4シミュレーション。  
電子ビームの多重散乱やradiation lengthを見積もります。  
ppcc2018のGeant4課題をもとに作成しました。  

## 内容
原点に物体(今はステレンス鋼)を置き、これに向かって電子ビームを入射させます。  
物体の後方のsensitive detector（空気）で粒子の位置とエネルギー、種類を記録します。  

### セットアップ
|source e+|-----(10mm-width/2)----|material|--(30.0mm)--|detector|  
detector 280mm * 280 mm * 1mm(air)
width is material's

## ディレクトリ構造
- elph_g4  
    - bin    ; make install することで自動的に生成される  
    - build  ; ビルド用ディレクトリ、cmake_run.sh すれば生成される  
    - source ; ソースファイル置き場  
        - src
        - include  
    - work   ; 作業ディレクトリ　　
        - data     ; データ置き場  
        - analysis ; 解析スクリプトを置いてくつもり  
## 使い方
/work で sh cmake_run.sh を実行するだけ。（今のところは）
loop~.shで厚みを変えるループをまわす
/work/dataにデータが生成される
par_idにおけるは以下の内容になっている
　1; e+
  2; e+
  3; e-
  4; gamma
  5; else(neutron)
## 変更予定
- shスクリプトで厚みを変えながら、シミュレーションを実行
- SUSでのradiation length を求め、結果が計算とconsistentか確認
    - 解析コードをつくる
- EMTに模した物体を置いて、シミュレーションを実行
