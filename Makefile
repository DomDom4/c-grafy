szukaj: main.o graph.o error.o queue.o algorithm.o
	$(CC) -o szukaj main.o graph.o error.o queue.o algorithm.o
.PHONY: clean


#Grafy z pliku:

testp1: #z pliku graf 3x3 nieskierowany
	./szukaj -f 2 -t 6 -i pliki_testowe/test1_1

testp1_sk: #z pliku graf 3x3 skierowany
	./szukaj -f 2 -t 7 -i pliki_testowe/test1_2

testp1_pr: #z pliku graf 3x3 z przecinkami zamiast kropek w liczbach
	./szukaj -f 2 -t 7 -i pliki_testowe/test1_3

testp1_err: #z pliku graf 3x3, sciezka do wezła, ktory nie istnieje
	./szukaj -f 0 -t 24 -i pliki_testowe/test1_1

testp2: #z pliku graf o szerkosci 1
	./szukaj -f 2 -t 5 -i pliki_testowe/test2_1

testp3: #z pliku graf o jednej krawedzi
	./szukaj -f 0 -t 1 -i pliki_testowe/test3_1

testp4: #z pliku graf niespojny
	./szukaj -f 2 -t 7 -i pliki_testowe/test4

testp5: #z pliku graf z testu 1. bez wyznczonego poczatku i konca sciezki
	./szukaj -i pliki_testowe/test1_1

test_mygraph: #z pliku mygraph z isod
	./szukaj -f 0 -t 24 -i pliki_testowe/mygraph


#Garfy generowane:

testbp1: #graf 3x3
	./szukaj -f 1 -t 5 -x 3 -y 3 -a 2 -b 8 -o pliki_potestach/test1 

testbp2: #graf o szerokosci 1
	./szukaj -f 1 -t 3 -x 1 -y 5 -a 2 -b 8 -o pliki_potestach/test2

testbp3: #graf o jednej krawedzi
	./szukaj -f 0 -t 1 -x 1 -y 2 -a 2 -b 8 -o pliki_potestach/test3

testbp4: #graf o jednej krawedzi
	./szukaj -f 0 -t 1 -x 2 -y 1 -a 2 -b 8 -o pliki_potestach/test4

testbp5: #graf 10x10 bez podanego wezla poczatkowego i koncowego
	./szukaj -x 10 -y 10 -a 0 -b 9 -o pliki_potestach/test5

#Graf podzielony

testbpd1: #graf 3x3 podzilony na 2 grafy
	./szukaj -f 1 -t 5 -x 3 -y 3 -a 2 -b 8 -n 2 -o pliki_potestach/test6

testbpd2: #graf 3x3 podzielony na 3 grafy
	./szukaj -f 1 -t 5 -x 3 -y 3 -a 2 -b 8 -n 3 -o pliki_potestach/test7

testbpd3: #graf 7x7 podzielony na 5 grafow
	./szukaj -f 3 -t 8 -x 7 -y 7 -a 0 -b 9 -n 5 -o pliki_potestach/test8



clean:
	-rm *.o szukaj
