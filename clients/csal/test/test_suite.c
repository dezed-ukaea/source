
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "test_suite.h"



int test_case_init( test_case_t* self, test_suite_t* owner )
{
    int err = 0;
    
    memset( self, 0, sizeof( test_case_t ) );

    self->test_suite = owner;

    return err;
}

int test_case_name_set( test_case_t* self, const char* pszname )
{
    int err =0;

    strncpy( self->szname, pszname, 255 );

    return err;
}

char* test_case_name_get( test_case_t* self )
{
    return self->szname;
}

int test_case_run( test_case_t* self )
{
    int err = 0;

    printf( "\n" );

    if( self->f )
        self->f( self );
 
    printf( "Test Case : %s : %d/%d passed\n",self->szname,  self->npassed, self->npassed + self->nfailed );
    printf( "Test Case : %s : %d/%d failed\n", self->szname, self->nfailed, self->npassed + self->nfailed );
    
    return err;
}

int test_case_finish( test_case_t* self )
{
    int err = 0;

    free( self->test_results );

    return err;
}

int test_suite_add_test_case( test_suite_t* self, const char* pszname, TEST_CASE_FUNCTION f)
{
    int err = 0;

    if( self->processing_flags & TEST_SUITE_PROC_RUN_TESTS )
        setjmp( self->abort_jmp_buf );

    if( self->processing_flags & TEST_SUITE_PROC_RUN_TESTS )
    {
        test_case_t*  tc = NULL;

        self->ntestcases++;
        self->testcases = (test_case_t*)realloc( self->testcases, sizeof(test_case_t) * self->ntestcases );

        tc = self->testcases + self->ntestcases-1;

        test_case_init( tc, self );
        test_case_name_set( tc, pszname );
        tc->f = f;
#if 0
        test_case_run( tc );
#endif
    }

    return err;
}

int test_suite_run_all( test_suite_t* self )
{
    int err = 0;

    size_t i = 0;
    for( i = 0; i < self->ntestcases; ++i )
    {

        if( self->processing_flags & TEST_SUITE_PROC_RUN_TESTS )
            setjmp( self->abort_jmp_buf );

        if( self->processing_flags & TEST_SUITE_PROC_RUN_TESTS )
        {
            test_case_t* tc = self->testcases + i;

            test_suite_run_test_case( self, tc );
        }

    }
    return err;
}

int test_suite_run_test_case( test_suite_t* self, test_case_t* tc )
{
    int err = 0;

    self->ncasesrun++;
    test_case_run( tc );

    return err;
}

int test_suite_run_name( test_suite_t* self, const char* psztestname )
{
    int err = 0;
    size_t i = 0;

    if( self->processing_flags & TEST_SUITE_PROC_RUN_TESTS )
            setjmp( self->abort_jmp_buf );


    for( i = 0; i < self->ntestcases && self->processing_flags & TEST_SUITE_PROC_RUN_TESTS; ++i )
    {
        test_case_t* tc = self->testcases + i;
        if( 0 == strcmp( tc->szname, psztestname ) )
            test_suite_run_test_case( self, tc );
    }




    return err;
}

int test_suite_init( test_suite_t* self, unsigned int ctrl_flags )
{
    self->ctrl_flags = ctrl_flags;

    self->processing_flags = TEST_SUITE_PROC_NONE;
    self->processing_flags |= TEST_SUITE_PROC_RUN_TESTS;

    self->ncasesrun = 0;
    self->ntestcases = 0;
    self->testcases = NULL;

    memset( &(self->abort_jmp_buf), 0, sizeof( jmp_buf ) );

    return 0;
}

int test_case_abort( test_case_t* self )
{
    longjmp( self->test_suite->abort_jmp_buf, 1 );
}

static int _test_case_passed( test_case_t* self, int res, const char* expr, const char* pszfile, unsigned int lineno )
{
    int err = 0;

    self->npassed++;

    if( self->test_suite->ctrl_flags & TEST_SUITE_CTRL_REPORT_PASS )
        printf( "%s(%d) : %s : %s\n", pszfile, lineno, expr, "PASS" );

    return err;
}


