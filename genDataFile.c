
#include <stdio.h>
#include <stdlib.h>
#pragma pack(1) 
#include "Person.h"


void insertToDat() {

	FILE *datFile;
	fopen_s(&datFile, "Person.dat", "wb");//deschidem fisierul in modul scriere de biti
	if (datFile == NULL) {
		printf("Error opening file!\n");
		return;
	}

	struct PersonTmpl person;
	int headerSize = sizeof(person.nPersonID) + sizeof(person.chRecordType);

	//initializam strctura persoana cu inregistrarea de tip 1
	person = { 1,'1',{ "Andrei","Pop","1/11/1999",Male }  };
	fwrite(&person, sizeof(struct PersonTmpl), 1, datFile); //dupa scriem structura in fisier

	//initializam strctura persoana de data asta cu inregistrarea de tip 2
	person = { 1,'2',{} };
	person.Details.HomeDetails = { { "Str Stefan","Iasi","Roamania" },"0123456789","mail@gmail.com" };
	fwrite(&person, sizeof(struct PersonTmpl), 1, datFile);

	//initializam strctura persoana de data asta cu inregistrarea de tip 3
	person = { 1,'3' };
	person.Details.WorkDetails = { "Company",{ "Str Stefan","Iasi","Roamania" },"0123456789","fax","mail@gmail.com" };
	fwrite(&person, sizeof(struct PersonTmpl), 1, datFile);

	fclose(datFile);
}


int main(void)
{
	insertToDat(); //inseram in fisierul Person.dat cate un exemplu de fiecare tip de data
	return 0;
}