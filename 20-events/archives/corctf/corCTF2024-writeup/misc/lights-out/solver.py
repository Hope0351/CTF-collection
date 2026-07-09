import math
import pyperclip

# Taken from lights_out.py
def create_vector_representations(n: int) -> list[list[int]]:
    """
    Create vector representations for each position on the n x n board.

    Args:
        n (int): The size of the board (n x n).

    Returns:
        list[list[int]]: A list of vectors representing the effect of
                           toggling each light.
    """
    vectors = []
    for i in range(n * n):
        vector = [0] * (n * n)
        vector[i] = 1
        if i % n != 0:
            vector[i - 1] = 1  # left
        if i % n != n - 1:
            vector[i + 1] = 1  # right
        if i >= n:
            vector[i - n] = 1  # up
        if i < n * (n - 1):
            vector[i + n] = 1  # down
        vectors.append(vector)
    return vectors

def create_augmented_matrix(vectors: list[list[int]],
                            board: list[int]) -> list[list[int]]:
    """
    Create an augmented matrix from the vectors and board state.

    Args:
        vectors (list[list[int]]): The vector representations.
        board (list[int]): The current state of the board.

    Returns:
        list[list[int]]: The augmented matrix.
    """
    matrix = [vec + [board[i]] for i, vec in enumerate(vectors)]
    return matrix

def gauss_jordan_elimination(matrix: list[list[int]]) -> list[list[int]]:
    """
    Perform Gauss-Jordan elimination on the given matrix to produce its
    Reduced Row Echelon Form (RREF).

    Args:
        matrix (list[list[int]]): The matrix to be reduced.

    Returns:
        list[list[int]]: The matrix in RREF.
    """
    rows, cols = len(matrix), len(matrix[0])
    r = 0
    for c in range(cols - 1):
        if r >= rows:
            break
        pivot = None
        for i in range(r, rows):
            if matrix[i][c] == 1:
                pivot = i
                break
        if pivot is None:
            continue
        if r != pivot:
            matrix[r], matrix[pivot] = matrix[pivot], matrix[r]
        for i in range(rows):
            if i != r and matrix[i][c] == 1:
                for j in range(cols):
                    matrix[i][j] ^= matrix[r][j]
        r += 1
    return matrix

def is_solvable(matrix: list[list[int]]) -> bool:
    """
    Check if the given augmented matrix represents a solvable system.

    Args:
        matrix (list[list[int]]): The augmented matrix.

    Returns:
        bool: True if the system is solvable, False otherwise.
    """
    rref = gauss_jordan_elimination(matrix)
    for row in rref:
        if row[-1] == 1 and all(val == 0 for val in row[:-1]):
            return False
    return True

def get_solution(board: list[int], n: int) -> list[int] | None:
    """
    Get a solution for the Lights Out board if it exists.

    Args:
        board (list[int]): The current state of the board.
        n (int): The size of the board (n x n).

    Returns:
        list[int] | None: A list representing the solution, or None
                            if no solution exists.
    """
    vectors = create_vector_representations(n)
    matrix = create_augmented_matrix(vectors, board)
    if not is_solvable(matrix):
        return None
    rref_matrix = gauss_jordan_elimination(matrix)
    # DEBUG
    # x = [row[-1] for row in rref_matrix[:n * n]]
    # xx = ""
    # for i in x:
    #     xx += "#" if i else "."
    # print(xx)
    # END DEBUG
    return [row[-1] for row in rref_matrix[:n * n]]

# Read board from file
board = []
n_squared = 0
with open("board.txt", "r") as f:
    for line in f:
        for c in line:
            if c == "#":
                board.append(1)
                n_squared += 1
            elif c == ".":
                board.append(0)
                n_squared += 1

# Get the solution and print in the correct format
numerical_solution = get_solution(board, int(math.sqrt(n_squared)))
user_answer_array = ["#" if n == 1 else "." for n in numerical_solution]
user_answer = "".join(user_answer_array)
#print(user_answer)
pyperclip.copy(user_answer)
