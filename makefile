##############################################################################
# Exemplo de makefile para um projeto em linguagem C++...
# Para simplificar, todos os arquivos estão em um mesmo diretório
##############################################################################
# Arquivo principal: main.cpp
##############################################################################
#                       Arquivos auxiliares do projeto
##############################################################################
# Registro.cpp: depende de Buffer.h 
# Buffer.cpp: depende de Buffer.h Registro.h e Arquivo.h 
# Arquivo.cpp: depende de Buffer.h Arquivo.h e Registro.h 
##############################################################################

# definindo as variáveis do projeto (MAIN é o nome do arquivo principal, que contem a função main, sem a extensao)

# Nome do arquivo principal (sem extensão)
MAIN := main
# Diretórios
SRC_DIR := src
INC_DIR := include
# Objetos a serem gerados
OBJECTS := $(SRC_DIR)/$(MAIN).o $(SRC_DIR)/Registro.o $(SRC_DIR)/Buffer.o $(SRC_DIR)/Arquivo.o $(SRC_DIR)/RegistroAluno.o
# Flags de compilação
FLAGS := -Wall -Wextra -std=c++17 -pedantic-errors -I$(INC_DIR)
# Habilitar depuração
DEBUG := -g
# Math lib (caso necessário)
MATH := -lm
# Compilador
CC := g++
# Ajuste para Windows/Linux
ifeq ($(OS), Windows_NT)
OUTPUTMAIN := $(MAIN).exe
RM := del /Q
else
OUTPUTMAIN := $(MAIN).out
RM := rm -rf
endif

# ponto de compilação principal
all: $(OUTPUTMAIN)
	@echo Compilação completa!

$(OUTPUTMAIN): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(OUTPUTMAIN) $(MATH)

# Compila os arquivos fonte
$(SRC_DIR)/main.o: main.cpp $(INC_DIR)/Arquivo.hpp $(INC_DIR)/Registro.hpp $(INC_DIR)/Buffer.hpp $(INC_DIR)/RegistroAluno.hpp
	$(CC) $(FLAGS) -c main.cpp -o $@

$(SRC_DIR)/Registro.o: $(SRC_DIR)/Registro.cpp $(INC_DIR)/Registro.hpp
	$(CC) $(FLAGS) -c $< -o $@

$(SRC_DIR)/Buffer.o: $(SRC_DIR)/Buffer.cpp $(INC_DIR)/Buffer.hpp $(INC_DIR)/Registro.hpp $(INC_DIR)/Arquivo.hpp
	$(CC) $(FLAGS) -c $< -o $@

$(SRC_DIR)/Arquivo.o: $(SRC_DIR)/Arquivo.cpp $(INC_DIR)/Arquivo.hpp $(INC_DIR)/Registro.hpp $(INC_DIR)/Buffer.hpp
	$(CC) $(FLAGS) -c $< -o $@

$(SRC_DIR)/RegistroAluno.o: $(SRC_DIR)/RegistroAluno.cpp $(INC_DIR)/RegistroAluno.hpp $(INC_DIR)/Registro.hpp
	$(CC) $(FLAGS) -c $< -o $@

clean:
	$(RM) $(OBJECTS)
	$(RM) $(OUTPUTMAIN)
	@echo Limpeza completa!

run: all
	./$(OUTPUTMAIN)
	@echo Execução completa!