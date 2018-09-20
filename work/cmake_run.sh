
echo "Do you wanna compile? [Y/n]"
read ANSWER

case $ANSWER in
     "Y" | "y" | "yes" | "Yes" | "YES" ) 
        rm -rf ../build/*
        rm -rf ../bin/Application*
        cd ../build
        cmake ../source/
        make
        make install;;
    * ) echo "I did nothing.";;
esac

echo "Do you wanna run?  [Y/n]"
read ANSWER
case $ANSWER in
      "Y" | "y" | "yes" | "Yes" | "YES" ) 
        cd ../work
        ../bin/Application_Main;;
    * ) echo "I did nothing.";;
esac
