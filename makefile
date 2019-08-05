#.PHONY:count_word
count_word:libword.a
	gcc -g -o count_word main.c -lword -L.
libword.a:double_list.o
	ar rcs libword.a double_list.o
double_list.o:double_list.c double_list.h
	gcc -g -c -Wall double_list.c
.PHONY:clean
clean:
	rm *.o count_word

