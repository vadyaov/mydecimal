CC = gcc
CFLAGS = -c -Wall -Werror -Wextra -std=c11 -pedantic
SOURCES = arithmetic/*.c comparsion/*.c converters/*.c helpers/*.c other/*.c




all:


s21_decimal.a:
	$(CC) $(CFLAGS) $(SOURCES)
	ar rcs s21_decimal.a *.o
	ranlib s21_decimal.a
	rm -r *.o

clean:
	rm -rf *.o *.out *.gcno *.gcna *.html *.gcda *.css *.exe
	rm -rf testrun/testrun
	rm -rf *.a

rebuild: clean s21_decimal.a