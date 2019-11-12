#include <iostream>
#include <string>
#define DEBUG

using namespace std;

void fillArrayWithFalse(bool array[10][10], const int SIZE);
int askLetter();
int askRow();
int askLength();
bool askBool(string str);
void placeShip(bool array[10][10], bool isHorizontal, int length, const int columnNumber, const int rowNumber);
bool checkPosition(bool array[10][10], bool isHorizontal, int length, const int columnNumber, const int rowNumber);
void printArray(bool array[10][10], const int SIZE);
bool counterShips(int const length);
void restartGame(bool array[10][10]);

int shipCounter1 = 0;
int shipCounter2 = 0;
int shipCounter3 = 0;
int shipCounter4 = 0;
int chooseMethod;

int main()
{
	int shipCounter;
	const int SIZE = 10;
	bool array[10][10];
	fillArrayWithFalse(array, SIZE);
	printf("You can place up to 10 ships\nOne 4-blocks length\nTwo 3-blocks length\nThree 2-blocks length\nFour 1-block length\n");
	for (;;) {
		for (;;)
		{
			int columnNumber = askLetter();
			int rowNumber = askRow();
			int length = askLength();
			bool counterLimit = counterShips(length);

			if (!counterLimit)
				continue;

			bool isHorizontal;
			if (length != 1)
				isHorizontal = askBool("Placed horizontally? 1 for yes and 0 for no");
			else
				isHorizontal = true;

			bool position = checkPosition(array, isHorizontal, length, columnNumber, rowNumber);	

			if (position)
			{
				placeShip(array, isHorizontal, length, columnNumber, rowNumber);
				break;
			}
			else
				cout << "Invalid placement" << endl;
		}
		printArray(array, SIZE);
		shipCounter = shipCounter1 + shipCounter2 + shipCounter3 + shipCounter4;
		if (shipCounter == 10)
		{
			cout << "You placed all ships" << endl;
			bool answer = askBool("Do you want to replace them? 1 for Yes and 0 for No");

			if (!answer)
				return 0;
			else
			{
				restartGame(array);
			}
		}
		else
		{
			bool answer = askBool("Do you want to place more ships? 1 for Yes and 0 for No");
			if (!answer)
				return 0;
		}
	}
}

void fillArrayWithFalse(bool array[10][10], const int SIZE)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			array[i][j] = false;
		}
	}
}

int askLetter()
{
	cout << "Enter column letter" << endl;
	char letter;
	for (;;)
	{
		cin >> letter;

		if (cin.fail())
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Invalid input!" << endl;
		}
		else
		{
			if (!isalpha(letter))
				cout << "Invalid input!" << endl;
			else
			{
				letter = tolower(letter);
				int result = (int)letter - (int)'a';

				if (result > -1 && result < 10)
					return result;
				else
				{
					cout << "Invalid input!" << endl;
				}
			}
		}
	}

}

int askRow()
{
	cout << "Enter row number from 1 to 10" << endl;
	int result;
	for (;;)
	{
		cin >> result;

		if (cin.fail())
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Invalid input" << endl;
		}
		else if (result > 0 && result < 11)
			return result - 1;
		else
			cout << "Invalid input!" << endl;
	}
}

int askLength()
{
	cout << "Enter length from 1 to 4" << endl;
	int result;
	for (;;)
	{
		cin >> result;

		if (cin.fail())
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Invalid input" << endl;
		}
		else if (result > 0 && result < 5)
			return result;
		else
			cout << "Invalid input! Length can be from 1 to 4" << endl;
	}
}

bool askBool(string str)
{
	cout << str << endl;
	bool result;

	for (;;)
	{
		cin >> result;

		if (cin.fail())
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "Invalid input!" << endl;
		}
		else
			return result;
	}
}

bool checkPosition(bool array[10][10], bool isHorizontal, int length, const int columnNumber, const int rowNumber)
{
	length -= 1;
	if (isHorizontal && columnNumber + length < 10)
	{
		for (int i = 0; i <= length; i++)
		{
			if (array[rowNumber][columnNumber + i] != false)
				return false;
		}
		chooseMethod = 1;
		return true;
	}
	else if (!isHorizontal && rowNumber + length < 10)
	{
		for (int i = 0; i < length; i++)
		{
			if (array[rowNumber + i][columnNumber] != false)
				return false;
		}
		chooseMethod = 2;
		return true;
	}
	else if (isHorizontal && columnNumber - length > -1)
	{
		for (int i = 0; i < length; i++)
		{
			if (array[rowNumber][columnNumber - i] != false)
				return false;
		}
		chooseMethod = 3;
		return true;
	}
	else if (!isHorizontal && rowNumber - length > -1)
	{
		for (int i = 0; i < length; i++)
		{
			if (array[rowNumber - i][columnNumber] != false)
				return false;
		}
		chooseMethod = 4;
		return true;
	}
	else
		return false;
	
}

bool counterShips(int const length)
{
	if (length == 1 && shipCounter1 < 4)
	{
		shipCounter1++;
		return true;
	}
	else if (length == 2 && shipCounter2 < 3)
	{
		shipCounter2++;
		return true;
	}
	else if (length == 3 && shipCounter3 < 2)
	{
		shipCounter3++;
		return true;
	}
	else if (length == 4 && shipCounter4 < 1)
	{
		shipCounter4++;
		return true;
	}
	else
	{
		cout << "You can't place more ships of that type!" << endl;
		return false;
	}
}

void placeShip(bool array[10][10], bool isHorizontal, int length, const int columnNumber, const int rowNumber)
{
	length -= 1;
	switch (chooseMethod)
	{
	case 1:
		for (int i = 0; i <= length; i++)
			array[rowNumber][columnNumber + i] = true;
		break;
	case 2:
		for (int i = 0; i <= length; i++)
			array[rowNumber + i][columnNumber] = true;
		break;
	case 3:
		for (int i = 0; i <= length; i++)
			array[rowNumber][columnNumber - i] = true;
		break;
	case 4:
		for (int i = 0; i <= length; i++)
			array[rowNumber - i][columnNumber] = true;
		break;
#ifdef DEBUG
	default:
		cout << "SOMETHING WRONG! I REPEAT!!! SOMETHING DOESN'T WORK!!!" << endl;
#endif // DEBUG
	}
}

void printArray(bool array[10][10], const int SIZE)
{
	string arrayOfCoords[20];

	int asciiCode = 65;
	char asciiChar = asciiCode;

	for (int i = 0; i < 10; i++)
	{
		arrayOfCoords[i] = asciiChar;
		asciiCode++;
		asciiChar = asciiCode;
	}

	asciiCode = 49;					
	asciiChar = asciiCode;			

	for (int i = 10; i < 20; i++)	
	{							
		if (i != 19)
		{
			arrayOfCoords[i] = asciiChar;
			asciiCode++;
			asciiChar = asciiCode;
		}
		else
			arrayOfCoords[i] = "10";
	}

	cout << "\t";

	for (int i = 0; i < 10; i++)
	{
		cout << arrayOfCoords[i] << "\t";
	}

	cout << "\n\n";

	int i = 10;
	for (int r = 0; r < SIZE; r++)
	{

		for (; i < 20;)
		{
			cout << arrayOfCoords[i] << "\t";
			i++;
			break;
		}

		for (int c = 0; c < SIZE; c++)
		{
			cout << array[r][c] << "\t";
		}
		cout << "\n";
	}
}

void restartGame(bool array[10][10])
{
	fillArrayWithFalse(array, 10);

	shipCounter1 = 0;
	shipCounter2 = 0;
	shipCounter3 = 0;
	shipCounter4 = 0;
}