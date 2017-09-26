#!/bin/bash
cd ~/adaboost/adaboost_sample/tmp
./exe ../new_pos_info_left.txt ~/adaboost/adaboost_sample/new_left_pos_sample/ > pos_info_left.txt
./exe ../new_pos_info_front.txt ~/adaboost/adaboost_sample/new_front_pos_sample/ > pos_info_front.txt
./exe ../new_pos_info_right.txt ../new_right_pos_sample/> pos_info_right.txt

cd ~/adaboost/adaboost_sample/
# cat pos_info_front.txt > pos_info.txt
# cat pos_info_left.txt >> pos_info.txt
# cat pos_info_right.txt >> pos_info.txt
cp -r new_left_pos_sample/ ~/adaboost/adaboost_train/left_pos_sample/
cp tmp/pos_info_left.txt ~/adaboost/adaboost_train/left_pos_sample/pos_info_left.txt 
cp -r new_right_pos_sample/ ~/adaboost/adaboost_train/right_pos_sample/
cp tmp/pos_info_right.txt ~/adaboost/adaboost_train/right_pos_sample/pos_info_right.txt 
cp -r new_front_pos_sample/ ~/adaboost/adaboost_train/front_pos_sample/
cp tmp/pos_info_front.txt ~/adaboost/adaboost_train/front_pos_sample/pos_info_front.txt 

cd ../adaboost_train/
./create_left_postive_vec.sh
./create_front_postive_vec.sh
./create_right_postive_vec.sh
./train_left_cascade.sh
./train_front_cascade.sh
./train_right_cascade.sh

cd ~/adaboost/adaboost_test/build_exe
mkdir ../new_negative/
mkdir ../new_positive/
./exe

