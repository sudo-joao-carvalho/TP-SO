CC = gcc

all: frontend backend promotor

frontend:
	@${CC} frontend_files/frontend.c -o frontend
	@echo Ficheiros de frontend compilados!

backend:
	@${CC} back_end_files/backend.c -o backend
	@echo Ficheiros de backend compilados!

promotor:
	@{CC} promotor_files/promotor.c -o promotor
	@echo Ficheiros de promotor compilados!

clean:
	@rm *.o
	@echo Ficheiros limpos!