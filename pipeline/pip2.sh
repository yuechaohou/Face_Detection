#!/bin/bash
count_pos=0
count_neg=0
for i in $(seq 19 19); do
	figure1="/home/capstone/image_test"
	figure2=".JPG"
	#figure=$figure1$i$figure2
	figure=$(echo "/home/capstone/image_test/"$i".JPG")
	outfile=$(echo "/home/capstone/pipeline/image_result"$i".jpg")
	rm -rf /home/capstone/pipeline/AdaBoost_to_CNN/detected_faces/*
	/home/capstone/pipeline/AdaBoost_to_CNN/AdaBoost_Test $figure
	cd ./AdaBoost_to_CNN/detected_faces
	number=$(ls -l | grep "^-" | wc -l)
	#number=$(($number-1))
	rm -rf /home/capstone/pipeline/face_result.txt
	cd /home/capstone/caffe/python
	python test_face.py $i $number
	cd /home/capstone/pipeline
	i=1
	while read line ;do
		#result=${line##*-}
		echo "line: " $line
		pic_tmp=$line
		read num_tmp
		echo "number: " $num_tmp
		if ( num_tmp==0 );then
		     prob=$num_tmp
		     count_pos=$(($count_pos+1))
		else
		     prob=${num_tmp:0:2}
		     count_neg=$(($count_neg+1))	
		fi
		echo "prob: " $prob
		echo "i: " $i
		#echo $result
		#pic_tmp=${line%-*}
		#echo $pic_tmp
		pic_name=$(echo $pic_tmp | cut -d '/' -f 7 )
		#pic_name=${pick_tmp##*'/'}
		echo $pic_name
		#tmp1='N;'
		#tmp2='a\'
		addline=$((2*$i-1))
		echo $addline
		#tmp3=${tmp1}${addline}${tmp2}${prob}
		tmp1='c '
		tmp2=' '
		#tmp3=${addline}${tmp1}${pic_name}${tmp2}${prob}
		#echo $tmp3
		#tmp3=$( echo 'N;'$addline'a\'$prob )
		sed -i $addline'c '$pic_name' '$prob ./AdaBoost_to_CNN/faces_log.txt
		i=$(($i+1))
		#while read line2 ; do
			#if( line2=pic_name );then
				#tmp1='/'
				#tmp2='/a\'
				#tmp3='/g'
				#tmp4=${tmp1}${pic_name}${tmp2}${result}
				#echo $tmp4 
				#sed -i $tmp4 ./AdaBoost_to_CNN/faces_log.txt
				#break 1
			#fi
		#done < ./AdaBoost_to_CNN/faces_log.txt
	done < ./face_result.txt
	rm -rf output.jpg
	cd ./build
	./picture $figure
	cd ..
	#cp ./output.jpg $outfile
	#display output.jpg
done
