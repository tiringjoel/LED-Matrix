# -*- coding: utf-8 -*-
"""
Created on Mon Feb 17 11:50:14 2020

@author: Joel
"""

import pygame
from grid import Grid
import time
import threading
# import GUI_Listbox_support

def initScreen():
    global grid,screen,rectsize
    pygame.init()
    grid = Grid(8,16)
    rectsize = 25
    size = width, height = grid.getNrCols()*rectsize, grid.getNrRows()*rectsize
    screen = pygame.display.set_mode(size)
    
def draw():
    for row in range(grid.getNrRows()):
        for col in range(grid.getNrCols()):
            if grid.getCell(row,col) == 0:
                color = (255,255,255)
            else:
                color = (255,0,0)
            pygame.draw.rect(screen,color,(col*rectsize,row*rectsize,rectsize,rectsize))
            pygame.draw.rect(screen,(0,0,0),(col*rectsize,row*rectsize,rectsize,rectsize),1)
    pygame.display.flip()

def mousePressed(pos):
    mouseX = int(pos[0]/rectsize)
    mouseY = int(pos[1]/rectsize)
    grid.invertCell(mouseY,mouseX)

def init():
    global pygameRunning
    pygameRunning = True
    initScreen()
    draw()
    
def IsPygameRunning():
    global pygameRunning
    return pygameRunning

def closePygame():
    print("Closing Pygame...")
    global pygameRunning
    pygameRunning = False
    pygame.quit()  
    print("Pygame Closed")

def main():
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            print("Close Request from Pygame")
            closePygame()             # DOES NOT WORK!!!
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_RIGHT:
                grid.moveRight()
            if event.key == pygame.K_LEFT:
                grid.moveLeft()
            if event.key == pygame.K_UP:
                grid.moveUp()
            if event.key == pygame.K_DOWN:
                grid.moveDown()
            if event.key == pygame.K_SPACE:
                grid.wipeLeft()
                    
        if event.type == pygame.MOUSEBUTTONDOWN:
            pos = pygame.mouse.get_pos()
            mousePressed(pos)
    draw()
            
        

        
    