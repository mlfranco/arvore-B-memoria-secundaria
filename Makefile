#Arquivo de makefile do nosso projeto ##
############################# Makefile ##########################
all: main.out
#Faz a união de todos os arquivos compilados
main.out: ArvoreBinaria.o main.o
		gcc -o main.out ArvoreBinaria.o main.o
#compila a estrutura de árvore de tópicos
ArvoreBinaria.o:ArvoreBinaria.h
		gcc -o ArvoreBinaria.o -c ArvoreBinaria.c
#Compila o programa cliente
main.o:ArvoreBinaria.h
		gcc -o main.o -c main.c
#Elimina todos os arquivos objetos gerados com a compilação
clean:
		rm -rf *.o
#Elimina todos os arquivos objetos gerados com a compilação e o programa gerado
clean-all:clean
		rm main.out
#roda o programa
run:
		./main.out
#Apaga todos os arquivos gerados na compilação e recompila todos os módulos
rebuild:clean-all all
#Compila todos os módulos e executa o programa
build-run:all run
