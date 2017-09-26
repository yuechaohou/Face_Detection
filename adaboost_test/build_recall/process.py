#!/usr/bin/env python 
import sqlite3
import sys
import os



if __name__ == "__main__":
	file=sys.argv[1]
	f = open(file, "r")  
	result=[]
	while True:  
		line = f.readline()  
		elements=[]
		if line:  
			elements=line.split("	")
			if len(elements)<2:
				continue
			else: 
				if elements[1]=='0':
					result.append(elements)
					elements[3]=int(elements[3])
		else:
			break
	result.sort(key=lambda x:x[3])
		#print elements
		#if elements[1]=='0':
		# 	print line 
	for elements in result:
		print elements[0]+' '+elements[1]+' '+elements[2]+' '+str(elements[3])+' '+elements[4]
	f.close()