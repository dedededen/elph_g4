
echo "Do you wanna compile? [Y/n]"
read ANSWER

case $ANSWER in
     "Y" | "y" | "yes" | "Yes" | "YES" ) 
        rm -rf ../build
        rm -rf ../bin/Application*
        mkdir ../build
        cd ../build
        cmake ../source/
        make
        make install;;
    * ) echo "I did nothing.";;
esac

echo "Do you wanna run?  [Y/n]"
read ANSWER

echo "How the width of a material is?"
read width
case $ANSWER in
      "Y" | "y" | "yes" | "Yes" | "YES" ) 
        cd ../work
        ../bin/Application_Main $width
        mv ./data/test.root ./data/wid_$width.root;;
    * ) echo "I did nothing.";;
esac

