// This is core/testlib/testlib_test.h
#ifndef testlib_test_h_
#define testlib_test_h_
//:
// \file
// \brief Testing software
// \author Tim Cootes
// \verbatim
//  Modifications
//   Apr 2002, Amitha Perera: Copied from vil_test and moved into testlib in an
//                  attempt to consolidate all the repeated test functionality.
//   Sep.2004, Peter Vanroose: added testlib_test_assert_near_relative().
// \endverbatim

#include <string>
#include <complex>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iomanip>

//: initialise test counters, check test name 'name' exists
void testlib_test_start(const char* name = nullptr);

//: increment number of tests, then output msg
void testlib_test_begin(const char* msg);

//: increment success/failure counters
void testlib_test_perform(bool success);

//: output summary of tests performed
int  testlib_test_summary();

//: output msg, then perform test in expr
void testlib_test_assert(const std::string& msg, bool expr);
//: output msg, then perform test to see if expr is within tol of target
void testlib_test_assert_near(const std::string& msg, double expr,
                              double target = 0, double tol = 1e-12);
//: output msg, then perform test to see if expr is within tol of target
void testlib_test_assert_near(const std::string& msg, std::complex<double> expr,
                              std::complex<double> target, double tol = 1e-12);
//: output msg, then test to see if expr is within relative tol of target
void testlib_test_assert_near_relative(const std::string& msg, double expr,
                                       double target = 0, double tol = 1e-12);
//: output msg, then test to see if expr is within relative tol of target
void testlib_test_assert_near_relative(const std::string& msg,
                                       std::complex<double> expr,
                                       std::complex<double> target,
                                       double tol = 1e-12);
//: output msg, then perform test to see if expr is not within tol of target
void testlib_test_assert_far(const std::string& msg, double expr,
                             double target = 0, double tol = 1e-12);
//: output msg, then perform test to see if expr is not within tol of target
void testlib_test_assert_far(const std::string& msg, std::complex<double> expr,
                             std::complex<double> target, double tol = 1e-12);
//: output msg, then perform test to see if expr is equal to target
void testlib_test_assert_equal(const std::string& msg, long expr, long target);


// move from .cxx file
static int num_test;
static int tests_passed;
static int tests_failed;
static const char* test_name;

void testlib_test_start(const char* name)
{
  num_test = 0;
  tests_passed = 0;
  tests_failed = 0;
  test_name = name;
  std::cout << "-----------------------------------------------------------------------------\n"
           << "Start Testing";
  if (test_name != nullptr) std::cout << ' ' << test_name;
  std::cout << ":\n-----------------------------------------------------------------------------\n" << std::flush;
 }

void testlib_test_begin(const char* msg)
{
  num_test++;
  std::cout <<" Test "<< std::setw(3) << std::right << std::setfill('0') << num_test
           <<": "<< std::setw(53) << std::left << std::setfill(' ')<< msg <<" --> "
           << std::flush;
}

// NOTE: We don't pass in the message (see test_begin) because
//       we want to ensure that the message is printed BEFORE
//       the test is executed.  This way when a test crashes
//       we can tell if it was during a test, or between tests.
void testlib_test_perform(bool success)
{
  if (success) {
    tests_passed++;
    std::cout << "  PASSED\n" << std::flush;
  } else {
    tests_failed++;
    std::cout << "**FAILED**\n" << std::flush;
  }
}

int testlib_test_summary()
{
  std::cout << "-----------------------------------------------------------------------------\n";
  if (test_name) std::cout << test_name << ' ';
  std::cout << "Test Summary: ";
  if (tests_failed > 0)
  {
    if (tests_passed == 0)
      std::cout << "No tests succeeded";
    else if (tests_passed == 1)
      std::cout << "1 test succeeded";
    else
      std::cout << tests_passed <<" tests succeeded";
    if (tests_failed == 1)
      std::cout <<", 1 test failed";
    else
      std::cout <<", "<< tests_failed <<" tests failed";
    std::cout<<"\t\t*****";
  }
  else
  {
    if (tests_passed > 1)
      std::cout << "All "<< tests_passed <<" tests succeeded";
    else if (tests_passed == 1)
      std::cout << "1 test succeeded";
    else
      std::cout << "Test succeeded";
  }
  std::cout << "\n-----------------------------------------------------------------------------\n" << std::flush;
  return tests_failed;
}

void testlib_test_assert(const std::string& msg, bool expr)
{
  std::cout << msg << " - " << std::flush;
  testlib_test_perform(expr);
}

void testlib_test_assert_near(const std::string& msg, double expr, double target, double tol)
{
  std::cout << msg << " should be " << target << ", is " << expr << ", " << std::flush;
  double diff = std::abs(expr - target);
  if (target != 0.0 && diff != 0.0)
    std::cout << "difference " << diff << ", " << std::flush;
  testlib_test_perform(diff <= tol);
}

void testlib_test_assert_near(const std::string& msg, std::complex<double> expr, std::complex<double> target, double tol)
{
  std::cout << msg << " should be " << target << ", is " << expr << ", " << std::flush;
  double diff = std::abs(expr - target);
  if (target != std::complex<double>(0,0) && diff != 0.0)
    std::cout << "difference " << diff << ", " << std::flush;
  testlib_test_perform(diff <= tol);
}

void testlib_test_assert_near_relative(const std::string& msg, double expr, double target, double tol)
{
  std::cout << msg << " should be " << target << ", is " << expr << ", " << std::flush;
  double max = std::abs(target); if (std::abs(expr) > max) max = std::abs(expr);
  if (max==0.0 || target==0.0) max=1.0;
  double diff = std::abs(expr - target) / max;
  if (target != 0.0 && diff != 0.0)
    std::cout << "relative difference " << diff << ", " << std::flush;
  testlib_test_perform(diff <= tol);
}

