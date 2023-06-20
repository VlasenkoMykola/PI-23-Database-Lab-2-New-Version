#include "DBSQLtable.h"
#include "screen.h"
#include <sqlite3.h>

/*
int dbsqltable::Search() {
	int found = 0;
	if (DBArray.size() <= 0) {
		cout << "Table is empty. Nothing to search";
	} else {
		db_object SearchExample;
		SearchExample.Init(num_intfields, intfieldnames, num_strfields, strfieldnames);
		SearchExample.ReadSearchExample();

		for (int i = 0; i < DBArray.size(); i++) {
			if (DBArray[i].MatchExample(SearchExample)) {
				DBArray[i].Print();
				found = 1;
			}
		}
	}
	return found;
}
*/

DBSQLobj::DBSQLobj() {};
DBSQLobj::DBSQLobj(sqlite3* database):
	db{database}
{
};

dbsqltable::dbsqltable(
	sqlite3* database, string table,
	int numIntFields, const char** IntFieldsNames,
	int numStrFields, const char** StrFieldsNames):
	DBSQLobj {database},
	tablename {table},
	num_intfields {numIntFields},
	intfieldnames {IntFieldsNames},
	num_strfields {numStrFields},
	strfieldnames {StrFieldsNames}
{
	ReadTable();
}

dbsqlview::dbsqlview(sqlite3* database): DBSQLobj {database} {};
dbsqlview::dbsqlview(sqlite3* database, string sql):
	DBSQLobj {database},
	sql4view {sql}
{
	ReadView();
}

dbsqlparamview::dbsqlparamview(sqlite3* database, string sql, int num_intplaceholders_new, int num_strplaceholders_new):
	dbsqlview {database},
	sql4param {sql},
	num_intplaceholders {num_intplaceholders_new},
	num_strplaceholders {num_strplaceholders_new}
{
}

DBSQLobj::~DBSQLobj() {};
dbsqltable::~dbsqltable() {};
dbsqlview::~dbsqlview() {};
dbsqlparamview::~dbsqlparamview() {};

void DBSQLobj::Print() {
	//cout << "Print: size=" << DBArray.size() << endl;
	for (int i = 0; i < DBArray.size(); i++) {
		cout << i << endl;
		DBArray[i].Print();
	}
}

string dbsqltable::Header4TableMenu() {
    return "table: " + tablename;
};

string dbsqlview::Header4TableMenu() {
	return "view: " + sql4view;
};

string dbsqlparamview::Header4TableMenu() {
	return "param: " + sql4param;
};

void DBSQLobj::ReadSQLRow(int numberCol, char** azColName, char** argv) {
	DBArray.push_back(SQL2DBObject(numberCol, azColName, argv));
};

db_object dbsqltable::SQL2DBObject(int numberCol, char** azColName, char** argv) {
	db_object newobj = db_object();
	//cout << "ReadSQLRow: tablename=" << tablename << endl;
	newobj.Init(num_intfields, intfieldnames, num_strfields, strfieldnames);
	newobj.ReadFromSQLTable(numberCol, azColName, argv);
	return newobj;
}

db_object dbsqlview::SQL2DBObject(int numberCol, char** azColName, char** argv) {
	db_object newobj = db_object();
	//cout << "ReadSQLRow: View: " << sql4view << endl;
	newobj.Init(0, NULL, numberCol, NULL);
	newobj.ReadFromSQLView(numberCol, azColName, argv);
	return newobj;
}

static int tablecallback(void* data, int argc, char** argv, char** azColName)
{
	dbsqltable* this_table = static_cast<dbsqltable*>(data);
	//for (int i = 0; i < argc; i++) {
	//	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	//}
	this_table->ReadSQLRow(argc, argv, azColName);
	return 0;
}

void dbsqltable::ReadTable() {

	string query = "SELECT * FROM " + tablename + ";";
	char* messaggeError;

	DBArray.resize(0);

	int exit = sqlite3_exec(db, query.c_str(), tablecallback, (void*)this, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error ReadTable " << tablename << messaggeError << std::endl;
		sqlite3_free(messaggeError);
	}
	else {
		//std::cout << "table " << tablename << " has been read successfully" << std::endl;
	}
}

static int viewcallback(void* data, int argc, char** argv, char** azColName)
{
	dbsqlview* this_table = static_cast<dbsqlview*>(data);
	//for (int i = 0; i < argc; i++) {
	//	printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	//}
	this_table->ReadSQLRow(argc, argv, azColName);
	return 0;
}

void dbsqlview::ReadView() {
	char* messaggeError = nullptr;
	DBArray.resize(0);

	int exit = sqlite3_exec(db, sql4view.c_str(), viewcallback, (void*)this, &messaggeError);
	if (exit != SQLITE_OK) {
		std::cerr << "Error ReadView. query: " << sql4view << " exit code: " << exit;
		if (messaggeError != nullptr) {
			std::cerr << " error message: " << messaggeError;
			sqlite3_free(messaggeError);
		}
		std::cerr << std::endl;
	}
	else {
		//std::cout << "query: " << sql4view << " has been read successfully" << std::endl;
	}
}

string dbsqltable::DBMenuTable() {
	string stateM;
	cls();
	cout << "    Database table menu [" << tablename << "]\n"
		<< "(0) Exit menu\n"
		<< "(1) Print DB table\n"
		<< "(2) Add DB entry\n"
		<< "(3) Delete DB entry\n"
		<< "(4) Edit DB entry\n"
		<< "Type a number from 0 to 4 to continue: ";
	cin >> stateM;
	cls();
	return stateM;
};

