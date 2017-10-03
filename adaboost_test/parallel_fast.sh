#!/bin/bash
#test with adaboost 1/5 final picture size in detect_multscale
count_pos=0
count_neg=0
root=$(echo "/home/capstone/pipeline/AdaBoost_to_CNN")
start=$(date +%S-%N)
#for i in $(seq 500 2500); do  #with this can switch to running several pictures
	#figure=$(echo "/home/capstone/pipeline/image_test/"$i".JPG")
        #figure=$(echo "/home/capstone/Picture/picture"$i".jpg")   #with this can switch to running several pictures
	figure=$(echo "/home/capstone/expo/picture.jpg")
	figurename=$(echo "picture")
#detecting front
	rm -rf /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_front/*
	/home/capstone/pipeline/AdaBoost_to_CNN/adaboost_test_front $figure
	cd /home/capstone/caffe/python
        python test_pl_front.py /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_front $figurename --gpu --center_only
#detecting left
	rm -rf /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_left/*
	/home/capstone/pipeline/AdaBoost_to_CNN/adaboost_test_left $figure
	cd /home/capstone/caffe/python
        python test_pl_left.py /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_left $figurename --gpu --center_only
#detecting right
	rm -rf /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_right/*
	/home/capstone/pipeline/AdaBoost_to_CNN/adaboost_test_right $figure
	cd /home/capstone/caffe/python
        python test_pl_right.py /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_right $figurename --gpu --center_only 
	/home/capstone/pipeline/picture $figure $root/faces_log_front.txt $root/faces_log_left.txt $root/faces_log_right.txt
#done
end=$(date +%S-%N)
echo $start
echo $end
#echo "positive result: " $count_pos
#echo "negative result: " $count_neg