void testlib_test_assert_near_relative(const std::string& msg, std::complex<double> expr, std::complex<double> target, double tol)
{
  std::cout << msg << " should be " << target << ", is " << expr << ", " << std::flush;
  double max = std::abs(target); if (std::abs(expr) > max) max = std::abs(expr);
  if (max==0.0 || target==std::complex<double>(0,0)) max=1.0;
  double diff = std::abs(expr - target) / max;
  if (target != std::complex<double>(0,0) && diff != 0.0)
    std::cout << "relative difference " << diff << ", " << std::flush;
  testlib_test_perform(diff <= tol);
}

void testlib_test_assert_far(const std::string& msg, double expr, double target, double tol)
{
  std::cout << msg << " should not be " << target << ", is " << expr << ", " << std::flush;
  double diff = std::abs(expr - target);
  if (target != 0.0 && diff != 0.0)
    std::cout << "difference " << diff << ", " << std::flush;
  testlib_test_perform(diff > tol);
}

void testlib_test_assert_far(const std::string& msg, std::complex<double> expr, std::complex<double> target, double tol)
{
  std::cout << msg << " should not be " << target << ", is " << expr << ", " << std::flush;
  double diff = std::abs(expr - target);
  if (target != std::complex<double>(0,0) && diff != 0.0)
    std::cout << "difference " << diff << ", " << std::flush;
  testlib_test_perform(diff > tol);
}

void testlib_test_assert_equal(const std::string& msg, long expr, long target)
{
  std::cout << msg << " should be " << target << ", is " << expr << ", " << std::flush;
  long diff = std::abs(expr - target);
  if (target != 0 && diff != 0)
    std::cout << "difference " << diff << ", " << std::flush;
  testlib_test_perform(diff == 0);
}


#define Assert testlib_test_assert
#define AssertNear testlib_test_assert_near
#define AssertFar testlib_test_assert_far

//: initialise test
#define START(s) testlib_test_start(s)

//: TEST function, s is message, test to see if p==v
#define TEST(s,p,v) \
do { \
  testlib_test_begin(s); \
  testlib_test_perform((p)==(v)); \
} while (false)

//: TEST function, s is message, test to see if p==v for integral values
#define TEST_EQUAL(s,p,v) \
do { \
  testlib_test_begin(s); \
  testlib_test_assert_equal("",p,v); \
} while (false)

//: TEST function, s is message, test to see if p is close to v, tolerance t
#define TEST_NEAR(s,p,v,t) \
do { \
  testlib_test_begin(s); \
  testlib_test_assert_near("",p,v,t); \
} while (false)

//: TEST function, message s, test to see if (p-v)/p is small compared to t
#define TEST_NEAR_REL(s,p,v,t) \
do { \
  testlib_test_begin(s); \
  testlib_test_assert_near_relative("",p,v,t); \
} while (false)

//: TEST function, s is message, test to see if p is far from v, tolerance t
#define TEST_FAR(s,p,v,t) \
do { \
  testlib_test_begin(s); \
  testlib_test_assert_far("",p,v,t); \
} while (false)

//: run x, s is message, then test to see if p==v
#define TEST_RUN(s,x,p,v) \
do { \
  testlib_test_begin(s); \
  x; \
  testlib_test_perform((p)==(v)); \
} while (false)

//: Summarise test
#define SUMMARY() return testlib_test_summary()

//: Run a singleton test function
#define RUN_TEST_FUNC(x) \
  testlib_test_start(#x); x(); return testlib_test_summary()

//: Declare the main function.
#define MAIN( testname ) \
  int testname ## _main(int,char*[])

//: Declare the main function with parameter passing.
#define MAIN_ARGS( testname ) \
  int testname ## _main(int argc, char* argv[])

//: A simplified version of the main test, just in one line.
// Avoids compiler warnings about "unused argc and argv".
#define TESTMAIN( testname ) \
  int testname ## _main(int,char*[]) { START(#testname); testname(); SUMMARY(); }

//: A simplified version of the main test, just in one line.
// This (new) variant is to be used with the (new) CMake GENERATE_TEST_DRIVER()
#define TEST_MAIN( testname ) \
  int testname(int,char*[]) { START(#testname); testname(); SUMMARY(); }

//: A simplified version of the main test, with parameter passing.
#define TESTMAIN_ARGS( testname ) \
  int testname ## _main(int argc, char*argv[]) { START(#testname); testname(argc,argv); SUMMARY(); }

//: A simplified version of the main test, with parameter passing.
// This (new) variant is to be used with the (new) CMake GENERATE_TEST_DRIVER()
#define TEST_MAIN_ARGS( testname ) \
  int testname(int argc, char*argv[]) { START(#testname); testname(argc,argv); SUMMARY(); }

//: Another simplified main test.  To be used in a standalone executable.
#undef TESTLIB_DEFINE_MAIN
#define TESTLIB_DEFINE_MAIN(testname) \
  int main() { START(#testname); testname(); return testlib_test_summary(); }

//: A simplified main test with parameter passing.  To be used in a standalone executable.
#undef TESTLIB_DEFINE_MAIN_ARGS
#define TESTLIB_DEFINE_MAIN_ARGS(testname) \
  int main(int argc, char * argv[]) { START(#testname); testname(argc,argv); SUMMARY(); }

#endif // testlib_test_h_
