import numpy as np
import math as mt
import random
import pygame
from pygame import gfxdraw
import sys

COLOR_red = (255,0,0)
COLOR_white = (255,255,255)
COLOR_black = (0,0,0)

class ant:
	def __init__(self, position, loaded, field_of_view, index_in_position_array):
		self.position = position
		self.loaded = loaded
		self.field_of_view = field_of_view
		self.index_in_position_array = index_in_position_array

	def pick_up_ant(self, board):
		board[self.position] = 0
		self.loaded = True

	def drop_off_ant(self, board):
		board[self.position] = -1
		self.loaded = False

	def get_field_of_view_coords(self, board):
		board_lines = board.shape[0]
		board_columns = board.shape[1]
		fov_coords = []
		for i in range(-self.field_of_view, self.field_of_view +1):
			for j in range(-self.field_of_view, self.field_of_view +1):
				fov_coords.append(((self.position[0]+i)%board_lines, (self.position[1]+j)%board_columns))
		return fov_coords

	def should_pick_up(self, board):
		fov_coords = self.get_field_of_view_coords(board)
		return random.random() <= (float(len([board[k] for k in fov_coords if board[k] == 0]))/len(fov_coords))

	def should_drop_off(self, board):
		fov_coords = self.get_field_of_view_coords(board)
		return random.random() <= (float(len([board[k] for k in fov_coords if board[k] == -1]))/len(fov_coords))

	def move(self, board, live_ants_positions):
		# |0|1|2|
		# |3|x|4|
		# |5|6|7|
		board_lines = board.shape[0]
		board_columns = board.shape[1]
		coords = {0: (-1, -1), 1: (-1, 0), 2: (-1, 1), 3: (0, -1), 4: (0, 1), 5: (1, -1), 6: (1, 0), 7: (1, 1)}
		direction = random.randint(0,7)
		new_position = ((self.position[0] + coords[direction][0])%board_lines, (self.position[1] + coords[direction][1])%board_columns)
		old_position = (self.position[0], self.position[1])
		#if not new_position in live_ants_positions:
			#live_ants_positions[live_ants_positions.index(self.position)] = new_position
		live_ants_positions[self.index_in_position_array] = new_position
		self.position = new_position
		return old_position, new_position
		

def generate_board(lines, columns):
	return np.zeros(shape=(lines, columns))

def populate_board(board, n_dead_ants):
	board_columns = board.shape[1]
	board_size = board.size
	dead_ants_positions = random.sample(range(board_size), n_dead_ants)
	dead_ants_coord = []
	for i in dead_ants_positions:	dead_ants_coord.append((i/board_columns, i%board_columns))
	for i in dead_ants_coord:	board[i]= -1

def generate_live_ants(board, fov_range, n_live_ants):
	live_ants = []
	index = 0
	for i in random.sample(range(board.size), n_live_ants):
		live_ants.append(ant((i/board.shape[1], i%board.shape[1]), False, fov_range, index))
		index += 1
	return live_ants
	#return [ant(k, False, 1) for k in [(i/board.shape[1], i%board.shape[1]) for i in random.sample(range(board.size), n_live_ants)]]

def check_closed_window():
	for event in pygame.event.get():
	  if event.type == pygame.QUIT:
	    pygame.quit(); sys.exit();


pygame.init()
screen = pygame.display.set_mode((500,500))
screen.fill(COLOR_white)

pygame.display.update()

board = generate_board(500,500)
populate_board(board, 5000)
ants = generate_live_ants(board, 3, 500)
live_ants_positions = [ant.position for ant in ants]

for i in range(500):
	for j in range(500):
		if board[i, j] == -1:
			gfxdraw.pixel(screen, i, j, COLOR_red)
		if (i, j) in live_ants_positions:
			gfxdraw.pixel(screen, i, j, COLOR_black)
			
pygame.display.update()
i=1
while True:
	check_closed_window()
	for ant in ants:
		if not ant.loaded:
			if board[ant.position] == -1 and ant.should_pick_up(board):
				ant.pick_up_ant(board)
		elif ant.loaded:
			if board[ant.position] == 0 and ant.should_drop_off(board):
				ant.drop_off_ant(board)
		
		old_position, new_position = ant.move(board, live_ants_positions)
		
		if board[old_position] == -1:
			gfxdraw.pixel(screen, old_position[0], old_position[1], COLOR_red)
		else:
			gfxdraw.pixel(screen, old_position[0], old_position[1], COLOR_white)
			
		gfxdraw.pixel(screen, new_position[0], new_position[1], COLOR_black)
		
	i += 1
	if i%1000 == 0:
		pygame.display.update()

