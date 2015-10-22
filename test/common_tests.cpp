#include "gtest/gtest.h"
#include "humblelogging/api.h"

using namespace humble::logging;

HUMBLE_LOGGER(HL, "CommonTests");

TEST(CommonTest, AllShouldLog) {
  Factory::getInstance().setConfiguration(new SimpleConfiguration(LogLevel::All));
  EXPECT_TRUE(HL.wouldLog(LogLevel::Trace));
  EXPECT_TRUE(HL.wouldLog(LogLevel::Debug));
  EXPECT_TRUE(HL.wouldLog(LogLevel::Info));
  EXPECT_TRUE(HL.wouldLog(LogLevel::Warn));
  EXPECT_TRUE(HL.wouldLog(LogLevel::Error));
  EXPECT_TRUE(HL.wouldLog(LogLevel::Fatal));
}

TEST(CommonTest, ErrorShouldLog) {
  Factory::getInstance().setConfiguration(new SimpleConfiguration(LogLevel::Error));
  EXPECT_TRUE(HL.wouldLog(LogLevel::Trace) == false);
  EXPECT_TRUE(HL.wouldLog(LogLevel::Debug) == false);
  EXPECT_TRUE(HL.wouldLog(LogLevel::Info) == false);
  EXPECT_TRUE(HL.wouldLog(LogLevel::Warn) == false);
  EXPECT_TRUE(HL.wouldLog(LogLevel::Error));
  EXPECT_TRUE(HL.wouldLog(LogLevel::Fatal));
}
