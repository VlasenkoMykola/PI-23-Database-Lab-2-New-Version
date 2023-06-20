#pragma once

#include <iostream>
#include <string>
#include <sqlite3.h>
#include "DB_Object.h"
#include <vector>

using namespace std;

class DBSQLobj {
protected:
	sqlite3* db;
	std::vector<db_object> DBArray;

public:
	DBSQLobj();
	DBSQLobj(sqlite3* database);
	virtual ~DBSQLobj();

	sqlite3* getDB() { return db; };
	void Print();
	void ReadSQLRow(int numberCol, char** azColName, char** argv);
	virtual db_object SQL2DBObject(int numberCol, char** azColName, char** argv)=0;
	virtual void DBApp()=0;
	virtual string Header4TableMenu()=0;
};

class dbsqltable : public DBSQLobj {

protected:
	string tablename;
	int num_strfields = 0;
	const char** strfieldnames = 0;
	int num_intfields = 0;
	const char** intfieldnames = 0;

public:
	dbsqltable(sqlite3* database, string table,
		int numIntFields, const char** IntFieldsNames,
		int numStrFields, const char** StrFieldsNames);
	~dbsqltable();

	void ReadTable();
	void Edit();
	void Add();
	void Delete();
	void RawDelete(int idDel);
	string DBMenuTable();
	string Header4TableMenu();
	void DBApp();
	db_object SQL2DBObject(int numberCol, char** azColName, char** argv);
};

class dbsqlview : public DBSQLobj {

protected:
	string sql4view;

public:
	dbsqlview(sqlite3* database);
	dbsqlview(sqlite3* database, string sql);
	~dbsqlview();

	string getSql4View() { return sql4view; };
	void ReadView();
	string DBMenuView();
	string Header4TableMenu();
	void DBApp();
	db_object SQL2DBObject(int numberCol, char** azColName, char** argv);
};

class dbsqlparamview : public dbsqlview {

protected:
	string sql4param;
	int num_intplaceholders;
	int num_strplaceholders;

public:
	dbsqlparamview(sqlite3* database, string sql, int num_intplaceholders_new, int num_strplaceholders_new);
	~dbsqlparamview();

	void DBApp();
	void ParamRead();
	string DBMenuParamView();
	string Header4TableMenu();
};
