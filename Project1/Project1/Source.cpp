//the plaintext must have the words "computer" and "security" in it for the cryptanalysis to work
#include <iostream>
#include <time.h>
#include <string>
#include <sstream>
#include <fstream>



const int TOTALAMOUNTOFALPHABETS = 26;
const int MAXARRAYLENGTH = 10000;
const int TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH = 8;

const int MONOALPHABETICKEY = 6;
const int TRANSPOSITIONKEY = 4;
const int PRODUCTKEY = 5;

int alphabetLinkArray[TOTALAMOUNTOFALPHABETS] = { 0 };
int numberLinkArray[10] = { 0 };

char transpositionCharArray[MAXARRAYLENGTH][TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH];
int transpositionArrayColumnSequence[TRANSPOSITIONARRAYCHARACTERBLOCKLENGTH] = { 0 };

std::string monoalphaSubsCipherText = "";
std::string transpositionCipherText = "";
std::string productCipherText = "";

char wordsWithEightLength[MAXARRAYLENGTH][8];

std::ifstream fileInputStream;
std::ofstream fileOutputStream;
/*
void OldMonoalphabeticSubstitution()
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
*/

void PrintingFunction(std::string outputString, int methodType)
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

std::string MonoalphabeticSubstitution(std::string completeInputText, int key, bool isProductCipher)
{
	int tempInt = 0;

	std::string monoAlphaSubOutputText = "";
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
			std::cout << "Error: unknown input: " + charToInt;
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

std::string TranspositionCipher(std::string inputText, int key, bool isProductCipher)
{
	char tempTranspositionChar;

	int tranpositionArrayBlockCounter = 0;
	int columnPositionTempInt = 0;
	int transpositionArrayMaxVertical = 0;

	int transpositionVerticalCounter = 0;
	std::string transpositionOutputText = "";

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

void ProductCipher(std::string completeInputText, int key)
{
	std::string outputCipherText = "";

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
	std::string tempString = "";
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

	std::string decryptOutputText = "";

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
				
				std::cout << "8 letter words: " + tempString + "\n";

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

					std::cout << "decrypt monoalphabetic substitution key answer: " + std::to_string(decryptKey) + "\n";

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
			std::cout << "Error: unknown input: " + decryptCharToInt;
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
	std::string completeInputText = "";
	std::string tempLine = "";

	fileInputStream.open("TextInput.txt");
	fileOutputStream.open("CipherText.txt");

	if (fileInputStream.is_open())
	{
		while (std::getline(fileInputStream, tempLine))
		{
			completeInputText += tempLine + " ";
		}
	}

	MonoalphabeticSubstitution(completeInputText, MONOALPHABETICKEY, false);

	TranspositionCipher(completeInputText, TRANSPOSITIONKEY, false);

	ProductCipher(completeInputText, PRODUCTKEY);
	
	monoAlphabeticDecrypt();
	


	fileInputStream.close();
	fileOutputStream.close();

	std::cout << ("Program has finished running. Press enter to continue.");
	getchar();

	return 0;
}