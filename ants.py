import numpy as np
import math as mt
import random

class ant:
	def __init__(self, position, loaded):
		self.position = position
		self.loaded = loaded

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
