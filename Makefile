szukaj: main.o graph.o error.o queue.o algorithm.o
	$(CC) -o szukaj main.o graph.o error.o queue.o algorithm.o
.PHONY: clean


testp1:
        ./szukaj -f 2 -t 6 -i pliki_testowe/test1_1

testp1_sk:
        ./szukaj -f 2 -t 7 -i pliki_testowe/test1_2

testp1_pr:
        ./szukaj -f 2 -t 7 -i pliki_testowe/test1_3

testp1_err:
        ./szukaj -f 0 -t 24 -i pliki_testowe/test1_1

testp2:
        ./szukaj -f 2 -t 5 -i pliki_testowe/test2_1

testp3:
        ./szukaj -f 0 -t 1 -i pliki_testowe/test3_1

testp4:
        ./szukaj -f 2 -t 7 -i pliki_testowe/test4

testp5:
        ./szukaj -i pliki_testowe/test1_1

test_mygraf:
        ./szukaj -f 0 -t 24 -i pliki_testowe/mygraph


testbp1:
        ./szukaj -f 1 -t 5 -x 3 -y 3 -a 2 -b 8 -o pliki_potestach/test1 

testbp2:
        ./szukaj -f 1 -t 3 -x 1 -y 5 -a 2 -b 8 -o pliki_potestach/test2

testbp3:
        ./szukaj -f 0 -t 1 -x 1 -y 2 -a 2 -b 8 -o pliki_potestach/test3

testbp4:
        ./szukaj -f 0 -t 1 -x 2 -y 1 -a 2 -b 8 -o pliki_potestach/test4

testbp5:
        ./szukaj -x 10 -y 10 -a 0 -b 9 -o pliki_potestach/plik.txt


clean:
	-rm *.o szukaj
