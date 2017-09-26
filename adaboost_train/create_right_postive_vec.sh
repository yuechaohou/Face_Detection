#!/bin/bash

output_name="right_pos_example.vec"
width=32
height=32
list_file="right_pos_sample/pos_info_right.txt"
num=23075

opencv_createsamples  -vec $output_name -info $list_file -num $num  -w $width -h $height -maxxangle 0.1 -maxyangle 0.1 -maxzangle 0.1




