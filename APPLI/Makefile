EXE=lzw
FLAGS= -Wall -g
# OPTIONS= -DDEBUG
OPTIONS=


$(EXE) : main.o dictionnaire.o compression.o decompression.o rle.o
	touch rle
	touch elr
	gcc -o $(EXE) main.o dictionnaire.o compression.o decompression.o rle.o

main.o : main.c dictionnaire.h compression.h decompression.h
	gcc $(FLAGS) $(OPTIONS) -c main.c dictionnaire.h compression.h decompression.h

dictionnaire.o : dictionnaire.c dictionnaire.h compression.h decompression.h
	gcc $(FLAGS) $(OPTIONS) -c dictionnaire.c dictionnaire.h compression.h decompression.h

compression.o : compression.c compression.h dictionnaire.h decompression.h
	gcc $(FLGAS) $(OPTIONS) -c compression.c compression.h dictionnaire.h decompression.h

decompression.o : decompression.c compression.h dictionnaire.h decompression.h
	gcc $(FLAGS) $(OPTIONS) -c decompression.c compression.h dictionnaire.h decompression.h

rle.o : rle.c rle.h
	gcc $(FLAGS) $(OPTIONS) -c rle.c rle.h

clean :
	rm -f -v *.gch *.o
.PHONY : clean

cleanall : clean
	rm -f -v $(EXE)
	rm -f -v zip
	rm -f -v unzip
	rm -f -v rle
	rm -f -v elr
.PHONY : cleanall
