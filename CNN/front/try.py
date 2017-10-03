import os
import sys
#write all the positive sample file directory and label 1 to tmp_pos.txt
direct2='/home/capstone/adaboost/adaboost_test/new_front_positive/'
for filename in os.listdir(direct2):
	f=open('/home/capstone/cnn_train_models/train_front/tmp_pos.txt','a')
        print >>f,direct2+filename+' 1'
#write all the positive sample (got from faces which adaboost cannot recall) file directory and label 1 to tmp_pos.txt
direct='/home/capstone/adaboost/adaboost_sample/tmp/not_recall_file_front_dataset/'
for filename in os.listdir(direct):
	f=open('/home/capstone/cnn_train_models/train_front/tmp_pos.txt','a')
        print >>f,direct+filename+' 1'

#write all the negative sample file directory and label 0 to tmp_neg.txt
direct2='/home/capstone/adaboost/adaboost_test/new_front_negative/'
for filename in os.listdir(direct2):
	f=open('/home/capstone/cnn_train_models/train_front/tmp_neg.txt','a')
        print >>f,direct2+filename+' 0'
