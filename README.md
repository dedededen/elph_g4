# elph_g4

## 概要
ELPHでのEMT性能チェックに向けたGeant4シミュレーション。  
電子ビームの多重散乱やradiation lengthを見積もります。  
ppcc2018のGeant4をもとに作成しました。  

## 内容
原点に物体(今はステレンス鋼)を置き、これに向かって電子ビームを入射させます。  
物体の後方のsensitive detector（空気）で粒子の位置とエネルギー、種類を記録します。  

### セットアップ
|source e+|-----(?mm)----|material|----(?mm)--|detector|

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

## 変更予定
- main関数の引数として、materialの厚みを自由に変更できるようにする
    - 出力ファイル名など何か所変更する必要がある。
- shスクリプトで厚みを変えながら、シミュレーションを実行
- SUSでのradiation length を求め、結果が計算とconsistentか確認
    - 解析コードをつくる
- EMTに適した物体を置いて、シミュレーションを実行
