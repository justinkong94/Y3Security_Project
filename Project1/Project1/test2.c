//Test Brancing
#include <stdio.h>
#include <stdbool.h>

#define TOTALAMOUNTOFALPHABETS 26
#define MAXARRAYLENGTH 10000
#define TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH 8

#define MONOALPHABETICKEY 6
#define TRANSPOSITIONKEY 4
#define PRODUCTKEY 5

int alphabetLinkArray[TOTALAMOUNTOFALPHABETS] = { 0 };
int numberLinkArray[10] = { 0 };

char transpositionCharArray[MAXARRAYLENGTH][TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH];
int transpositionArrayColumnSequence[TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH] = { 0 };

// C++ Method
// ifstream fileInputStream; //CHANGE
// ofstream fileOutputStream; //CHANGE

FILE *fileInputStream,*fileOutputStream;

void PrintingFunction(string outputString, int methodType)
{
	//print output cipherText to file
	if (fileOutputStream.is_open())
	{
		switch (methodType)
		{
		case 1:
			fileOutputStream << "Monoalphabetic Substitution CipherText:\n" + outputString + "\n\n\n";
			break;
		case 2:
			fileOutputStream << "Transposition CipherText:\n" + outputString + "\n\n\n";
			break;
		case 3:
			fileOutputStream << "Product CipherText:\n" + outputString + "\n\n\n";
			break;
		case 4:
			fileOutputStream << "Decrypted Monoalphabetic Text:\n" + outputString + "\n\n\n";
			break;
		default:
			break;
		}
	}
}

string MonoalphabeticSubstitution(string completeInputText, int key, bool isProductCipher)
{
	int tempInt = 0;

	string monoAlphaSubOutputText = "";
	char tempChar;
	int charToInt = 0;
	bool isNumber = false;

	for (int i = 0; i < TOTALAMOUNTOFALPHABETS; i++)
	{
		tempInt = i + key + 65;

		if (tempInt > 90)
		{
			tempInt -= TOTALAMOUNTOFALPHABETS;
			alphabetLinkArray[i] = tempInt;
		}
		else
		{
			alphabetLinkArray[i] = tempInt;
		}
	}

	for (int j = 0; j < 10; j++)
	{
		tempInt = j + key + 48;

		if (tempInt > 57)
		{
			tempInt -= 10;
			numberLinkArray[j] = tempInt;
		}
		else
		{
			numberLinkArray[j] = tempInt;
		}
	}


	//substitution
	for (int i = 0; i < completeInputText.size(); i++)
	{
		tempChar = completeInputText[i];

		charToInt = tempChar;

		//capital alphabets
		if (charToInt >= 65 && charToInt <= 90)
		{
			charToInt -= 65;
		}
		else if (charToInt >= 97 && charToInt <= 122) //lowercase alphabets
		{
			charToInt -= 97;
		}
		else if (charToInt >= 48 && charToInt <= 57) //numbers 0-9 characters
		{
			isNumber = true;
			charToInt -= 48;
		}
		else if (charToInt == 32) //empty space
		{
			charToInt = -1; //set to -1
		}
		else
		{
			cout << "Error: unknown input: " + charToInt;
		}

		//character is not empty space
		if (isNumber == true)
		{
			isNumber = false;

			monoAlphaSubOutputText += (char)(numberLinkArray[charToInt]);
		}
		else if (charToInt >= 0)
		{
			monoAlphaSubOutputText += (char)(alphabetLinkArray[charToInt]);
		}
		else //character is empty space , charToInt is -1
		{
			monoAlphaSubOutputText += " ";
		}
	}

	if (isProductCipher == false)
	{
		PrintingFunction(monoAlphaSubOutputText, 1);

		monoalphaSubsCipherText = monoAlphaSubOutputText;

		return "";
	}
	else
	{
		return monoAlphaSubOutputText;
	}

}

