TARGET=client server 
CC=gcc
server: server.c
	$(CC) server.c -o server -lpthread
client: client.c
	$(CC) client.c -o client 
clean:
	$(RM) $(TARGET)
