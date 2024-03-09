#include <iostream>
#include <vector>
#include <queue>
#include <unistd.h>
#include <fstream>
#include <sstream>

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
		GameOfLife(void)
		{
			rows = 0;
			cols = 0;
		}

		void initBoard(int argc, char **argv)
		{
			if (argc == 1)
			{
				std::cout << " * Enter the rows and cols *\n";
				std::cout << "\trows: ";
				std::cin >> rows;
				std::cout << "\tcols: ";
				std::cin >> cols;
				std::cout << "\t* Enter the Board N by M *\n";
				board.resize(rows, std::vector<bool>(cols, false));
				char tmp;
				for (int i = 0 ; i < rows ; ++i)
				{
					for (int j = 0 ; j < cols ; ++j)
					{
						std::cin >> tmp;
						board[i][j] = (bool)(tmp - '0');
					}
				}
			}
			else if (argc == 2)
			{
				std::ifstream file(argv[1]); // 파일을 열기 위한 ifstream 객체 생성
				if (file.is_open())
				{
					std::string line;
					if (std::getline(file, line)) // 파일에서 한 줄 읽기
					{
						std::istringstream iss(line);
						if (!(iss >> rows >> cols)) // 읽은 줄에서 N과 M을 추출
						{
							std::cerr << "Error: File format is incorrect.\n";
							exit(1);
						}
						board.resize(rows, std::vector<bool>(cols, false));
						for (int i = 0; i < rows; ++i)
						{
							if (!std::getline(file, line))
							{
								std::cerr << "Error: Unexpected end of file or format error.\n";
								exit(1);
							}
							for (int j = 0; j < cols; ++j)
								if (j < line.length())
									board[i][j] = (line[j] == '1');
						}	
					}
					file.close();
				}
				else
				{
					std::cerr << "Error: Could not open file " << argv[1] << "\n";
					exit(1);
				}
			}
			else
			{
				std::cerr << "Error: Too many arguments.\n";
				exit(1);
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
				usleep(200000);
			}
		}
};

int	main(int argc, char **argv)
{
	GameOfLife game;
	game.initBoard(argc, argv);
	game.runGame();

	return (0);
}
