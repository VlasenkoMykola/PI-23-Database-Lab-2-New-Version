OBJ = rpg_server.o DB_Object.o screen.o DBSQLtable.o
HEADERS = DB_Object.h screen.h DBSQLtable.h

main: $(OBJ) $(HEADERS)
	c++ -o main $(OBJ) -lsqlite3

lab2.dblite:
	sqlite3 lab2.dblite < import.sql

clean:
	rm -f main $(OBJ) *.7z *.zip
