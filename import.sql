-- players[] = {"name","email","password"};
-- servers[] = {"DNS name"};
-- sessions[] = { "playerid","serverid"};

--CREATE TABLE Sessions (ID INTEGER PRIMARY KEY, playerid INTEGER, serverid INTEGER);

--CREATE TABLE Servers (ID INTEGER PRIMARY KEY, DNSname TEXT);

CREATE TABLE Players (ID INTEGER PRIMARY KEY ASC ON CONFLICT FAIL AUTOINCREMENT, name TEXT, email TEXT, password TEXT);
CREATE TABLE CharacterClasses (ID INTEGER PRIMARY KEY ASC ON CONFLICT FAIL AUTOINCREMENT, classname TEXT);
CREATE TABLE Characters (ID INTEGER PRIMARY KEY ASC ON CONFLICT FAIL AUTOINCREMENT, playerid INTEGER, level INTEGER, classid INTEGER, name TEXT);
--one player can have multliple characters
CREATE TABLE Teams (ID INTEGER PRIMARY KEY ASC ON CONFLICT FAIL AUTOINCREMENT, leader_player_id INTEGER, teamname TEXT);
--in this specific RPG game, you can have multiple characters from one player in the same team
CREATE TABLE CharacterTeamConnections (ID INTEGER PRIMARY KEY ASC ON CONFLICT FAIL AUTOINCREMENT, characterid INTEGER, teamid INTEGER);
CREATE TABLE Matches (ID INTEGER PRIMARY KEY ASC ON CONFLICT FAIL AUTOINCREMENT, team1id INTEGER, team2id INTEGER, score1 INTEGER, score2 INTEGER);

--.import --csv InputServers.csv Servers
--.import --csv InputSessions.csv Sessions

.import --csv InputPlayers.csv Players
.import --csv InputCharacters.csv Characters
.import --csv InputClasses.csv CharacterClasses
.import --csv InputTeams.csv Teams
.import --csv InputCharacterTeamConnections.csv CharacterTeamConnections
.import --csv InputMatches.csv Matches
