import sqlite3
import os

class aflw_db(object):
    '''
    classdocs
    '''

    def __init__(self,db_path):
      self.conn = sqlite3.connect(db_path)
      self.cursor = self.conn.cursor()

    def QueryByName(self, imgname):
        #return face_id, x, y, w, h
        cursor = self.cursor
        cursor.execute("SELECT face_id FROM Faces WHERE file_id=?", (imgname,))
        facelist = []
        tmp = cursor.fetchone()
        while tmp != None:
            facelist.append(tmp)
            tmp = cursor.fetchone()
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
            return result
        return [-1,-1,-1,-1,-1,-1]

    def ScanLeft(self, xpath):
        left_pos = open('pos_info_left.txt', 'a')
        for i, imgname in enumerate(os.listdir(xpath)):
#            if i > 20 :
#                break
            imgfile = os.path.join(xpath, imgname)
            [face_id, face_x, face_y, face_w, face_h, face_angle] = self.QueryByName(imgname)
            if face_x > 0 and face_y > 0 and face_angle > 0.5:
                s = "%s%s %d %d %d %d %d\n" % (xpath, imgname, 1, face_x, face_y, face_w, face_h)
                left_pos.write(s)

    def ScanFront(self, xpath):
        front_pos = open('pos_info_front.txt', 'a')
        for i, imgname in enumerate(os.listdir(xpath)):
#            if i > 20 :
#                break
            imgfile = os.path.join(xpath, imgname)
            [face_id, face_x, face_y, face_w, face_h, face_angle] = self.QueryByName(imgname)
            if face_x > 0 and face_y > 0 and face_angle > -0.5 and face_angle < 0.5:
                s = "%s%s %d %d %d %d %d\n" % (xpath, imgname, 1, face_x, face_y, face_w, face_h)
                front_pos.write(s)

    def ScanRight(self, xpath):
        right_pos = open('pos_info_right.txt', 'a')
        for i, imgname in enumerate(os.listdir(xpath)):
#            if i > 20 :
#                break
            imgfile = os.path.join(xpath, imgname)
            [face_id, face_x, face_y, face_w, face_h, face_angle] = self.QueryByName(imgname)
            if face_x > 0 and face_y > 0 and face_angle < -0.5:
                s = "%s%s %d %d %d %d %d\n" % (xpath, imgname, 1, face_x, face_y, face_w, face_h)
                right_pos.write(s)

if __name__ == "__main__":
    db_path = "/home/ubuntu/aflw/data/aflw.sqlite"
    db = aflw_db(db_path)
    db.ScanLeft("/home/ubuntu/aflw/data/flickr/0/")
    db.ScanLeft("/home/ubuntu/aflw/data/flickr/2/")
    db.ScanLeft("/home/ubuntu/aflw/data/flickr/3/")
    db.ScanFront("/home/ubuntu/aflw/data/flickr/0/")
    db.ScanFront("/home/ubuntu/aflw/data/flickr/2/")
    db.ScanFront("/home/ubuntu/aflw/data/flickr/3/")
    db.ScanRight("/home/ubuntu/aflw/data/flickr/0/")
    db.ScanRight("/home/ubuntu/aflw/data/flickr/2/")
    db.ScanRight("/home/ubuntu/aflw/data/flickr/3/")
