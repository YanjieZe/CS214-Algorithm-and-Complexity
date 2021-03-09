"""
Author: Yanjie Ze
Date: Mar 09, 2021
Platform: macOS Big Sur
"""
import sys

if sys.version_info.major == 2:
    from Tkinter import *
elif sys.version_info.major == 3:
    from tkinter import *

class MyCanvas(Canvas):
    def __init__(self, master, hLineWidth=1, vLineWidth=1, radius=2, **kwargs):
        Canvas.__init__(self, master, kwargs)
        self.hLineWidth = hLineWidth
        self.vLineWidth = vLineWidth
        self.radius = radius

    def create_segment_h(self, x, y, l):
        self.create_line(x, y, x + l, y, width=self.hLineWidth)
        self.create_oval(x - self.radius, y - self.radius, x + self.radius, y + self.radius, fill='black')
        self.create_oval(x + l - self.radius, y - self.radius, x + l - self.radius, y + self.radius, fill='black')

    def create_segment_v(self, x, y, l):
        self.create_line(x, y, x, y + l, width=self.vLineWidth)
        self.create_oval(x - self.radius, y - self.radius, x + self.radius, y + self.radius, fill='black')
        self.create_oval(x - self.radius, y + l - self.radius, x + self.radius, y + l + self.radius, fill='black')

    def create_line_h(self, x, y, l):
        self.create_line(x, y, x + l, y, width=self.hLineWidth)

    def create_line_v(self, x, y, l):
        self.create_line(x, y, x, y + l, width=self.vLineWidth)

class TranspositionNetwork:
    def __init__(self, n, canvas_pen, width, height):
        self.size = n
        self.width = width
        self.height = height
        self.hMargin, self.vMargin = self.width// 20, self.height // 20
        self.vertical_gap = (self.height - self.vMargin*2)//(self.size-1)
        # print(self.vertical_gap)
        self.horizontal_gap = (self.width - self.hMargin*2)//(self.size-1)
        self.horizontal_length = self.width - self.hMargin*2
        if not isinstance(canvas_pen, MyCanvas):
            raise Exception("Type Error: Not MyCanvas Class")


    def draw_hline(self, cvs):
        for i in range(n):
            cvs.create_line_h(self.hMargin, self.vMargin+i*self.vertical_gap, self.horizontal_length)
    
    def draw_vline(self, cvs, line_no):# line_no from 1 to n-1
        if line_no%2==1:
            vline_num = self.size-line_no
            for i in range(vline_num):
                cvs.create_segment_v(self.hMargin+(i+0.5+line_no//2)*self.horizontal_gap,self.vMargin+(line_no-1)*self.vertical_gap, self.vertical_gap)
        if line_no%2==0:
            vline_num = self.size - line_no
            for i in range(vline_num):
                cvs.create_segment_v(self.hMargin+(i+line_no//2)*self.horizontal_gap, self.vMargin+(line_no-1)*self.vertical_gap, self.vertical_gap)

    def draw_all(self, cvs):
        self.draw_hline(cvs)
        for k in range(self.size-1):
            line_no = k+1
            self.draw_vline(cvs, line_no)

if __name__=='__main__':
    
    n = int(input("Please input the number n: "))

    winW, winH = 2400 * 0.6, 1500 * 0.6
    root = Tk()
    root.title("Transposition Network of Size %d"%n)
    cvs = MyCanvas(root, bg='white', width=winW, height=winH)
    net = TranspositionNetwork(n, cvs, winW, winH)
    net.draw_all(cvs)
    cvs.pack()
    root.mainloop()