CC = gcc

all: frontend backend

frontend:
	@${CC} frontend_files/frontend.c -o frontend_files/frontend -pthread
	@echo Ficheiros de frontend compilados!

backend:
	@${CC} backend_files/backend.c backend_files/users_lib.o -o backend_files/backend -pthread
	@echo Ficheiros de backend compilados!

clean:
	@rm *.o
	@echo Ficheiros limpos!