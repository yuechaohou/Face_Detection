#!/usr/bin/env python
"""
classify.py is an out-of-the-box image classifer callable from the command line.

By default it configures and runs the Caffe reference ImageNet model.
"""
import numpy as np
import os
import sys
import argparse
import glob
import time
import natsort
import caffe

root='/home/capstone/cnn_train_models/train_right/'
deploy=root + 'face_deploy2.prototxt'
caffe_model='/home/capstone/cnn_train_models/model_right/face_iter_946770.caffemodel'
labels_filename = root + 'labels.txt'
mean_file=root+'face_mean.npy'

def main(argv):
    pycaffe_dir = os.path.dirname(__file__)

    parser = argparse.ArgumentParser()
    # Required arguments: input and output files.
    parser.add_argument(
        "input_file",
        help="Input image, directory, or npy."
    )
    parser.add_argument(
        "output_file",
        help="Output npy filename."
    )
    # Optional arguments.
    parser.add_argument(
        "--model_def",
        default=os.path.join(pycaffe_dir,
                deploy),
        help="Model definition file."
    )
    parser.add_argument(
        "--pretrained_model",
        default=os.path.join(pycaffe_dir,
                caffe_model),
        help="Trained model weights file."
    )
    parser.add_argument(
        "--gpu",
        action='store_true',
        help="Switch for gpu computation."
    )
    parser.add_argument(
        "--center_only",
        action='store_true',
        help="Switch for prediction from center crop alone instead of " +
             "averaging predictions across crops (default)."
    )
    parser.add_argument(
        "--images_dim",
        default='32,32',
        help="Canonical 'height,width' dimensions of input images."
    )
    parser.add_argument(
        "--mean_file",
        default=os.path.join(pycaffe_dir,
                             mean_file),
        help="Data set image mean of [Channels x Height x Width] dimensions " +
             "(numpy array). Set to '' for no mean subtraction."
    )
    parser.add_argument(
        "--input_scale",
        type=float,
        help="Multiply input features by this scale to finish preprocessing."
    )
    parser.add_argument(
        "--raw_scale",
        type=float,
        default=255.0,
        help="Multiply raw input by this scale before preprocessing."
    )
    parser.add_argument(
        "--channel_swap",
        default='2,1,0',
        help="Order to permute input channels. The default converts " +
             "RGB -> BGR since BGR is the Caffe default by way of OpenCV."
    )
    parser.add_argument(
        "--ext",
        default='jpg',
        help="Image file extension to take as input when a directory " +
             "is given as the input file."
    )
    args = parser.parse_args()
    
    image_dims = [int(s) for s in args.images_dim.split(',')]
  
    mean, channel_swap = None, None
    if args.mean_file:
        mean = np.load(args.mean_file)
    if args.channel_swap:
        channel_swap = [int(s) for s in args.channel_swap.split(',')]

    if args.gpu:
        caffe.set_mode_gpu()
        print("GPU mode")
    else:
        caffe.set_mode_cpu()
        print("CPU mode")

    # Make classifier.
    classifier = caffe.Classifier(args.model_def, args.pretrained_model,
            image_dims=image_dims, mean=mean,
            input_scale=args.input_scale, raw_scale=args.raw_scale,
            channel_swap=channel_swap)

    # Load numpy array (.npy), directory glob (*.jpg), or image file.
    args.input_file = os.path.expanduser(args.input_file)
    start2=time.time()
    if args.input_file.endswith('npy'):
        print("Loading file: %s" % args.input_file)
        inputs = np.load(args.input_file)
    elif os.path.isdir(args.input_file):
        print("Loading folder: %s" % args.input_file)
        inputs =[caffe.io.load_image(im_f)
                 for im_f in natsort.natsorted(glob.glob(args.input_file + '/*.' + args.ext))]
    else:
        print("Loading file: %s" % args.input_file)
        inputs = [caffe.io.load_image(args.input_file)]

    print("Classifying %d inputs." % len(inputs))
    print("Done in %.2f s." % (time.time() - start2))
    # Classify.
    start = time.time()
    predictions = classifier.predict(inputs, not args.center_only)
    print("Done in %.2f s." % (time.time() - start))
    start = time.time()
    labels = np.loadtxt(labels_filename, str, delimiter='\t') 
    i=0
    j=0
   # f=open('/home/capstone/pipeline/face_result_right.txt','a')
    f=open('/home/capstone/pipeline/AdaBoost_to_CNN/faces_log_right.txt','r+')
    flist=f.readlines()
    for filename in natsort.natsorted(glob.glob(args.input_file + '/*.' + args.ext)):
	#print >>f,filename
    	order=predictions[i].argsort()[-1]
	j=2*i
	#print order
	if order==1:
    		#print >>f,predictions[i][1]
		strii='_'+str(i)+'.jpg '+str(predictions[i][1])[:7]+'\n'
		flist[j]=str(args.output_file)+strii
	else:
		#print >>f,'0'
		strii='_'+str(i)+'.jpg 0\n'
		flist[j]=str(args.output_file)+strii
        i=i+1
    # Save
    #print("Saving results into %s" % args.output_file)
    #np.save(args.output_file, predictions)
    f=open('/home/capstone/pipeline/AdaBoost_to_CNN/faces_log_right.txt','w+')
    f.writelines(flist)
    print("Print in %.2f s." % (time.time() - start))
    f.close()
if __name__ == '__main__':
    main(sys.argv)
