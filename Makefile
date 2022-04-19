szukaj: main.o graph.o error.o queue.o algorithm.o
	$(CC) -o szukaj main.o graph.o error.o queue.o algorithm.o
.PHONY: clean

test: clean szukaj test_plik test_gen

test_gen: gen_3x3 gen_1x5 gen_1x2 gen_2x1 gen_10x10_bez_ft gen_3x3_2grafy gen_3x3_3grafy gen_7x7_5grafow

test_plik: plik_3x3 plik_3x3_skierowany plik_3x3_przecinki plik_3x3_err_sciezka plik_1x7 plik_1x2 plik_niespojny plik_3x3_bez_ft plik_mygraph

#Grafy z pliku:

plik_3x3: #z pliku graf 3x3 nieskierowany
	./szukaj -f 2 -t 6 -i pliki_testowe/test1_1

plik_3x3_skierowany: #z pliku graf 3x3 skierowany
	./szukaj -f 2 -t 7 -i pliki_testowe/test1_2

plik_3x3_przecinki: #z pliku graf 3x3 z przecinkami zamiast kropek w liczbach
	./szukaj -f 2 -t 7 -i pliki_testowe/test1_3

plik_3x3_err_sciezka: #z pliku graf 3x3, sciezka do wezła, ktory nie istnieje
	-./szukaj -f 0 -t 24 -i pliki_testowe/test1_1

plik_1x7: #z pliku graf o szerkosci 1
	./szukaj -f 2 -t 5 -i pliki_testowe/test2_1

plik_1x2: #z pliku graf o jednej krawedzi
	./szukaj -f 0 -t 1 -i pliki_testowe/test3_1

plik_niespojny: #z pliku graf niespojny
	./szukaj -f 2 -t 7 -i pliki_testowe/test4

plik_3x3_bez_ft: #z pliku graf z testu 1. bez wyznczonego poczatku i konca sciezki
	./szukaj -i pliki_testowe/test1_1

plik_mygraph: #z pliku mygraph z isod
	./szukaj -f 0 -t 24 -i pliki_testowe/mygraph


#Garfy generowane: 

gen_3x3: #graf 3x3
	./szukaj -f 1 -t 5 -x 3 -y 3 -a 2 -b 8 -o pliki_potestach/test1 

gen_1x5: #graf o szerokosci 1
	./szukaj -f 1 -t 3 -x 1 -y 5 -a 2 -b 8 -o pliki_potestach/test2

gen_1x2: #graf o jednej krawedzi
	./szukaj -f 0 -t 1 -x 1 -y 2 -a 2 -b 8 -o pliki_potestach/test3

gen_2x1: #graf o jednej krawedzi
	./szukaj -f 0 -t 1 -x 2 -y 1 -a 2 -b 8 -o pliki_potestach/test4

gen_10x10_bez_ft: #graf 10x10 bez podanego wezla poczatkowego i koncowego
	./szukaj -x 10 -y 10 -a 0 -b 9 -o pliki_potestach/test5

#Graf podzielony

gen_3x3_2grafy: #graf 3x3 podzilony na 2 grafy
	-./szukaj -f 1 -t 5 -x 3 -y 3 -a 2 -b 8 -n 2 -o pliki_potestach/test6

gen_3x3_3grafy: #graf 3x3 podzielony na 3 grafy
	-./szukaj -f 1 -t 5 -x 3 -y 3 -a 2 -b 8 -n 3 -o pliki_potestach/test7

gen_7x7_5grafow: #graf 7x7 podzielony na 5 grafow
	-./szukaj -f 3 -t 8 -x 7 -y 7 -a 0 -b 9 -n 5 -o pliki_potestach/test8



clean:
	-rm *.o szukaj pliki_potestach/test* || true