void dbsqltable::DBApp() {
	string stateM;
	do {
	    stateM = DBMenuTable();

	    if (stateM == "1") {
		Print();
		pause();
	    }
	    else if (stateM == "2") {
		Add();
	    }
	    else if (stateM == "3") {
		Delete();
		pause();
	    }
	    else if (stateM == "4") {
		Edit();
	    }
	    else if (stateM != "0") {
		cout << "************************\n"
		     << "ERROR: incorrect option. Should be a number from 0 to 4\n"
		     << "************************\n";

	    }

	} while (stateM != "0");
}

void dbsqltable::RawDelete(int idDel) {

	string query = "DELETE FROM " + tablename + " WHERE ID = " + to_string(idDel) + ";";
	char* messaggeError;

	int exit_sql = sqlite3_exec(db, query.c_str(), NULL, 0, &messaggeError);
	if (exit_sql != SQLITE_OK) {
		std::cerr << "Error Delete" << std::endl;
		exit(1);
	}
	ReadTable();
}

void dbsqltable::Add() {

	db_object newobj = db_object();
	newobj.Init(num_intfields, intfieldnames, num_strfields, strfieldnames);
	newobj.ReadSTDIN(0);

	string sql = "INSERT INTO " + tablename + "(" + newobj.getInsertColumnsForSQL() + " ) VALUES(" + newobj.getInsertValuesForSQL() + ");";

	char* messaggeError;
	int exit_sql = sqlite3_exec(db, sql.c_str(), NULL, 0, &messaggeError);
	if (exit_sql != SQLITE_OK) {
		std::cerr << "Error Add " << sql << std::endl;
		exit(1);
	}
	ReadTable();
}

void dbsqltable::Delete() {
	int idDel;
	cout << "Type in the ID of the table row you want to delete: ";
	cin >> idDel;
	RawDelete(idDel);
}


void dbsqltable::Edit() {

	int input_id;
	cout << "Type in the ID of the table row you want to edit:";
	cin >> input_id;
	string query = "UPDATE " + tablename + " SET ";
	for (int i = 0; i < DBArray.size(); i++) {
		if (DBArray[i].GetID() == input_id) {
			DBArray[i].Edit();
			query += DBArray[i].SQLforUpdate() + " WHERE ID = " + to_string(input_id);
		}
	}
	char* messaggeError;

	int exit_sql = sqlite3_exec(db, query.c_str(), NULL, 0, &messaggeError);
	if (exit_sql != SQLITE_OK) {
		std::cerr << "Error Edit" << std::endl;
		exit(1);
	}

	ReadTable();

}

string dbsqlview::DBMenuView() {
	string stateM;
	cls();
	cout << "    SQL View menu [" << sql4view << "]\n"
		<< "(0) Exit menu\n"
		<< "(1) Print Result\n"
		<< "Type a number from 0 to 1 to continue: ";
	cin >> stateM;
	cls();
	return stateM;
};

string dbsqlparamview::DBMenuParamView() {
	string stateM;
	//cls();
	cout << "    SQL ParamView menu\n";
	cout << "Param: [" << sql4param << "]\n";
	if (sql4view.size()) {
	    cout << "View: [" << sql4view << "]\n";
	} else {
	    cout << "View: [" << "none (set parameters first)" << "]\n";
	}
	cout << "(0) Exit menu\n";
	if (sql4view.size()) {
	    cout<< "(1) Print\n";
	}
	cout	<< "(2) Set Parameters\n"
		<< "Type a number from 0 to 2 to continue: ";
	cin >> stateM;
	//cls();
	return stateM;
};

void dbsqlview::DBApp() {
	string stateM;
	do {
		stateM = DBMenuView();
		if (stateM == "1") {
			Print();
			pause();
		}
		else if (stateM != "0") {
			cout << "************************\n"
				<< "ERROR: incorrect option. Should be a number from 0 to 1\n"
				<< "************************\n";
		}
	} while (stateM != "0");
}

void dbsqlparamview::DBApp() {
	string stateM;
	do {
		stateM = DBMenuParamView();
		if (stateM == "1") {
			Print();
			pause();
		}
		else if (stateM == "2") {
			ParamRead();
			pause();
		}
		else if (stateM != "0") {
			cout << "************************\n"
			     << "ERROR: ParamViewMenu: incorrect option [" << stateM << "]. Should be a number from 0 to 2\n"
				<< "************************\n";
		}
	} while (stateM != "0");
}

static void stringsubst(string& where, string what, string with) {
	size_t index = 0;
	while (index < where.size()) {
		/* Locate the substring to replace. */
		index = where.find(what, index);
		if (index == std::string::npos) break;
		/* Make the replacement. */
		where.replace(index, what.size(), with);
		/* Advance index forward so the next iteration doesn't pick it up as well. */
		index += with.size();
	}
}

void dbsqlparamview::ParamRead() {
	sql4view = sql4param;
	int input_int;
	int i;
	for (i = 0; i < num_intplaceholders; i++) {
		cout << "Enter the value for @INTEGER" << i << "@: " ;//<< endl;
		cin >> input_int;
		cout << endl;
		stringsubst(sql4view,"@INTEGER" + to_string(i) + "@", to_string(input_int));
	}

	string input_str;
	for (i = 0; i < num_strplaceholders; i++) {
		cout << "Enter the value for @TEXT" << i << "@: ";//<< endl;
		cin >> input_str;
		cout << endl;
		stringsubst(sql4view,"@TEXT" + to_string(i) + "@", "'" + input_str + "'");
	}

	ReadView();
}
