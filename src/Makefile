CC	=	gcc
CFLAGS	=	-c	-Wall	-Werror	-Wextra	-std=c11	-pedantic
SOURCES	=	arithmetic/*.c	comparsion/*.c	converters/*.c	helpers/*.c	other/*.c
TEST_SRCS	=	tests/convert_tests/*.c	tests/other_tests/*.c tests/arithmetic_tests/*.c #tests/comparsion_test/*.c
RFLAGS	=	-fprofile-arcs	-ftest-coverage
LFLAGS	=	-lcheck	-lm	-lpthread
LIB_NAME	=	s21_decimal.a


all: s21_decimal.a

all_peer:	s21_decimal.a_peer	test_peer	gcov_report

s21_decimal.a:
	$(CC)	$(CFLAGS)	$(SOURCES)
	ar	rcs	$(LIB_NAME)	*.o
	ranlib	$(LIB_NAME)
	rm	-r	*.o
s21_decimal.a_peer:
	$(CC)	$(CFLAGS)	$(RFLAGS)	$(SOURCES)
	ar	rcs	$(LIB_NAME)	*.o
	ranlib	$(LIB_NAME)
	rm	-r	*.o
test_peer:
	$(CC)	$(CFLAGS)	-c	$(TEST_SRCS)	tests/*.c
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