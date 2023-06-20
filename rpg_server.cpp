#include "DBSQLtable.h"
#include "screen.h"
#include <stdio.h>
#include <sqlite3.h>

using namespace std;

//static const char* servers[] = {"DNS name"};
//static const char* sessions[] = { "playerid","serverid"};

static const char* players[] = {"name","email","password"};
static const char* characters_intfields[] = { "playerid", "level", "classid"};
static const char* characters_strfields[] = { "name"};
static const char* classes_strfields[] = { "classname"};
static const char* teams_intfields[] = { "leader_player_id"};
static const char* teams_strfields[] = { "teamname"};
static const char* characterteamconnections[] = { "characterid", "teamid"};
static const char* matches[] = { "team1id", "team2id", "score1", "score2"};

int main() {
	sqlite3* db = 0;
	char* err = 0;
	if (sqlite3_open("lab2.dblite", &db)) {
		cout << "Error opening/creating DB: " << sqlite3_errmsg(db) << endl;
		exit(1);
	}
	std::vector<DBSQLobj*> dbmenu;
	//dbsqltable DBServers = dbsqltable(db,"Servers", 0, NULL, 1, servers);
	//dbsqltable DBSessions = dbsqltable(db, "Sessions", 2, sessions, 0, NULL);
	dbsqltable tables[] = {
		dbsqltable(db,"Players", 0, NULL, 3, players),
		dbsqltable(db,"CharacterClasses", 0, NULL, 1, classes_strfields),
		dbsqltable(db,"Characters", 3, characters_intfields, 1, characters_strfields),
		dbsqltable(db,"Teams", 1, teams_intfields, 1, teams_strfields),
		dbsqltable(db,"CharacterTeamConnections", 2, characterteamconnections, 0, NULL),
		dbsqltable(db,"Matches", 4, matches, 0, NULL)
	};
	for (int i=0; i< sizeof(tables) / sizeof(dbsqltable); i++) {
		dbmenu.push_back(static_cast<DBSQLobj*>(&tables[i]));
	}
	dbsqlview views[] = {
		//назви команд (та бали) €к≥ приймали участь в матч≥
		dbsqlview(db, "SELECT A.teamname, B.teamname, score1, score2 FROM Matches, Teams AS A, Teams AS B ON team1id = A.ID AND team2id= B.ID;"),
	};
	for (int i=0; i< sizeof(views) / sizeof(dbsqlview); i++) {
		dbmenu.push_back(static_cast<DBSQLobj*>(&views[i]));
	}
	dbsqlparamview paramviews[] = {
	//5 simple comparisons:

		//≥мена персонаж≥в, €к≥ належать гравц€м з поштою @TEXT0@
    	dbsqlparamview(db, "SELECT Characters.name FROM Players LEFT JOIN Characters ON playerid = Players.ID WHERE Players.email = @TEXT0@", 0, 1),
		//≥мена гравц≥в €к≥ мають персонаж≥в з ≥менем @TEXT0@
	    dbsqlparamview(db, "SELECT Players.name FROM Characters LEFT JOIN Players ON playerid = Players.ID WHERE Characters.name=@TEXT0@;", 0, 1),
        //пари ≥мен персонаж≥в р≥вень €ких вище або дор≥внюЇ @INTEGER0@, та ≥мена гравц≥м €ким ц≥ персонаж≥ належать
		dbsqlparamview(db, "SELECT Players.name, Characters.name FROM Characters LEFT JOIN Players ON playerid = Players.ID WHERE Characters.level>=@INTEGER0@;", 1, 0),

		//≥мена гравц≥в персонаж≥ €к≥ приймали участь в матчах
		dbsqlparamview(db, "SELECT Players.name FROM Players WHERE ID IN (SELECT Characters.playerid FROM Characters WHERE Characters.ID IN (SELECT characterid FROM CharacterTeamConnections WHERE teamid IN (SELECT team1id FROM Matches) OR teamid IN (SELECT team2id FROM Matches)))", 0, 0),

		//≥мена гравц≥в, €к≥ мають персонаж≥в у команд≥ з назвою @TEXT0@
		dbsqlparamview(db, "SELECT Players.name FROM Players WHERE ID IN (SELECT Characters.playerid FROM Characters WHERE Characters.ID IN (SELECT characterid FROM CharacterTeamConnections WHERE teamid IN (SELECT ID FROM Teams WHERE teamname=@TEXT0@)));", 0, 1),

		//3 comparisons:

		//≥мена гравц≥в €к≥ мають персонаж≥в з такими же классами €к хоч один з персонаж≥в гравц€ з ≥дом @INTEGER0@
		dbsqlparamview(db, "SELECT Players.name FROM Characters LEFT JOIN Players ON playerid=Players.ID WHERE classid IN ( SELECT classid FROM Characters WHERE playerid=@INTEGER0@ );", 1, 0),

		//ун≥кальн≥ пари персонаж≥в з однаковим р≥внем (A.id < B.id щоб персонаж≥ не повторювались)
		dbsqlparamview(db, "SELECT A.ID, A.Name, B.ID, B.Name FROM Characters AS A, Characters AS B WHERE A.level = B.level AND A.id < B.id;", 0, 0),

		//≥д та назви гравц≥в, у €ких к≥льк≥сть персонаж≥в така сама €к у гравц€ з ≥дом @INTEGER0@
		dbsqlparamview(db, "SELECT Players.ID, Players.name FROM Characters LEFT JOIN Players ON Players.id = playerid GROUP BY playerid HAVING COUNT(Characters.ID) in ( SELECT COUNT(ID) FROM Characters WHERE playerid = 1 );", 1, 0),

		//ўе 3 comparisons:

		//≥мена гравц≥в €к≥ мають персонаж≥в з такими же классами €к хоч один з персонаж≥в гравц€ з ≥дом @INTEGER0@, але
		//не мають клас≥в €к у хоч одного з персонаж≥в гравц€ з ≥дом @INTEGER1@
		dbsqlparamview(db, "SELECT Players.name FROM Characters LEFT JOIN Players ON playerid=Players.ID WHERE classid IN ( SELECT classid FROM Characters WHERE playerid=@INTEGER0@ ) AND classid NOT IN ( SELECT classid FROM Characters WHERE playerid=@INTEGER1@ );", 2, 0),
		//≥мена гравц≥в €к≥ мають персонаж≥в що вход€ть в команду з персонажем гравц€ з ≥дом @INTEGER0@
		dbsqlparamview(db, "SELECT Players.name FROM Players WHERE Players.ID IN (SELECT playerid FROM Characters WHERE Characters.ID IN (SELECT characterid FROM CharacterTeamConnections WHERE teamid IN ( SELECT teamid FROM CharacterTeamConnections WHERE characterid IN ( SELECT ID FROM Characters WHERE playerid=@INTEGER0@ ) ) ) );", 1, 0),
		//≥мена гравц≥в €к≥ мають персонаж≥в що вход€ть в команду з персонажем гравц€ з ≥дом @INTEGER0@, але
		//не мають персонаж≥в що вход€ть в команду з персонажем гравц€ з ≥дом @INTEGER1@
		dbsqlparamview(db, "SELECT Players.name FROM Players WHERE Players.ID IN (SELECT playerid FROM Characters WHERE Characters.ID IN (SELECT characterid FROM CharacterTeamConnections WHERE teamid IN ( SELECT teamid FROM CharacterTeamConnections WHERE characterid IN ( SELECT ID FROM Characters WHERE playerid=@INTEGER0@ ) ) ) ) AND Players.ID NOT IN (SELECT playerid FROM Characters WHERE Characters.ID IN (SELECT characterid FROM CharacterTeamConnections WHERE teamid IN ( SELECT teamid FROM CharacterTeamConnections WHERE characterid IN ( SELECT ID FROM Characters WHERE playerid=@INTEGER1@ ) ) ) );", 2, 0)
	};
	for (int i=0; i < sizeof(paramviews) / sizeof(dbsqlparamview); i++) {
		dbmenu.push_back(static_cast<DBSQLobj*>(&paramviews[i]));
	}

	string stateM;
	int state;
	do {
//		cls();
		int i;
		cout << "    Select Database table:\n"
		     << "(0) Exit menu\n";
		for (i=0; i< dbmenu.size(); i++) {
			cout << "(" << i + 1 << ") " << dbmenu[i]->Header4TableMenu() << "\n";
		}
		cout << "Type a number from 0 to " << dbmenu.size() << " to continue: ";
		cin >> stateM;
		cls();
		state = atoi(stateM.c_str());
		if (state < 0 || state > dbmenu.size()) {
			cout << "************************\n"
			     << "ERROR: DBMenu: incorrect option. Should be a number from 0 to "<< dbmenu.size() << "\n"
			     << "************************\n";
		}
		else if (state) {
			dbmenu[state - 1]->DBApp();
		}
		//pause();

	} while (state);
	sqlite3_close(db);
}
