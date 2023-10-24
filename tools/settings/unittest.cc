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
      "?date=2023-10-23&meal=Dinner&food_name=Noodles&qty_in_oz=5&wastage_reason="
      "Too+much+left+overs&disposal_mechanism=Donation&cost=4.5"};
  return res;
}

TEST(FoodWastageTrackerBackend, AddRecords) {
  std::string kFilename = "tools/settings/data/food_wastage_records.json";
  FoodWastageTrackerBackend backend{kFilename};
  backend.LoadRecordsFromJSONFile();
  json records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 6);

  json add_status = json::parse(backend.AddRecord(CreateQueryString()).dump());
  ASSERT_TRUE(add_status.at("success"));

  records = json::parse(backend.GetRecords().dump());
  ASSERT_TRUE(records.at("num_records") == 7);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  testing::UnitTest::GetInstance()->listeners().Append(new SkipListener());
  return RUN_ALL_TESTS();
}
