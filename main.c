#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#define fileNameMaxLen 50
#define searchedWordsStrMaxLen 20
#define wordLenMax 50
#define outputFileWordsPerLine 15

int transformFile(char fileName[fileNameMaxLen]);

char searchedWords[][searchedWordsStrMaxLen] = {
	"fuck",
	"cum",
	"suck",
	"dick",
	"bullshit",
	"pussy",
	"bitch",
	"sex",
	"anal",
	"boob",
	"shit",
	"bastard",
	"cock",
	"crap",
	"cunt",
	"piss",
	"wank",
	"motherfucker",
	"ass"
};

char* replaceSymbols = "!@#$%&*";

int main(int argc, char const *argv[]) {
	if (argc == 1) {
		printf("Error: %20s\n", "Hey! No arguments. I don't know file which I need to transform");
		return 1;
	}
	if (strlen(argv[1]) > fileNameMaxLen-1) {
		printf("Error: %20s\n", "File name is too long");
		return 1;
	}

	srand(time(NULL));

	char fileName[fileNameMaxLen];

	strcpy(fileName, argv[1]);

	transformFile(fileName);

	return 0;
}

int transformFile(char fileName[fileNameMaxLen]) {
	FILE* soucreFile = NULL;
	FILE* outputFile = NULL;
	
	soucreFile = fopen(fileName, "r");
	if (soucreFile == NULL) {
		printf("Fatal error: %30s\n", "Can't open a file");
		return 1;
	}

	outputFile = fopen("output.txt", "w");
	if (outputFile == NULL) {
		printf("Fatal error: %30s\n", "Can't open a file");
		return 1;
	}

	char buf[wordLenMax];
	int wordCounts = sizeof(searchedWords)/sizeof(*searchedWords);
	int wpl = 0;
	int offset = 0;
	while(!feof(soucreFile)) {
		fscanf(soucreFile, "%s", buf);

		if ((wpl % outputFileWordsPerLine) == 0 && wpl != 0) {
			fputc('\n', outputFile);
		}

		for (int i = 0; i < strlen(buf); ++i) {
			buf[i] = tolower((unsigned char) buf[i]);
		}

		int y = 0;
		for (int i = 0; i < wordCounts; ++i) {
			if (strstr(buf, "ing")) {
				offset = 3;
				goto T;
			}
			if (strstr(buf, "ck")) {
				offset = 0;
			}
			if (strstr(buf, "er")) {
				offset = 2;	
			}
			if (strstr(buf, "ed")) {
				offset = 2;
				goto T;
			}
			T:
			if (strcmp(buf, searchedWords[i]) == 0) {
				for (int i = 0; i < strlen(buf)-offset; ++i) {
					// buf[(i!=0)? i : 1] = '*';
					buf[(i!=0)? i : 1] = replaceSymbols[rand()%(strlen(replaceSymbols))];
				}
				break;
			} else {
				if (strncmp(buf, searchedWords[i], strlen(searchedWords[i])) == 0) {
					for (int i = 0; i < strlen(buf)-offset; ++i) {
						buf[(i!=0)? i : 1] = replaceSymbols[rand()%(strlen(replaceSymbols))];
					}
					break;
				}
			}
		}

		strcat(buf, " ");

		fputs(buf, outputFile);

		++wpl;
	}

	fclose(soucreFile);
	fclose(outputFile);
}