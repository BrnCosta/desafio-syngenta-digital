# Makefile

# Nome do Projeto
PROJ_NAME=desafio_syngenta

# .cpp
CPP= $(wildcard *.cpp)

# Compilador
CC= g++

# Delete
RM= rm -rf

#Compilar
all: $(PROJ_NAME)

$(PROJ_NAME):
	@ echo 'Realizando a build.'
	$(CC) main.cpp -o $(PROJ_NAME)

run: clean all
	@ echo 'Executando o projeto!'
	./$(PROJ_NAME)

clean:
	@ $(RM) ./*.o $(PROJ_NAME) *~ message.txt
	@ $(RM) message.txt