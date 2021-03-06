// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>
#pragma pack(1)
#include "Person.h"



void make_initfile() {
	FILE *inifile;
	
	fopen_s(&inifile, "testc.ini", "w");

	if (inifile == NULL) {
		printf("Error opening file!\n");
	}
	else {
		fprintf(inifile, "[testc]\nin=Person.dat\nout=Person.txt");
		fclose(inifile);
	}
}

void read_initFile(char *path, char *section, char *key, char* value) {
	FILE *inifile;
	char fSection[10];
	char fKey[10];
	char line[100];


	int lenKey;

	bool foudSection = 0;
	bool foundKey = 0;

	//Sectiunea formatata cu paranteze
	strcpy_s(fSection, "[");
	strcat_s(fSection, section);
	strcat_s(fSection, "]\n");

	strcpy_s(fKey, key);
	strcat_s(fKey, "=");

	lenKey = strlen(fKey);

	fopen_s(&inifile, path, "r");
	if (inifile == NULL) {
		printf("Error opening file!\n");
	}
	else {
		while (fgets(line, 99, inifile) != NULL) {
			if (!foudSection) { //cautam sectiunea prima
				if (strcmp(fSection, line) == 0) { //topicul l-am formatat deja [topic]\n deci trebuie sa fie egal cu linia 
					foudSection = 1;
				}
				continue; //in caz ca nu am gasit topicul deja sarim peste linie
			}
			if (foudSection && !foundKey) { //in caz ca am dat peste un '[' inseamna ca am ajuns la topicul urmator si nu am gasit ckeia
				if (line[0] == '[') break;
			}
			if (strncmp(fKey, line, lenKey) == 0) {//am gasit cheia
				foundKey = 1;
				strcpy_s(value,20,line + lenKey);
				value[strlen(value) - 1] = '\0';
				continue;
			}
		}
		fclose(inifile);
	}
}

