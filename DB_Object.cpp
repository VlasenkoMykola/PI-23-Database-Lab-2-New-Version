#include "DB_Object.h"
#include <cstring>

#ifdef _MSC_VER
#define mystrdup _strdup
#else
#define mystrdup strdup
#endif

db_object::db_object() {
	ID = 0;
	num_intfields = 0;
	num_strfields = 0;
}

db_object::~db_object() {
}

void db_object::Init(int num_intf, const char** intnames, int num_strf, const char** strnames) {
	ID = 0;
	num_intfields = num_intf;
	intfieldname = intnames;
	intfield = NULL;
	if (num_intf > 0)
		intfield = new int[num_intf];
	num_strfields = num_strf;
	strfieldname = strnames;
	strfield = NULL;
	if (num_strf > 0)
		strfield = new string[num_strf];
}

void db_object::Print() {
	if (ID != 0) {
		cout << "ID: " << ID << endl;
	}
	for (int i = 0; i < num_intfields; i++) {
		cout << intfieldname[i] << " " << intfield[i] << endl;
	}
	for (int i = 0; i < num_strfields; i++) {
		cout << strfieldname[i] << " " << strfield[i] << endl;
	}
	cout << "************************" << endl;
}

void db_object::Edit() {
	ReadSTDIN(ID);
}

void db_object::ReadSTDIN(int Id) {
	for (int i = 0; i < num_intfields; i++) {
		cout << "Type in " << intfieldname[i] << ": ";
		cin >> intfield[i];
	}
	for (int i = 0; i < num_strfields; i++) {
		cout << "Type in " << strfieldname[i] << ": ";
		cin >> strfield[i];
	}
	ID = Id;
}

void db_object::ReadFromSQLTable(int numberCol, char** argv, char** azColName) {
	if (1 + num_strfields + num_intfields != numberCol) {
		cout << "ERROR: number of columns mismatch in object and input!" << endl;
		cout << "DEBUG: num_strfields=" << num_strfields << " num_intfields=" << num_intfields << " numberCol=" << numberCol << endl;
		exit(1);
	}

	if (strncmp(azColName[0], "ID", sizeof("ID"))) {
		cout << "ERROR: column names don't match: ID vs " << azColName[0] << endl;
		exit(1);
	}

	ID = atoi(argv[0]);

	//starting from i=1 since first column ID was already checked and read
	for (int i = 0; i < num_intfields; i++) {
		if (strncmp(azColName[i+1], intfieldname[i], sizeof(intfieldname[i]))) {
			cout << "ERROR: column names don't match: " << azColName[i+1] << " vs " << intfieldname[i] << endl;
			exit(1);
		}
		intfield[i] = atoi(argv[i + 1]);
	}

	//starting from i = 1 + num_intfields
	for (int i = 0; i < num_strfields; i++) {
		if (strncmp(azColName[i + 1 + num_intfields], strfieldname[i], sizeof(strfieldname[i]))) {
			cout << "ERROR: column names don't match: " << azColName[i + 1 + num_intfields] << " vs " << strfieldname[i] << endl;
			exit(1);
		}
		strfield[i] = mystrdup(argv[i + 1 + num_intfields]);
	}
}

void db_object::ReadFromSQLView(int numberCol, char** argv, char** azColName) {
	strfieldname = new const char* [numberCol];
	num_strfields = numberCol;

	for (int i = 0; i < numberCol; i++) {
		strfield[i] = mystrdup(argv[i]);
		strfieldname[i] = mystrdup(azColName[i]);
	}
}

void db_object::ReadSearchExample() {
	cout << "Type in object ID (press 0 to skip): ";
	cin >> ID;
	for (int i = 0; i < num_intfields; i++) {
		cout << "Type in " << intfieldname[i] << " (type - to skip): ";
		cin >> intfield[i];
	}
	for (int i = 0; i < num_strfields; i++) {
		cout << "Type in " << strfieldname[i] << " (type - to skip): ";
		cin >> strfield[i];
	}
	cout << "************************\n";
}

/*
int db_object::MatchExample(db_object db_objectS) {

	int IdS = db_objectS.GetID();

	if (ID == IdS) {
		cout << "Id matches" << endl;
	} else if (IdS != 0) {
		return 0;
	}

	for (int i = 0; i < num_intfields; i++) {
		int matchval = db_objectS.intfield[i];
		if (intfield[i] == matchval) {
			if (matchval != 0) {
				cout << intfieldname[i] <<  " are equal " << endl;
			}
		} else if (matchval != 0) {
			return 0;
		}
	}

	for (int i = 0; i < num_strfields; i++) {
		if ((strfield[i].compare(db_objectS.strfield[i])) == 0) {
			cout << strfieldname[i] <<  " matches" << endl;
		} else if (db_objectS.strfield[i] != "-") {
			return 0;
		}
	}

	return 1;

}
*/

string db_object::getInsertColumnsForSQL() {
	string columns = "";
	for (int i = 0; i < num_intfields; i++) {
		if (columns.size()) {
			columns += ",";
		}
		columns += + intfieldname[i];
    }
	for (int i = 0; i < num_strfields; i++) {
		if (columns.size()) {
			columns += ",";
		}
		columns += strfieldname[i];
	}
	return columns;
}

string db_object::getInsertValuesForSQL() {
	string values = "";
	for (int i = 0; i < num_intfields; i++) {
		if (values.size()) {
			values += ",";
		}
		values += to_string(intfield[i]);
	}
	for (int i = 0; i < num_strfields; i++) {
		if (values.size()) {
			values += ",";
		}
		values += "'" + strfield[i] + "'";
	}
	return values;
}

string db_object::SQLforUpdate() {
	string sqlforupdate = "";
	for (int i = 0; i < num_intfields; i++) {
		if (sqlforupdate.size()) {
			sqlforupdate += ",";
		}
		sqlforupdate = sqlforupdate + intfieldname[i] + "=" + to_string(intfield[i]);
	}
	for (int i = 0; i < num_strfields; i++) {
		if (sqlforupdate.size()) {
			sqlforupdate += ",";
		}
		sqlforupdate = sqlforupdate + strfieldname[i] + "= '" + strfield[i] + "'";
	}
	return sqlforupdate;

}
