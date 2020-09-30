/*Matrix*/

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


int main()
{ 
	const int SIZE = 3;
	int matrix[SIZE][SIZE];

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			cin >> matrix[i][j];
			system("cls");
			switch (i)
			{
			case (1):
				cout << matrix[0][0] << "|";
				cout << matrix[0][1] << "|";
				cout << matrix[0][2] << "|" << endl;
				for (int x = 0; x <= j; x++)
				{
					if (x == SIZE - 1)
					{
						cout << matrix[i][x] << "|" << endl;
					}
					else
					{
						cout << matrix[i][x] << "|";
					}
				}
				break;
			case (2):
				cout << matrix[0][0] << "|";
				cout << matrix[0][1] << "|";
				cout << matrix[0][2] << "|" << endl;
				cout << matrix[1][0] << "|";
				cout << matrix[1][1] << "|";
				cout << matrix[1][2] << "|" << endl;
				for (int x = 0; x <= j; x++)
				{
					if (x == SIZE - 1)
					{
						cout << matrix[i][x] << "|" << endl;
					}
					else
					{
						cout << matrix[i][x] << "|";
					}
				}
				break;
			default:
				for (int x = 0; x <= j; x++)
				{
					if (x == SIZE-1)
					{
						cout << matrix[i][x] << "|" << endl;
					}
					else
					{
						cout << matrix[i][x] << "|";
					}
				}
				break;
			}
		}
	}
	
	int matrixResult = (matrix[0][0] * matrix[1][1] * matrix[2][2]) +
		(matrix[0][1] * matrix[1][2] * matrix[2][0]) +
		(matrix[0][2] * matrix[1][0] * matrix[2][1]) -
		(matrix[0][2] * matrix[1][1] * matrix[2][0]) -
		(matrix[0][1] * matrix[1][0] * matrix[2][2]) -
		(matrix[0][0] * matrix[1][2] * matrix[2][1]);

	cout << endl << "Matrix result is " << matrixResult;
	
	return 0;
}