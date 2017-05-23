EXE=lzw
FLAGS= -Wall -g 

$(EXE) : main.o dictionnaire.o compression.o decompression.o
	gcc -o $(EXE) main.o dictionnaire.o compression.o decompression.o
 
main.o : main.c dictionnaire.h compression.h decompression.h
	gcc $(FLAGS) -c main.c dictionnaire.h compression.h decompression.h

dictionnaire.o : dictionnaire.c dictionnaire.h compression.h decompression.h
	gcc $(FLAGS) -c dictionnaire.c compression.h decompression.h

compression.o : compression.c compression.h dictionnaire.h decompression.h
	gcc $(FLGAS) -c compression.c compression.h dictionnaire.h decompression.h

decompression.o : decompression.c compression.h dictionnaire.h decompression.h
	gcc $(FLAGS) -c decompression.c compression.h dictionnaire.h decompression.h

clean : 
	rm -f -v *.gch *.o
.PHONY : clean

cleanall : clean
	rm -f -v $(EXE)
	rm -f -v zip
	rm -f -v unzip
.PHONY : cleanall