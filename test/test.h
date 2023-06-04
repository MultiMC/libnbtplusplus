#pragma once

#include <iostream>

// Check the boolean value of an expression
#define TEST_FAILED_MSG(msg) do { std::cerr << "Test failed at " << __FILE__ << ":" << __LINE__ << ": " << std::endl << msg << std::endl << std::flush; } while(false)

#define TS_ASSERT(expr) do { if(!(expr)) { TEST_FAILED_MSG("Condition '" #expr "' failed"); return false; } } while(false)

#define TS_ASSERT_THROWS(expr, EXCEPTION_TYPE) \
do { \
    try { \
        (expr); \
        TEST_FAILED_MSG("Expression '" #expr "' did not throw an '" #EXCEPTION_TYPE"'"); \
        return false; \
    } catch (EXCEPTION_TYPE & e) { \
        return true; \
    } catch(...) { \
        TEST_FAILED_MSG("Expression '" #expr "' threw a different exceptions than expected (" #EXCEPTION_TYPE")"); \
        return false; \
    } \
} while(false)

// Compare the value of an expression evaluation with the given expected value
#define TS_ASSERT_EQUALS(expr, expected) \
do { \
    auto temp = expr; \
    if(temp != expected) \
    { \
        TEST_FAILED_MSG("Expression '" #expr "' does not equal expected value '" #expected "', instead, it is: " << temp); \
        return false; \
    } \
} while(false)

#define TS_ASSERT_DIFFERS(expr, expected) \
do { \
    auto temp = expr; \
    if(temp == expected) \
    { \
        TEST_FAILED_MSG("Expression '" #expr "' equals expected value '" #expected "', it is: " << temp); \
        return false; \
    } \
} while(false)

#define TS_ASSERT_LESS_THAN(expr, bound) \
do { \
    auto temp = expr; \
    if(temp >= bound) \
    { \
        TEST_FAILED_MSG("Expression '" #expr "' is greater or equal to expected value '" #bound "', it is: " << temp); \
        return false; \
    } \
} while(false)
