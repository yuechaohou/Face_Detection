#!/usr/bin/env sh
DATA=/home/capstone/adaboost/adaboost_test
MY=/home/capstone/cnn_train_models/train_front
negative=0
positve=1

echo "Create test.txt..."
rm -rf $MY/test3.txt
for i in image208 image359 image127 image609 image415 image010 image650 image647 image709 image493 image182 image522 image515 image312 image155 image677 image660 image156 image369 image268 image446 image330 image127 image014 image157 image541 image512 image639 image291 image523 image621 image372 image169 image620 image267 image584 image503 image203 image389 image370 image569 image444 image178 image242 image628 image206 image205 image446 image234 image446 image586 image681 image648 image585 image695 image677 image284 image493 image603 image576 image175 image382 image234 image216 image160 image373 image672 image663 image449 image348 image320 image304 image664 image370 image418 image450 image448 #image495 image182 image683 image227 image055 image650 image162 image512 image503 image125 image083 image155 image600 image659 image330 image268 image051 image546 image429 image296 image504 image250 image031 image010 image442 image335 image674 image099 image625 image282 image547 image406 image337 image388 image634 image264 image196 image668 image062 image700 image665 image145 image141 image552 image676 image471 image106 image013 image175 image407 image182 image679 image658 image213 image690 image258 image421 image522 image357 image332 image091 image063 image025 image300 image323 image531 image564 image520 image485 image626 image378 image436 image058 image519 image146 image020 image148 image125 image620 image323 image532 image088 image160 image348 image301 image008 image607 image594 image531 image122 image213 image494 image057 image110 image080 image381 image641 image644 image059 image284 image556 image437 image592 image486 image114 image025 image507 image262 image150 image413 image457 image554 image373 image617 image189 image546 image626 image668 image427 image315 image662 image640 image681 image006 image036 image633 image259 image549 image435 image318 image119 image277 image041 image711 image636 image155 image022 image429 image289 image044 image000 image618 image599 
do
mv $DATA/new_front_positive/$i*.jpg $DATA/front_test/positive
mv $DATA/new_front_negative/$i*.jpg $DATA/front_test/negative
find $DATA/front_test/negative -name $i*.jpg | cut -d '/' -f 1-12 | sed "s/$/ 0/">>$MY/test3.txt
find $DATA/front_test/positive -name $i*.jpg | cut -d '/' -f 1-12 | sed "s/$/ 1/">>$MY/test3.txt
done
echo "All done"
