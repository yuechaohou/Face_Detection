#!/bin/bash
#test with adaboost 1/10 final picture size in detect_multscale
count_pos=0
count_neg=0
root=$(echo "/home/capstone/pipeline/AdaBoost_to_CNN")
start=$(date +%S-%N)
for i in $(seq 2115 2125); do
#for i in 1241 1252 1254 1256 1257
#do
	#figure=$(echo "/home/capstone/pipeline/image_test/"$i".JPG")
        #figure=$(echo "/home/capstone/Picture/picture"$i".jpg")
	figure=$(echo "/home/capstone/gakki/picture"$i".jpg")
	figurename=$(echo "picture"$i)
	outfile=$(echo "/home/capstone/pipeline/result_front/"$i".jpg")
#detecting front
	rm -rf /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_front/*
	/home/capstone/pipeline/AdaBoost_to_CNN/adaboost_test_front10 $figure
	cd /home/capstone/caffe/python
        python test_pl_front.py /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_front $figurename --gpu --center_only
#detecting left
	rm -rf /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_left/*
	/home/capstone/pipeline/AdaBoost_to_CNN/adaboost_test_left10 $figure
	cd /home/capstone/caffe/python
        python test_pl_left.py /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_left $figurename --gpu --center_only
#detecting right
	rm -rf /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_right/*
	/home/capstone/pipeline/AdaBoost_to_CNN/adaboost_test_right10 $figure
	cd /home/capstone/caffe/python
        python test_pl_right.py /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces_right $figurename --gpu --center_only 
	/home/capstone/pipeline/picture $figure $root/faces_log_front.txt $root/faces_log_left.txt $root/faces_log_right.txt
done
end=$(date +%S-%N)
echo $start
echo $end
#echo "positive result: " $count_pos
#echo "negative result: " $count_neg