string TranspositionCipher(string inputText, int key, bool isProductCipher)
{
	char tempTranspositionChar;

	int tranpositionArrayBlockCounter = 0;
	int columnPositionTempInt = 0;
	int transpositionArrayMaxVertical = 0;

	int transpositionVerticalCounter = 0;
	string transpositionOutputText = "";

	for (int i = 0; i < inputText.size(); i++)
	{
		tempTranspositionChar = inputText[i];

		if (tempTranspositionChar != ' ')
		{
			transpositionCharArray[transpositionArrayMaxVertical][tranpositionArrayBlockCounter] = tempTranspositionChar;

			if (tranpositionArrayBlockCounter < TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH - 1)
			{
				tranpositionArrayBlockCounter++;
			}
			else
			{
				transpositionArrayMaxVertical++;
				tranpositionArrayBlockCounter = 0;
			}
		}
	}

	for (int j = 0; j < TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH; j++)
	{
		columnPositionTempInt = j + key;

		if (columnPositionTempInt > TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH - 1)
		{
			columnPositionTempInt -= TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH;

			transpositionArrayColumnSequence[j] = columnPositionTempInt;
		}
		else
		{
			transpositionArrayColumnSequence[j] = columnPositionTempInt;
		}
	}

	//tranposition
	tranpositionArrayBlockCounter = 0;

	while (tranpositionArrayBlockCounter < TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH)
	{
		if (transpositionCharArray[transpositionVerticalCounter][transpositionArrayColumnSequence[tranpositionArrayBlockCounter]] != '\0')
		{
			transpositionOutputText += transpositionCharArray[transpositionVerticalCounter][transpositionArrayColumnSequence[tranpositionArrayBlockCounter]];

			transpositionVerticalCounter++;
		}
		else
		{
			transpositionVerticalCounter = 0;
			tranpositionArrayBlockCounter++;
		}
	}

	if (isProductCipher == false)
	{

		PrintingFunction(transpositionOutputText, 2);

		transpositionCipherText = transpositionOutputText;

		return "";
	}
	else
	{
		return transpositionOutputText;
	}
}

void ProductCipher(string completeInputText, int key)
{
	string outputCipherText = "";

	//reset arrays
	for (int i = 0; i < TOTALAMOUNTOFALPHABETS; i++)
	{
		alphabetLinkArray[i] = 0;
	}

	for (int j = 0; j < 10; j++)
	{
		numberLinkArray[j] = 0;
	}

	for (int k = 0; k < TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH; k++)
	{
		transpositionArrayColumnSequence[k] = 0;
	}

	outputCipherText = MonoalphabeticSubstitution(completeInputText, key, true);

	outputCipherText = TranspositionCipher(outputCipherText, key, true);

	PrintingFunction(outputCipherText, 3);

	productCipherText = outputCipherText;
}

