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

`./cnn_train_models/create_lmdb.sh`

`./create_meanfile.sh`

`./train3.sh`

## Run

The whole pipeline is in pipeline/pipeline.sh

