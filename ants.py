import numpy as np
import math as mt
import random

class ant:
	def __init__(self, position, loaded):
		self.position = position
		self.loaded = loaded

def generate_board(size):
	return np.array([[0 for x in range(size)] for y in range(size)])

def populate_board(board, n_dead_ants):
	board_size = board.size()
	dead_ants_positions = random.sample(range(board_size), n_dead_ants)
	dead_ants_coord = []
	for i in dead_ants_positions:
		