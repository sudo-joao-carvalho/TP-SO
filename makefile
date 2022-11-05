CC = gcc

all: frontend backend promotor

frontend:
	@${CC} frontend_files/frontend.c -o ../frontendfiles/frontend
	@echo Ficheiros de frontend compilados!

backend:
	@${CC} backend_files/backend.c -o ../backend_files/backend
	@echo Ficheiros de backend compilados!

promotor:
	@{CC} promotor_files/promotor.c -o ../promotorfiles/promotor
	@echo Ficheiros de promotor compilados!

clean:
	@rm *.o
	@echo Ficheiros limpos!