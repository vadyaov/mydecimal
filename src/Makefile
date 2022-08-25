CC	=	gcc
CFLAGS	=	-c	-Wall	-Werror	-Wextra	-std=c11	-pedantic
ARITH_SRC	=	s21_add.c	s21_mod.c	s21_mul.c	s21_sub.c	s21_div.c
COMPR_SRC	=	s21_is_equal.c	s21_is_not_equal.c	s21_is_greater_or_equal.c	s21_is_greater.c	s21_is_less_or_equal.c	s21_is_less.c
CONVR_SRC	=	s21_from_decimal_to_float.c	s21_from_decimal_to_int.c	s21_from_float_to_decimal.c	s21_from_int_to_decimal.c
OTHER_SRC	=	s21_negate.c	s21_round.c	s21_floor.c	s21_truncate.c
SOURCES	=	$(ARITH_SRC)	$(COMPR_SRC)	$(CONVR_SRC)	$(OTHER_SRC)
HELPERS	=	all_helpers.c
TEST_SRC	=	tests/convert_tests/*.c	tests/other_tests/*.c tests/arithmetic_tests/*.c tests/comparsion_test/*.c
RFLAGS	=	-fprofile-arcs	-ftest-coverage
LFLAGS	=	-lcheck	-lm	-lpthread
LIB_NAME	=	s21_decimal.a


all: s21_decimal.a	test

all_peer:	s21_decimal.a_peer	test_peer	gcov_report

s21_decimal.a:
	$(CC)	$(CFLAGS)	$(SOURCES)	$(HELPERS)
	ar	rcs	$(LIB_NAME)	*.o
	ranlib	$(LIB_NAME)
	rm	-r	*.o
s21_decimal.a_peer:
	$(CC)	$(CFLAGS)	$(HELPERS)
	$(CC)	$(CFLAGS)	$(RFLAGS)	$(SOURCES)
	ar	rcs	$(LIB_NAME)	*.o
	ranlib	$(LIB_NAME)
	rm	-r	*.o
test:
	$(CC)	$(CFLAGS)	-c	$(TEST_SRC)	tests/*.c
	$(CC)	*.o	$(LIB_NAME)	$(LFLAGS)	-o	tests/runtest
	tests/runtest
	rm	-rf	*.o
test_peer:
	$(CC)	$(CFLAGS)	-c	$(TEST_SRC)	tests/*.c
	$(CC)	$(RFLAGS)	*.o	$(LIB_NAME)	$(LFLAGS)	-o	tests/runtest
	tests/runtest
	rm	-rf	*.o
gcov_report:
	gcovr	-r	.	--html	--html-details	-o	coverage_report.html
	rm	-rf	*.o	*.out	*.gcno	*.gcna	*gcda
	open	./coverage_report.html
clean:
	rm	-rf	*.o	*.out	*.gcno	*.gcna	*.html	*.gcda	*.css	*.exe
	rm	-rf	*.a
	rm -rf tests/runtest

rebuild:	clean	s21_decimal.a