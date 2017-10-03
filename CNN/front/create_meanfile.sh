#!/usr/bin/env sh

EXAMPLE=/home/capstone/cnn_train_models/train_front
DATA=/home/capstone/cnn_train_models/train_front
TOOLS=/home/capstone/caffe/build/tools

$TOOLS/compute_image_mean $EXAMPLE/face_train_lmdb $DATA/face_mean.binaryproto

echo "Done."
