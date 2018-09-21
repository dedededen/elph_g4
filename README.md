# elph_g4

## Overview
ELPHでのEMT性能チェックに向けたGeant4シミュレーション。  
電子ビームの多重散乱やradiation lengthを見積もります。  
ppcc2018のGeant4をもとに作成しました。  

## Description
原点に物体(今はステレンス鋼)を置き、これに向かって電子ビームを入射させます。  
物体の後方のsensitive detector（空気）で粒子の位置とエネルギーを測定します。  

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
