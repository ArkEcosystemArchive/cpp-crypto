#ifndef __GTEST_H__
#define __GTEST_H__

#include <AUnit.h>

#define TEST(category, name) test(category##__##name)

#define ASSERT_EQ(e, a) assertEqual(static_cast<decltype(a)>(e), a)
#define ASSERT_NE(e, a) assertNotEqual(static_cast<decltype(a)>(e), a)
#define ASSERT_STREQ(e, a) assertEqual(static_cast<decltype(a)>(e), a)
#define ASSERT_STRNE(e, a) assertNotEqual(static_cast<decltype(a)>(e), a)
#define ASSERT_STRCASEEQ(e, a) assertStringCaseEqual(static_cast<decltype(a)>(e), a)
#define ASSERT_STRCASENE(e, a) assertStringCaseNotEqual(static_cast<decltype(a)>(e), a)

#define ASSERT_TRUE(x) assertNotEqual(static_cast<unsigned>(x), 0u)
#define ASSERT_FALSE(x) assertEqual(static_cast<unsigned>(x), 0u)

#endif