void monoAlphabeticDecrypt()
{
	string tempString = "";
	int charIntValue = 0;
	bool isNumber = false;

	int wordsEightLengthCounter = 0;
	bool doWordsMatchComputerAndSecurity = true;
	bool isDecryptionFound = false;

	int decryptTable[TOTALAMOUNTOFALPHABETS] = { 0 };
	int decryptNumberTable[10] = { 0 };
	int decryptKey = 0;

	int decryptAlphabetValue = 0;
	char tempDecryptChar;
	int decryptCharToInt = 0;

	string decryptOutputText = "";

	//substitution
	for (int i = 0; i < monoalphaSubsCipherText.size(); i++)
	{
		if (monoalphaSubsCipherText[i] != ' ')
		{
			tempString += monoalphaSubsCipherText[i];
		}
		else
		{
			if (tempString.length() == 8)
			{
				for (int j = 0; j < 8; j++)
				{
					wordsWithEightLength[wordsEightLengthCounter][j] = tempString[j];
				}

				cout << "8 letter words: " + tempString + "\n";

				wordsEightLengthCounter++;
			}

			tempString = "";
		}
	}

	//find computer and security words, which helps find the key
	for (int i = 0; i < wordsEightLengthCounter; i++)
	{
		for (int j = 0; j < wordsEightLengthCounter; j++)
		{
			//prevent comparing similar words
			if (i != j && isDecryptionFound == false)
			{
				//check for the letter C comparison
				if (wordsWithEightLength[i][0] != wordsWithEightLength[j][2])
				{
					doWordsMatchComputerAndSecurity = false;
				}
				//check for the letter U comparison
				if (wordsWithEightLength[i][4] != wordsWithEightLength[j][3])
				{
					doWordsMatchComputerAndSecurity = false;
				}
				//check for the letter T comparison
				if (wordsWithEightLength[i][5] != wordsWithEightLength[j][6])
				{
					doWordsMatchComputerAndSecurity = false;
				}
				//check for the letter E comparison
				if (wordsWithEightLength[i][6] != wordsWithEightLength[j][1])
				{
					doWordsMatchComputerAndSecurity = false;
				}
				//check for the letter R comparison
				if (wordsWithEightLength[i][7] != wordsWithEightLength[j][4])
				{
					doWordsMatchComputerAndSecurity = false;
				}


				if (doWordsMatchComputerAndSecurity == true)
				{
					decryptTable[2] = wordsWithEightLength[i][0] - 65; //letter C linked
					decryptTable[4] = wordsWithEightLength[i][6] - 65; //letter E linked
					decryptTable[17] = wordsWithEightLength[i][7] - 65; //letter R linked
					decryptTable[19] = wordsWithEightLength[i][5] - 65; //letter T linked
					decryptTable[20] = wordsWithEightLength[i][4] - 65; //letter U linked

					decryptKey = decryptTable[2] - 2;

					cout << "decrypt monoalphabetic substitution key answer: " + to_string(decryptKey) + "\n";

					for (int k = 0; k < TOTALAMOUNTOFALPHABETS; k++)
					{
						decryptAlphabetValue = k - decryptKey;

						if (decryptAlphabetValue < 0)
						{
							decryptAlphabetValue += 26;
						}

						decryptAlphabetValue += 65;

						decryptTable[k] = decryptAlphabetValue;
					}

					for (int k = 0; k < 10; k++)
					{
						decryptAlphabetValue = k - decryptKey;

						if (decryptAlphabetValue < 0)
						{
							decryptAlphabetValue += 10;
						}

						decryptAlphabetValue += 48;

						decryptNumberTable[k] = decryptAlphabetValue;
					}

					isDecryptionFound = true;
				}
				else //doWordsMatchComputerAndSecurity == false, not matching, reset bool
				{
					doWordsMatchComputerAndSecurity = true;
				}
			}
		}
	}

	//get plaintext
	for (int i = 0; i < monoalphaSubsCipherText.size(); i++)
	{
		tempDecryptChar = monoalphaSubsCipherText[i];

		decryptCharToInt = tempDecryptChar;

		//capital alphabets
		if (decryptCharToInt >= 65 && decryptCharToInt <= 90)
		{
			decryptCharToInt -= 65;
		}
		else if (decryptCharToInt >= 97 && decryptCharToInt <= 122) //lowercase alphabets
		{
			decryptCharToInt -= 97;
		}
		else if (decryptCharToInt >= 48 && decryptCharToInt <= 57) //numbers 0-9 characters
		{
			isNumber = true;
			decryptCharToInt -= 48;
		}
		else if (decryptCharToInt == 32) //empty space
		{
			decryptCharToInt = -1; //set to -1
		}
		else
		{
			cout << "Error: unknown input: " + decryptCharToInt;
		}

		//character is not empty space
		if (isNumber == true)
		{
			isNumber = false;

			decryptOutputText += (char)(decryptNumberTable[decryptCharToInt]);
		}
		else if (decryptCharToInt >= 0)
		{
			decryptOutputText += (char)(decryptTable[decryptCharToInt]);
		}
		else //character is empty space , charToInt is -1
		{
			decryptOutputText += " ";
		}
	}

	PrintingFunction(decryptOutputText, 4);
}

int main(int argc, char * argv[])
{
	//string does not work
	string completeInputText = "";
	string tempLine = "";

	// fileInputStream.open("TextInput.txt");
	// fileOutputStream.open("CipherText.txt");
	fileInputStream("TextInput.txt","r");
	fileOutputStream("cipherText.txt","w");


	if (fileInputStream.is_open())
	{
		//getline does not work
		while (getline(fileInputStream, tempLine))
		{
			completeInputText += tempLine + " ";
		}
	}

	MonoalphabeticSubstitution(completeInputText, MONOALPHABETICKEY, false);

	TranspositionCipher(completeInputText, TRANSPOSITIONKEY, false);

	ProductCipher(completeInputText, PRODUCTKEY);

	//printf and getchar does not work
	printf("Program has finished running. Press enter to continue.");
	getchar();
}
