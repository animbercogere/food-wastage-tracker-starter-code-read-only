#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "../../food_wastage_tracker_backend.h"
#include "../cppaudit/gtest_ext.h"

using ::testing::HasSubstr;
using ::testing::Not;
using json = nlohmann::json;

crow::query_string CreateQueryString() {
  crow::query_string res{
      "?date=2023-10-21&meal=Dinner&food_name=Pasta&qty_in_oz=5&wastage_reason="
      "Too+much+left+overs&disposal_mechanism=Donation&cost=4.5"};
  return res;
}

TEST(FoodWastageTrackerBackend, WriteToFile) {
  const std::string kFilename = "tools/settings/data/temp.json";
  FoodWastageTrackerBackend backend{kFilename};
  backend.AddRecord(CreateQueryString());
  ASSERT_TRUE(backend.WriteRecordsToJSONFile());

  FoodWastageTrackerBackend backend2{kFilename};
  ASSERT_TRUE(backend2.LoadRecordsFromJSONFile());
  json records = json::parse(backend2.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 1);
  std::remove(kFilename.c_str());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::UnitTest::GetInstance()->listeners().Append(new SkipListener());
  return RUN_ALL_TESTS();
}
