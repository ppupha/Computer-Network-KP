#fisier folosit pentru compilarea surselor din proiect
all:
	gcc client.c login.c connection.c transferFiles.c -o client
	gcc server.c login.c connection.c transferFiles.c -o server -lsqlite3 -pthread
	gcc create_usersDB.c -o create_usersDB -lsqlite3
clean:
	rm -f client
	rm -f server
	rm -f create_usersDB

test:
	gcc test.c -o test.app
	
encode:
	gcc -o encode rsa_encode.c

decode: 
	gcc -o decode rsa_decode.c
