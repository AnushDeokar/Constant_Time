// C++ code to implement Hill Cipher
#include<stdio.h>
#include<math.h>
#include <stdint.h>
#include <string.h>


// Following function generates the
// key matrix for the key string
int l = l;
void getKeyMatrix(char key[], int keyMatrix[][100])
{
	int k = 0;
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
		{
			keyMatrix[i][j] = (key[k]) % 65;
			k++;
		}
	}
}

// Following function encrypts the message
void encrypt(int cipherMatrix[][1],
			int keyMatrix[][100],
			int messageVector[][1])
{
	int x, i, j;
	for (i = 0; i < l; i++)
	{
		for (j = 0; j < 1; j++)
		{
			cipherMatrix[i][j] = 0;
		
			for (x = 0; x < l; x++)
			{
				cipherMatrix[i][j] +=
					keyMatrix[i][x] * messageVector[x][j];
			}
		
			cipherMatrix[i][j] = cipherMatrix[i][j] % 26;
		}
	}
}

// Function to implement Hill Cipher
void HillCipher(char message[], char key[])
{
	// Get key matrix from the key string
	int keyMatrix[l][l];
	getKeyMatrix(key, keyMatrix);

	int messageVector[l][1];

	// Generate vector for the message
	for (int i = 0; i < l; i++)
		messageVector[i][0] = (message[i]) % 65;

	int cipherMatrix[l][1];

	// Following function generates
	// the encrypted vector
	encrypt(cipherMatrix, keyMatrix, messageVector);

	char CipherText[100];

	// Generate the encrypted text from
	// the encrypted vector
	for (int i = 0; i < l; i++){
	    int length = 0;
        while (CipherText[length] != '\0') {
            ++length;
        }
        CipherText[length] = cipherMatrix[i][0] + 65;
	 
	}
	   // strcat(CipherText, cipherMatrix[i][0]+65);
// 		CipherText += cipherMatrix[i][0] + 65;

	// Finally print the ciphertext
	printf(" Ciphertext: %s", CipherText);
}

// Driver function for above code
int main()
{
	// Get the message to be encrypted
	char message[] = "ACT";

	// Get the key
	char key[] = "GYBNQKURP";

    int length = 0;
    while (message[length] != '\0') {
        ++length;
    }
    l = length;
	HillCipher(message, key);

	return 0;
}
