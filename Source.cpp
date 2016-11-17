#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

const int TOTALAMOUNTOFALPHABETS = 26;
const int MAXARRAYLENGTH = 100000;
const int TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH = 8;

int alphabetLinkArray[TOTALAMOUNTOFALPHABETS] = { 0 };
char transpositionCharArray[MAXARRAYLENGTH][TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH];

ifstream fileInputStream;
ofstream fileOutputStream;

void MonoalphabeticSubstitution()
{
	int alphabetInt = 0;
	int numberOfAlphabetsAvailable = TOTALAMOUNTOFALPHABETS;

	bool isReassignmentActive = false;

	for (int i = 0; i < TOTALAMOUNTOFALPHABETS; i++)
	{
		int tempAlphabetCounter = 0;

		alphabetInt = rand() % numberOfAlphabetsAvailable;

		for (int j = 0; j < alphabetInt + 1; j++)
		{
			if (alphabetLinkArray[tempAlphabetCounter] == 0)
			{
				if (j < alphabetInt)
				{
					tempAlphabetCounter++;
				}
			}
			else
			{
				while (alphabetLinkArray[tempAlphabetCounter] != 0)
				{
					tempAlphabetCounter++;
				}

				if (j < alphabetInt)
				{
					tempAlphabetCounter++;
				}
			}
		}

		//new assigned character is similar to original character
		if (tempAlphabetCounter == i)
		{
			//reassignment happened twice in a row and is stuck, reset entire table
			if (isReassignmentActive == true)
			{
				printf("assignment is stuck, reset\n");

				isReassignmentActive = false;

				i = -1;
				numberOfAlphabetsAvailable = TOTALAMOUNTOFALPHABETS;
				alphabetInt = 0;

				for (int j = 0; j < TOTALAMOUNTOFALPHABETS; j++)
				{
					alphabetLinkArray[j] = 0;
				}
			}
			else
			{
				isReassignmentActive = true;

				printf("alphabet reshuffled\n");
				//decrement i by 1, this is to redo random assignment
				i -= 1;
			}
			
		}
		else //proceed as normal
		{
			isReassignmentActive = false;

			//assign alphabet to its corresponding cipher
			alphabetLinkArray[tempAlphabetCounter] = i + 1;

			numberOfAlphabetsAvailable--;
		}
		
	}
}

void TranspositionCipher(string inputText)
{
	char tempTranspositionChar;

	int transpositionArrayVerticalCounter = 0;
	int tranpositionArrayBlockCounter = 0;

	for (int i = 0; i < inputText.size(); i++)
	{
		tempTranspositionChar = inputText[i];

		if (tempTranspositionChar != ' ')
		{
			transpositionCharArray[transpositionArrayVerticalCounter][tranpositionArrayBlockCounter] = tempTranspositionChar;

			if (tranpositionArrayBlockCounter < TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH - 1)
			{
				tranpositionArrayBlockCounter++;
			}
			else
			{
				transpositionArrayVerticalCounter++;
				tranpositionArrayBlockCounter = 0;
			}
		}
	}
}

int main(int argc, char * argv[])
{
	string completeInputText = "";
	string outputText = "";
	string tempLine = "";

	fileInputStream.open("TextInput.txt");
	fileOutputStream.open("CipherText.txt");

	if (fileInputStream.is_open())
	{
		while (getline(fileInputStream, tempLine))
		{
			completeInputText += tempLine + " ";
		}
	}

	srand(time(NULL));

	//MonoalphabeticSubstitution();

	TranspositionCipher(completeInputText);

	char tempChar;
	int charToInt = 0;
	bool isLowercaseChar = true;

	for (int i = 0; i < completeInputText.size(); i++)
	{
		tempChar = completeInputText[i];

		charToInt = tempChar;

		//capital alphabets
		if (charToInt >= 65 && charToInt <= 90)
		{
			isLowercaseChar = false;

			charToInt -= 65;
		}
		else if (charToInt >= 97 && charToInt <= 122) //lowercase alphabets
		{
			isLowercaseChar = true;

			charToInt -= 97;
		}
		else if (charToInt >= 48 && charToInt <= 57) //numbers 0-9 characters
		{
			charToInt -= 48;
		}
		else if (charToInt == 32) //empty space
		{
			charToInt = -1; //set to -1
		}
		else
		{
			printf("Error: unknown input\n");
		}

		//character is not empty space
		if (charToInt >= 0)
		{
			if (isLowercaseChar == true)
			{
				outputText += (char)(alphabetLinkArray[charToInt] - 1 + 97);
			}
			else //isLowercaseChar == false
			{
				outputText += (char)(alphabetLinkArray[charToInt] - 1 + 65);
			}
		}
		else //character is empty space , charToInt is -1
		{
			outputText += " ";
		}	
	}

	//print output cipherText to file
	if (fileOutputStream.is_open())
	{
		fileOutputStream << outputText + "\n\nCipherKey:\n";
		cout << outputText;//testing purposes only


		for (int i = 65; i < 91; i++)
		{
			string tempOutputString = "";

			char tempOutputChar1;
			char tempOutputChar2;

			tempOutputChar1 = i;
			tempOutputChar2 = alphabetLinkArray[i - 65] - 1 + 65;

			tempOutputString += tempOutputChar1;
			tempOutputString += " -> ";
			tempOutputString += tempOutputChar2;

			fileOutputStream << tempOutputString + "\n";
		}
		
	}
	else
	{
		printf("Error opening file\n");
	}
		
	

	printf("test");
}