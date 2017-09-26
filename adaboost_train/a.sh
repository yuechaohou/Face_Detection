./create_left_postive_vec.sh
echo "finished0"
./create_front_postive_vec.sh
echo "finished1"
./create_right_postive_vec.sh
echo "finished3"
./train_left_cascade.sh
echo "finished4"
./train_front_cascade.sh
echo "finished5"
./train_right_cascade.sh
echo "finished6"
cd ../adaboost_test/build/
echo "finished7"
./exe 