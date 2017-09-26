#!/usr/bin/env python 
import sqlite3
import os

mypath = "/home/capstone/adaboost/aflw/data/flickr/photo/"

class aflw_db(object):
    '''
    classdocs
    '''

    def __init__(self,db_path):
      self.conn = sqlite3.connect(db_path)
      self.cursor = self.conn.cursor()
      #mypath = "/home/capstone/adaboost/aflw/data/flickr/photo/"

    def QueryByName(self, imgname):
        #return face_id, x, y, w, h
        cursor = self.cursor
        cursor.execute("SELECT face_id FROM Faces WHERE file_id=?", (imgname,))
        facelist = []
        tmp = cursor.fetchone()
        while tmp != None:
            facelist.append(tmp)
            tmp = cursor.fetchone()
        resultlist = []
        for item in facelist:
            faceid = item[0]
            #print faceid
            cursor.execute("SELECT face_id, x, y, w, h FROM FaceRect WHERE face_id=?", (faceid,))
            #print cursor.fetchone()
            xx = cursor.fetchone()
            #print face angle
            cursor.execute("SELECT yaw FROM FacePose WHERE face_id=?", (faceid,))
            #print cursor.fetchone
            yy = cursor.fetchone()
            result = [xx[0], xx[1], xx[2], xx[3], xx[4]]
            result = result + [yy[0]]
            resultlist.append(result)
        return resultlist

    def ScanLeft(self, xpath):
	global mypath
        left_pos = open('new_pos_info_left.txt', 'a')
        for i, imgname in enumerate(os.listdir(xpath)):
#            if i > 20 :
#                break
            imgfile = os.path.join(xpath, imgname)
            resultlist = self.QueryByName(imgname)
            for item in resultlist:
                [face_id, face_x, face_y, face_w, face_h, face_angle] = item
                if face_x > 0 and face_y > 0 and face_angle > 0.5:
                    s = "%s%s %d %d %d %d %d\n" % (mypath, imgname, 1, face_x, face_y, face_w, face_h)
                    left_pos.write(s)

    def ScanFront(self, xpath):
	global mypath
        front_pos = open('new_pos_info_front.txt', 'a')
        for i, imgname in enumerate(os.listdir(xpath)):
#            if i > 20 :
#                break
            imgfile = os.path.join(xpath, imgname)
            resultlist = self.QueryByName(imgname)
            for item in resultlist:
                [face_id, face_x, face_y, face_w, face_h, face_angle] = item
                if face_x > 0 and face_y > 0 and face_angle > -0.5 and face_angle < 0.5:
                    s = "%s%s %d %d %d %d %d\n" % (mypath, imgname, 1, face_x, face_y, face_w, face_h)
                    front_pos.write(s)
           
            

    def ScanRight(self, xpath):
	global mypath
        right_pos = open('new_pos_info_right.txt', 'a')
        for i, imgname in enumerate(os.listdir(xpath)):
#            if i > 20 :
#                break
            imgfile = os.path.join(xpath, imgname)
            resultlist = self.QueryByName(imgname)
            for item in resultlist:
                [face_id, face_x, face_y, face_w, face_h, face_angle] = item
                if face_x > 0 and face_y > 0 and face_angle < -0.5:
                    s = "%s%s %d %d %d %d %d\n" % (mypath, imgname, 1, face_x, face_y, face_w, face_h)
                    right_pos.write(s)

if __name__ == "__main__":
    db_path = "/home/capstone/adaboost/aflw/data/aflw.sqlite"
    db = aflw_db(db_path)
    
    db.ScanLeft("/home/capstone/adaboost/aflw/data/new/")
    db.ScanFront("/home/capstone/adaboost/aflw/data/new/")
    #db.ScanFront("/home/capstone/adaboost/aflw/data/new/")
    #db.ScanFront("/home/capstone/adaboost/aflw/data/new/")
    db.ScanRight("/home/capstone/adaboost/aflw/data/new/") 
    #db.ScanRight("/home/capstone/adaboost/aflw/data/new/")
    #db.ScanRight("/home/capstone/adaboost/aflw/data/new/")
