# Deep Learning Based Face Detection

## 2016 Fall Capstone Group 8

## Problem

To detect the faces in the video or images  and frame the detected ones with detecting windows.

## Goal

 To stabilize the detecting window, increase accuracy in classification as well as maintaining a relative high recall rate. 

## Overview

* Adaboost

We used the Adaboost in OpenCV library as a pre-filter to scan the candidates

* CNN

This part we trained our CNN model inspired with Cifar-10 on Caffe  with the data from aflw database to delete the  wrong candidates

* NMS

Finally, we use NMS (Non-maximum suppression) algorithm to eliminating the wrong windows and combining the duplicate the frames into the final candidates

## Environment

* Ubuntu 14.0.4
* Caffe Platform with CUDA
* OpenCV 2.4.13

## Train

* Adaboost

`./adboost_sample/create_sample.sh`

* CNN

Training Procedure (under CNN)

1. Use test3.sh to choose some positive and negative samples as test samples, and move them to a new directory
2. Use try.py to print positive training samples list in tmp_pos.txt and negative training samples list in tmp_neg.txt
3. Based on batch size 100 and ratio between positive and negative training sample number, choose the best ratio between positive training sample and negative training sample.
4. Use create_list.cpp to create training samples list.
5. Use create_lmdb.sh to transform training sample to lmdb form
6. Use create_meanfile.sh to create meanfile
7. Change parameters in mult_solver.prototxt 
8. Change directory of training and testing samples in face_train.prototxt, face_test.prototxt
9. Run python ~/caffe/python/train_face.py to train model and plot figure.

##Testing

* Adaboost

  * parallel_fast.sh for adaboost detectmultscale() final frame size 1/5

    parallel_more.sh for adaboost detectmultscale() final frame size 1/10

  * ~/adaboost/adaboost_test/adaboost_test_front.cpp  => adaboost_test_front

    ~/adaboost/adaboost_test/adaboost_test_left.cpp   => adaboost_test_left
    ~/adaboost/adaboost_test/adaboost_test_right.cpp  => adaboost_test_right

* CNN

1. Use ~/caffe/python/convert_mean.py to convert face_mean.binaryproto to face_mean.npy
2. face_deploy.prototxt for testing batch size 1 
3. face_deploy2.prototxt for testing batch size <=500 (parallel computation of GPU)
4. run python ~/caffe/python/test_pl_front.py to test figure (see pipeline folder for test files)

## Run

The whole pipeline is in pipeline/pipeline.sh

