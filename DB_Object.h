#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class db_object {
protected:
	int ID;
	int num_strfields;
	string* strfield;
	const char** strfieldname;
	int num_intfields;
	const char** intfieldname;
	int* intfield;

public:

	db_object();
	~db_object();
	int GetID() { return ID; };
	void Init(int numIntFields, const char** IntFieldNames, int numStrFields, const char** StrFieldNames);
	void Print();
	void Edit();
	void ReadSTDIN(int Id);
	void ReadSearchExample();
	void ReadFromSQLTable(int numberCol, char** argv, char** azColName);
	void ReadFromSQLView(int numberCol, char** argv, char** azColName);
	string getInsertColumnsForSQL();
	string getInsertValuesForSQL();
	string SQLforUpdate();
};