int test_result_init( test_result_t* self, int passed, const char* pszexpr, const char* pszfile, unsigned int lineno )
{
    int err = 0;

    self->passed = passed;
    strcpy( self->szexp, pszexpr );
    strcpy( self->szfile, pszfile );
    self->lineno = lineno;

    return err;
}

static int _test_case_failed( test_case_t* self, int res, const char* expr, const char* pszfile, unsigned int lineno )
{
    int err = 0;

    self->nfailed++;

    printf( "%s(%d) : %s : %s\n", pszfile, lineno, expr, "FAIL" );

    if( !res && self->test_suite->ctrl_flags & TEST_SUITE_CTRL_EXIT_ON_FAIL )
    {
        self->test_suite->processing_flags &= ~TEST_SUITE_PROC_RUN_TESTS;
        test_case_abort( self );
    }

    return err;
}



int test_case_test( test_case_t* self, int res, const char* expr, const char* file, unsigned int lineno )
{
    test_result_t* tr = NULL;
    self->test_results = (test_result_t*)realloc( self->test_results, sizeof( test_result_t ) * (self->nresults+1) );
    tr = self->test_results + self->nresults;

    test_result_init( tr, res, expr, file, lineno );
   
    self->nresults++;

    if( res )
        _test_case_passed( self, res, expr, file, lineno );
    else
        _test_case_failed( self, res, expr, file, lineno );

    return 0;
}

int test_case_equal_int( test_case_t* self, int val, int expected, const char* pszfile, unsigned int lineno )
{
    int res = (val == expected);

    char buffer[ 512];

    sprintf( buffer, "%d == %d", val, expected );

    if( res )
        _test_case_passed( self, res, buffer, pszfile, lineno );
    else
        _test_case_failed( self, res, buffer, pszfile, lineno );

    return 0;
}

int test_case_equal_float( test_case_t* self, float val, float expected, const char* pszfile, unsigned int lineno )
{
    int res = (val == expected);

    char buffer[ 512];

    sprintf( buffer, "%f == %f", val, expected );

    if( res )
        _test_case_passed( self, res, buffer, pszfile, lineno );
    else
        _test_case_failed( self, res, buffer, pszfile, lineno );

    return 0;
}

int test_case_equal_double( test_case_t* self, double val, double expected, const char* pszfile, unsigned int lineno )
{
    int res = (val == expected);

    char buffer[ 512];

    sprintf( buffer, "%f == %f", val, expected );

    if( res )
        _test_case_passed( self, res, buffer, pszfile, lineno );
    else
        _test_case_failed( self, res, buffer, pszfile, lineno );

    return 0;
}


int test_suite_finish( test_suite_t* self )
{
    size_t i = 0;
    size_t j = 0;

    int npassed=0;
    int nfailed=0;

    printf( "\n" );

    if( self->ctrl_flags & TEST_SUITE_CTRL_SUMMARY )
        printf( "Summary\n");

    for( i = 0; i < self->ntestcases; ++i )
    {
        test_case_t* tc = self->testcases + i;
    
        npassed += tc->npassed;
        nfailed += tc->nfailed;

        if( tc->nfailed && self->ctrl_flags & TEST_SUITE_CTRL_SUMMARY )
        {
            printf( "\n" );
            for( j = 0; j < tc->nresults; ++j )
            {
                test_result_t* tr = tc->test_results + j;
                if( 0 == tr->passed )
                {
                    printf( "%s(%d) : %s : %s : FAIL\n", tr->szfile, tr->lineno, tc->szname, tr->szexp );
                }
            }
        }

        test_case_finish( tc );
    }

    printf( "\n" );
    printf( "%d/%d tests failed\n", nfailed, nfailed+npassed );
    printf( "%d/%d tests passed\n", npassed, nfailed+npassed );
    printf( "%d/%d test cases\n", self->ncasesrun, self->ntestcases );

    free( self->testcases );

    return 0;
}


