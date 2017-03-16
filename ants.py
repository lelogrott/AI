import numpy as np
import math as mt
import random

class ant:
	def __init__(self, position, loaded):
		self.position = position
		self.loaded = loaded

	def pick_up_ant(self, board):
		board[self.position] = 0
		self.loaded = True

	def drop_off_ant(self, board):
		board[self.position] = -1
		self.loaded = False

	def move(self, board):
		# |0|1|2|
		# |3|x|4|
		# |5|6|7|
		coords = {0: (-1, -1), 1: (-1, 0), 2: (-1, 1), 3: (0, -1), 4: (0, 1), 5: (1, -1), 6: (1, 0), 7: (1, 1)}
		direction = random.randint(0,7)
		new_position = (self.position[0] + coords[direction][0], self.position[1] + coords[direction][1])
		board[new_position] = 1
		self.position = new_position
		

def generate_board(lines, columns):
	return np.zeros(shape=(lines, columns))

def populate_board(board, n_dead_ants):
	board_columns = board.shape[1]
	board_size = board.size
	dead_ants_positions = random.sample(range(board_size), n_dead_ants)
	dead_ants_coord = []
	for i in dead_ants_positions:	dead_ants_coord.append((i/board_columns, i%board_columns))
	for i in dead_ants_coord:	board[i]= -1

def generate_live_ants(board_size, board_columns, n_live_ants):
	return [ant(k, False) for k in [(i/board_columns, i%board_columns) for i in random.sample(range(board_size), n_live_ants)]]

print [k.position for k in generate_live_ants(25, 5, 10)]
