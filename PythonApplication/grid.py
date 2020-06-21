
import numpy as np
import time, threading

class Grid:
    # Initializer
    def __init__(self,NrRows,NrCols):
        self.NrRows = NrRows
        self.NrCols = NrCols
        self.data = np.zeros((NrRows,NrCols), dtype=np.int8)
        self.wiperpos = 0
        self.scrollDirection = 'RIGHT'
        self.scrollingEnabled = False
        self.scrollSpeed = 0
        self.patterns = {}
        
    # Methods
    def moveRight(self):
        self.data = np.roll(self.data,1,axis=1)
    
    def moveLeft(self):
        self.data = np.roll(self.data,-1,axis=1)
    
    def moveUp(self):
        self.data = np.roll(self.data,-1,axis=0)
    
    def moveDown(self):
        self.data = np.roll(self.data,1,axis=0)
        
    def invertCell(self,x,y):
        self.data[x][y] = np.invert(self.data[x][y])
        
    def getNrRows(self):
        return np.size(self.data,0)
        
    def getNrCols(self):
        return np.size(self.data,1)
    
    def setCell(self,x,y,value):
        self.data[x][y] = value
        
    def getCell(self,x,y):
        return self.data[x][y]
    
    # def wipeLeft(self):
    #     # call in repeadatly in while loop and draw in between
    #     # at the End of while loop draw again
    #     done = False
    #     if self.wiperpos < self.NrCols:
    #         done = False
    #         self.data[:,self.wiperpos] = -1
    #         if self.wiperpos > 0:    
    #                 self.data[:,(self.wiperpos-1)] = 0
    #         self.wiperpos += 1
    #     else:
    #         self.wiperpos = 0
    #         self.data[:,-1] = 0
    #         done = True
    #     return not done
    
    def wipeLeft(self):
        def wiping():
            if self.wiperpos < self.NrCols:
                self.data[:,self.wiperpos] = -1
                if self.wiperpos > 0:    
                        self.data[:,(self.wiperpos-1)] = 0
                self.wiperpos += 1
                time.sleep(0.05)
                wiping()
            else:
                self.wiperpos = 0
                self.data[:,-1] = 0 
        self.t2 = threading.Thread(target=wiping)
        self.t2.start()
    
    def updateScroll(self):
        if self.scrollDirection == 'UP':
            self.moveUp()
        if self.scrollDirection == 'DOWN':
            self.moveDown()
        if self.scrollDirection == 'LEFT':
            self.moveLeft()
        if self.scrollDirection == 'RIGHT':
            self.moveRight()
        if self.scrollingEnabled == True:
            self.t1 = threading.Timer(self.scrollSpeed,self.updateScroll)
            self.t1.start()
    
    def enableScrolling(self):
        self.scrollingEnabled = True
        self.updateScroll()
   
    def disableScrolling(self):
        self.scrollingEnabled = False
        
    def setScrollSpeed(self, speed):
        self.scrollSpeed = speed**3
    
    def setScrollDirection(self, direction):
        if direction == 'UP':
            self.scrollDirection = 'UP'
        if direction == 'DOWN':
            self.scrollDirection = 'DOWN'
        if direction == 'LEFT':
            self.scrollDirection = 'LEFT'
        if direction == 'RIGHT':
            self.scrollDirection = 'RIGHT'
            
    def getScrollDirection(self):
        return self.scrollDirection
    
    def savePattern(self,name):
        if name not in self.patterns.keys():
            self.patterns[name] = np.copy(self.data)
            return True
        else:
            self.patterns[name] = np.copy(self.data)
            return False
        
    def loadPattern(self,name):
        if name in self.patterns.keys():
            self.data = np.copy(self.patterns[name])
            return True
        else:
            return False

if __name__ == '__main__':
    import application
    application.vp_start_gui()