void convertToASCII(char* pathIn, char* pathOut) {
	FILE *datFile,*txtFile;
	struct PersonTmpl person;
	int pozitie;

	fopen_s(&datFile, pathIn, "rb");//deschidem fisierul in modul scriere de biti
	if (datFile == NULL) {
		printf("Eroare la descidere fisier input!\n");
		return;
	}

	printf("%i\n", sizeof(struct PersonTmpl));

	fopen_s(&txtFile, pathOut, "w");
	if (datFile == NULL) {
		printf("Eroare la deschidere fisier output!\n");
		return;
	}

	while (fread(&person, sizeof(struct PersonTmpl), 1, datFile)){
		pozitie = 1;
		fprintf_s(txtFile, " _______________________________________________________________\n");
		fprintf_s(txtFile,"|\tCamp\t\t|\tPozitite\t|Nr.caractere\t|\t\tObs\t\t|\n");
		fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
		fprintf_s(txtFile, "|PersonID\t\t|%i\t\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.nPersonID),"");
		pozitie += sizeof(person.nPersonID);
		fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
		fprintf_s(txtFile, "|RecordType\t\t|%i\t\t\t\t|%i\t\t\t\t|Este %c\t\t\t|\n", pozitie, sizeof(person.chRecordType), person.chRecordType);
		pozitie += sizeof(person.chRecordType);
		fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
		switch(person.chRecordType) {
		case '1':
			fprintf_s(txtFile, "|LastName\t\t|%i\t\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.PersonalInfo.sLastName), "");
			pozitie += sizeof(person.Details.PersonalInfo.sLastName);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|FirstName\t\t|%i\t\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.PersonalInfo.sFirstName), "");
			pozitie += sizeof(person.Details.PersonalInfo.sFirstName);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|Birthdate\t\t|%i\t\t\t\t|%i\t\t\t\t|%s\t|\n", pozitie, sizeof(person.Details.PersonalInfo.sLastName), "Data in format");
			fprintf_s(txtFile, "|\t\t\t\t|\t\t\t\t|\t\t\t\t|%s\t\t|\n",  "ZZ-LL-AAAA");
			pozitie += sizeof(person.Details.PersonalInfo.sBirthdate);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|Gender\t\t\t|%i\t\t\t\t|%i\t\t\t\t|%s\t\t\t|\n", pozitie, sizeof(person.Details.PersonalInfo.theGender), "Sexul:");
			fprintf_s(txtFile, "|\t\t\t\t|\t\t\t\t|\t\t\t\t|%s\t\t|\n", "M-Masculin");
			fprintf_s(txtFile, "|\t\t\t\t|\t\t\t\t|\t\t\t\t|%s\t\t|\n", "F-Feminin");
			pozitie += sizeof(person.Details.PersonalInfo.theGender);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|CR/LF\t\t\t|%i\t\t\t\t|%i\t\t\t\t|%s|\n", pozitie, 2, "Terminatorlinie");
			break;
		case '2':
			fprintf_s(txtFile, "|Street\t\t\t|%i\t\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.HomeDetails.homeAddress.sStreet), "");
			pozitie += sizeof(person.Details.HomeDetails.homeAddress.sStreet);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|City\t\t\t|%i\t\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.HomeDetails.homeAddress.sCity), "");
			pozitie += sizeof(person.Details.HomeDetails.homeAddress.sCity);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|Country\t\t|%i\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.HomeDetails.homeAddress.sCountry), "");
			pozitie += sizeof(person.Details.HomeDetails.homeAddress.sCountry);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|Phone\t\t\t|%i\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.HomeDetails.sPhone), "");
			pozitie += sizeof(person.Details.HomeDetails.sPhone);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|Email\t\t\t|%i\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.HomeDetails.sEmail), "");
			pozitie += sizeof(person.Details.HomeDetails.sEmail);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|CR/LF\t\t\t|%i\t\t\t|%i\t\t\t\t|%s|\n", pozitie, 2, "Terminatorlinie");
			break;
		case '3':
			fprintf_s(txtFile, "|Company\t\t|%i\t\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.WorkDetails.sCompany), "");
			pozitie += sizeof(person.Details.WorkDetails.sCompany);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|Street\t\t\t|%i\t\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.WorkDetails.workAddress.sStreet), "");
			pozitie += sizeof(person.Details.WorkDetails.workAddress.sStreet);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|City\t\t\t|%i\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.WorkDetails.workAddress.sCity), "");
			pozitie += sizeof(person.Details.WorkDetails.workAddress.sCity);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|Country\t\t|%i\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.WorkDetails.workAddress.sCountry), "");
			pozitie += sizeof(person.Details.WorkDetails.workAddress.sCountry);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|Phone\t\t\t|%i\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.WorkDetails.sPhone), "");
			pozitie += sizeof(person.Details.WorkDetails.sPhone);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|Email\t\t\t|%i\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.WorkDetails.sFax), "");
			pozitie += sizeof(person.Details.WorkDetails.sFax);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|Email\t\t\t|%i\t\t\t|%i\t\t\t\t|%s\t\t\t\t|\n", pozitie, sizeof(person.Details.WorkDetails.sEmail), "");
			pozitie += sizeof(person.Details.WorkDetails.sEmail);
			fprintf_s(txtFile, "|---------------------------------------------------------------|\n");
			fprintf_s(txtFile, "|CR/LF\t\t\t|%i\t\t\t|%i\t\t\t\t|%s|\n", pozitie, 2, "Terminatorlinie");


			break;
		}
		fprintf_s(txtFile, " ---------------------------------------------------------------\n\n");
	}

	fclose(datFile);
	fclose(txtFile);
}

int main()
{
	char iniFile[] = "testc.ini";
	char section[] = "testc";
	char inkey[] = "in";
	char outkey[] = "out";
	char inFile[20];
	char outFile[20];

	//make_initfile(); //genereaza fisierul .ini
	read_initFile(iniFile, section, inkey, inFile);
	read_initFile(iniFile, section, outkey, outFile);
	printf(inFile);
	printf(outFile);

	//acum avem nume fisierelor de intrare si iesire
	convertToASCII(inFile,outFile);

    return 0;
}
