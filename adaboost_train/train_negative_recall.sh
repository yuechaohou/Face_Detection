
# cp -r  left_pos_sample left_pos_sampe~
# #cp -r  front_pos_sample front_pos_sampe~
# cp -r  right_pos_sample right_pos_sampe~
# cp -r lbp_neg lbp_neg_left
# cp -r lbp_neg lbp_neg_front
# cp -r lbp_neg lbp_neg_right

#cat neg_list.txt |sed s/lbp_neg/lbp_neg_left/g >neg_list_left.txt
cat neg_list.txt |sed s/lbp_neg/lbp_neg_front/g >neg_list_front.txt
cat neg_list.txt |sed s/lbp_neg/lbp_neg_right/g >neg_list_right.txt


 cd ../adaboost_sample/tmp
# cp not_recall_file_left_dataset/* /home/capstone/adaboost/adaboost_train/left_pos_sample/
# cp not_recall_file_front_dataset/* /home/capstone/adaboost/adaboost_train/front_pos_sample/
# cp not_recall_file_right_dataset/* /home/capstone/adaboost/adaboost_train/right_pos_sample/
# cat not_recall_left.out >> /home/capstone/adaboost/adaboost_train/left_pos_sample/pos_info_left.txt
# cat not_recall_front.out >> /home/capstone/adaboost/adaboost_train/front_pos_sample/pos_info_front.txt
# cat not_recall_right.out >> /home/capstone/adaboost/adaboost_train/right_pos_sample/pos_info_right.txt

# cp negative_left_dataset/* /home/capstone/adaboost/adaboost_train/lbp_neg_left/
# cp negative_front_dataset/* /home/capstone/adaboost/adaboost_train/lbp_neg_front/
# cp negative_right_dataset/* /home/capstone/adaboost/adaboost_train/lbp_neg_right/

cat negative_left_file.out >> /home/capstone/adaboost/adaboost_train/neg_list_left.txt
cat negative_front_file.out >> /home/capstone/adaboost/adaboost_train/neg_list_front.txt
cat negative_right_file.out >> /home/capstone/adaboost/adaboost_train/neg_list_right.txt
# cd /home/capstone/adaboost/adaboost_train/


# cd /home/capstone/adaboost/adaboost_train/
# ./create_left_postive_vec.sh
# ./create_front_postive_vec.sh
# ./create_right_postive_vec.sh
#  tar zcvf vec.tar.gz left_pos_example.vec front_pos_example.vec right_pos_example.vec
 scp -i /home/capstone/adaboost/sjtu2.pem -rC neg_list_left.txt  neg_list_front.txt neg_list_right.txt ubuntu@ec2-54-249-19-134.ap-northeast-1.compute.amazonaws.com:~/