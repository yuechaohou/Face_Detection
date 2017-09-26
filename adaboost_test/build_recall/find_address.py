#!/usr/bin/env python 
import sqlite3
import sys
import os

if __name__ == "__main__":
	file0=sys.argv[1]
	file1=sys.argv[2]
	f = open(file0, "r")  
	address_book=[]
	while True:  
		line = f.readline() 
		elements=[]
		#print line
		if line:  
			elements=line.split(" ")
			address_book.append(elements)
		else: break 
	f.close()
	f=open(file1,"r")

	result=[]
	while True:  
		line = f.readline()  
		elements=[]
		if line:  
			elements=line.split(" ")
			result.append(elements)

		else: break
	f.close()


	for elements in result:
		for address in address_book:
			



			if str(elements[0])==str(address[0]):
				s=''
				s=str(address[0])+' '+str(address[1])
				for i in range(int(address[1])):
					s+=' '+str(address[i+2])+' '+str(address[i+3])+' '+str(address[i+4])+' '+str(address[i+5]).replace('\n','')
				print s
			 	#print str(address[0])+' '+str(address[1])+' '+str(address[2])+' '+str(address[3])+' '+str(address[4])+' '+str(address[5]).replace('\n','')

