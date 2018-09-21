
exho "Do you wanna loop?"
reaf ANSWER
case $ANSWER in
     "Y" | "y" | "yes" | "Yes" | "YES" ) 
         for i in 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 
         do
             ../bin/Application_Main $i
             mv ./data/test.root ./data/wid_$i.root
             echo "done!"
         done
         ;;
    * ) echo "Goodbye!!";;
esac


