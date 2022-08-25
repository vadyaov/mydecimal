#include "decimal_test.h"

int main() {
    int no_failed1 = 0;
    int no_failed2 = 0;
    int no_failed3 = 0;
    // int no_failed4 = 0;
    // int no_failed5 = 0;
    // int no_failed6 = 0;
    // int no_failed7 = 0;
    // int no_failed8 = 0;
    // int no_failed9 = 0;
    // int no_failed10 = 0;
    // int no_failed11 = 0;
    // int no_failed12 = 0;
    // int no_failed13 = 0;
    // int no_failed14 = 0;
    // int no_failed15 = 0;

    Suite *s1, *s2, *s3/*, *s4, *s5, *s6, *s7, *s8, *s9, *s10, *s11, *s12,
                   *s13, *s14, *s15*/;
    SRunner *runner1, *runner2, *runner3/*, *runner4, *runner5, *runner6, *runner7, *runner8,
            *runner9, *runner10, *runner11, *runner12, *runner13, *runner14, *runner15*/;

    s1 = s21_from_int_to_decimal_test();
    runner1 = srunner_create(s1);
    srunner_set_fork_status(runner1, CK_NOFORK);
    srunner_run_all(runner1, CK_NORMAL);
    no_failed1 = srunner_ntests_failed(runner1);
    srunner_free(runner1);

    s2 = s21_from_decimal_to_int_test();
    runner2 = srunner_create(s2);
    srunner_set_fork_status(runner2, CK_NOFORK);
    srunner_run_all(runner2, CK_NORMAL);
    no_failed2 = srunner_ntests_failed(runner2);
    srunner_free(runner2);

    s3 = s21_from_float_to_decimal_test();
    runner3 = srunner_create(s3);
    srunner_set_fork_status(runner3, CK_NOFORK);
    srunner_run_all(runner3, CK_NORMAL);
    no_failed3 = srunner_ntests_failed(runner3);
    srunner_free(runner3);
/*
    s4 = s21_Suite_log();
    runner4 = srunner_create(s4);
    srunner_set_fork_status(runner4, CK_NOFORK);
    srunner_run_all(runner4, CK_NORMAL);
    no_failed4 = srunner_ntests_failed(runner4);
    srunner_free(runner4);

    s5 = s21_Suite_pow();
    runner5 = srunner_create(s5);
    srunner_set_fork_status(runner5, CK_NOFORK);
    srunner_run_all(runner5, CK_NORMAL);
    no_failed5 = srunner_ntests_failed(runner5);
    srunner_free(runner5);

    s6 = s21_Suite_sin();
    runner6 = srunner_create(s6);
    srunner_set_fork_status(runner6, CK_NOFORK);
    srunner_run_all(runner6, CK_NORMAL);
    no_failed6 = srunner_ntests_failed(runner6);
    srunner_free(runner6);

    s7 = s21_Suite_cos();
    runner7 = srunner_create(s7);
    srunner_set_fork_status(runner7, CK_NOFORK);
    srunner_run_all(runner7, CK_NORMAL);
    no_failed7 = srunner_ntests_failed(runner7);
    srunner_free(runner7);

    s8 = s21_Suite_sqrt();
    runner8 = srunner_create(s8);
    srunner_set_fork_status(runner8, CK_NOFORK);
    srunner_run_all(runner8, CK_NORMAL);
    no_failed8 = srunner_ntests_failed(runner8);
    srunner_free(runner8);

    s9 = s21_Suite_fmod();
    runner9 = srunner_create(s9);
    srunner_set_fork_status(runner9, CK_NOFORK);
    srunner_run_all(runner9, CK_NORMAL);
    no_failed9 = srunner_ntests_failed(runner9);
    srunner_free(runner9);

    s10 = s21_Suite_acos();
    runner10 = srunner_create(s10);
    srunner_set_fork_status(runner10, CK_NOFORK);
    srunner_run_all(runner10, CK_NORMAL);
    no_failed10 = srunner_ntests_failed(runner10);
    srunner_free(runner10);

    s11 = s21_Suite_asin();
    runner11 = srunner_create(s11);
    srunner_set_fork_status(runner11, CK_NOFORK);
    srunner_run_all(runner11, CK_NORMAL);
    no_failed11 = srunner_ntests_failed(runner11);
    srunner_free(runner11);

    s12 = s21_Suite_tan();
    runner12 = srunner_create(s12);
    srunner_set_fork_status(runner12, CK_NOFORK);
    srunner_run_all(runner12, CK_NORMAL);
    no_failed12 = srunner_ntests_failed(runner12);
    srunner_free(runner12);

    s13 = s21_Suite_atan();
    runner13 = srunner_create(s13);
    srunner_set_fork_status(runner13, CK_NOFORK);
    srunner_run_all(runner13, CK_NORMAL);
    no_failed13 = srunner_ntests_failed(runner13);
    srunner_free(runner13);

    s14 = s21_Suite_floor();
    runner14 = srunner_create(s14);
    srunner_set_fork_status(runner14, CK_NOFORK);
    srunner_run_all(runner14, CK_NORMAL);
    no_failed14 = srunner_ntests_failed(runner14);
    srunner_free(runner14);

    s15 = s21_Suite_ceil();
    runner15 = srunner_create(s15);
    srunner_set_fork_status(runner15, CK_NOFORK);
    srunner_run_all(runner15, CK_NORMAL);
    no_failed15 = srunner_ntests_failed(runner15);
    srunner_free(runner15);
*/
    int failures = (!no_failed1 && !no_failed2/ && !no_failed3/* && !no_failed4 && !no_failed5 && !no_failed6
                    && !no_failed7 && !no_failed8 && !no_failed9 && !no_failed10 && !no_failed11
                    && !no_failed12 && !no_failed13 && !no_failed14 && !no_failed15*/) ? 0 : 1;
    return (failures == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
