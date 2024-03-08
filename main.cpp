#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>

int N, M;

class GameOfLife
{
	private:
		std::vector<std::vector<bool>> board;
		int rows, cols;

		bool isAlive(int x, int y)
		{
			if (x < 0 || x >= rows || y < 0 || y >= cols)
				return (false);
			return (board[x][y]);
		}

		int countNeighbors(int x, int y)
		{
			int count = 0;
			for (int i = -1; i <= 1; i++)
			{
				for (int j = -1; j <= 1; j++)
				{
					if (i == 0 && j == 0)
						continue;
					if (isAlive(x + i, y + j))
						count++;
				}
			}
			return (count);
		}

	public:
		GameOfLife(int r, int c) : rows(r), cols(c)
		{
			board.resize(rows, std::vector<bool>(cols, false));
		}

		void initBoard()
		{
			std::cout << "\t* Enter the Board N by M *\n";
			char tmp;
			for (int i = 0 ; i < N ; ++i)
			{
				for (int j = 0 ; j < M ; ++j)
				{
					std::cin >> tmp;
					board[i][j] = (bool)(tmp - '0');
				}
			}
		}

		void updateBoard(void)
		{
			std::vector<std::vector<bool>> newBoard = board;
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					int aliveNeighbors = countNeighbors(i, j);
					if (isAlive(i, j))
						newBoard[i][j] = aliveNeighbors == 2 || aliveNeighbors == 3;
					else
						newBoard[i][j] = aliveNeighbors == 3;
				}
			}
			board = newBoard;
		}

		void printBoard(void)
		{
			system("clear");
			for (auto &row : board)
			{
				for (bool cell : row)
					std::cout << (cell ? "██" : "░░");
				std::cout << "\n";
			}
		}

		void runGame(void)
		{
			while (true)
			{
				printBoard();
				updateBoard();
				usleep(400000);
			}
		}
};

void Input(void)
{
	std::cout << " * Enter the N(rows) and M(cols) *\n";
	std::cout << "\tN: ";
	std::cin >> N;
	std::cout << "\tM: ";
	std::cin >> M;
}

int	main(void)
{
	Input();
	GameOfLife game(N, M);
	game.initBoard();
	game.runGame();

	return (0);
}
