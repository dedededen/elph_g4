# elph_g4
Geant4 simulation of ELPH about EMT

#ディレクトリ構造
elph_g4
    bin    ; make install することで自動的に生成される
    build  ; ビルド用ディレクトリ、cmake_run.sh すれば生成される
    source ; ソースファイル置き場
           src
           include
    work   ; 作業ディレクトリ、この中で cmake_run.sh を実行すればとりあえず動く
           data     ; データ置き場
           analysis ; 解析スクリプトを置いてくつもり
           
# 変更予定
