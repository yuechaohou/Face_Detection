#!/bin/bash

output_mode_dir="left_profile_face_model"
vec_file="left_pos_example.vec"
neg_file="neg_list_left.txt"

pos_num=18910
neg_num=64649

w=32
h=32

stage_num=8
max_weak_count=150
min_hit_rate=0.9999
max_false_alarm_rate=0.5

precalc_val_bufsize=4000
precalc_idx_bufsize=4000
feature_type="LBP" # "HOG", "HAAR"
bt="GAB"
max_depth=1


opencv_traincascade -data $output_mode_dir -vec "$vec_file"  -bg "$neg_file" -numPos $pos_num -numNeg $neg_num  -numStages $stage_num -w $w -h $h -maxWeakCount $max_weak_count -minHitRate $min_hit_rate -maxFalseAlarmRate $max_false_alarm_rate -precalcValBufSize $precalc_idx_bufsize -precalcIdxBufSize $precalc_idx_bufsize -featureType $feature_type -bt $bt -maxDepth $max_depth
