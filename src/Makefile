CC	=	gcc
CFLAGS	=	-c	-Wall	-Werror	-Wextra	-std=c11	-pedantic
ARITH_SRC	=	arithmetic/s21_add.c	arithmetic/s21_div.c	arithmetic/s21_mod.c	arithmetic/s21_mul.c	arithmetic/s21_sub.c
COMPR_SRC	=	comparsion/s21_is_equal.c	comparsion/s21_is_not_eq.c	comparsion/s21_is_greater_or_eq.c	comparsion/s21_is_greater.c	comparsion/s21_is_less_or_eq.c	comparsion/s21_is_less.c
CONVR_SRC	=	converters/s21_from_dec_to_float.c	converters/s21_from_dec_to_int.c	converters/s21_from_float_to_dec.c	converters/s21_from_int_to_dec.c
OTHER_SRC	=	other/*.c
SOURCES	=	$(ARITH_SRC)	$(COMPR_SRC)	$(CONVR_SRC)	$(OTHER_SRC)
HELP_SRC	=	arithmetic/arithmetic_help.c	comparsion/comp_help.c	converters/conv_help.c
HELPERS	=	helpers/*.c
TEST_SRC	=	tests/convert_tests/*.c	tests/other_tests/*.c tests/arithmetic_tests/*.c tests/comparsion_test/*.c
RFLAGS	=	-fprofile-arcs	-ftest-coverage
LFLAGS	=	-lcheck	-lm	-lpthread
LIB_NAME	=	s21_decimal.a


all: s21_decimal.a

all_peer:	s21_decimal.a_peer	test_peer	gcov_report

s21_decimal.a:
	$(CC)	$(CFLAGS)	$(SOURCES)	$(HELP_SRC)	$(HELPERS)
	ar	rcs	$(LIB_NAME)	*.o
	ranlib	$(LIB_NAME)
	rm	-r	*.o
s21_decimal.a_peer:
	$(CC)	$(CFLAGS)	$(HELP_SRC)	$(HELPERS)
	$(CC)	$(CFLAGS)	$(RFLAGS)	$(SOURCES)
	ar	rcs	$(LIB_NAME)	*.o
	ranlib	$(LIB_NAME)
	rm	-r	*.o
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

rebuild:	clean	s21_decimal.a