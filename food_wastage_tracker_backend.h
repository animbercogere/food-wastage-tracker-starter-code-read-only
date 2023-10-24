#ifndef FOOD_WASTAGE_TRACKER_BACKEND_H_
#define FOOD_WASTAGE_TRACKER_BACKEND_H_

#include <string>

#include "food_wastage_tracker.h"
#include "server_utils/crow_all.h"

// A class to represent the Food wastage tracker backend. This class receives
// and returns CROW framework compatible objects. So when you are implementing
// your own classes to represent concepts like food wastage record and food
// wastage report etc, you'll have to comvert those objects to/from CROW
// objects. Some helper functions have been provided in
// food_wastage_tracker_backend.cc to help you with that conversion.
class FoodWastageTrackerBackend {
public:
  FoodWastageTrackerBackend(const std::string &food_wastage_records_filepath)
      : food_wastage_records_filepath_{food_wastage_records_filepath} {}

  // Reads the food wastage records from the file at
  // food_wastage_records_filepath_, and loads those in memory. If the file is
  // empty, it is a no-op. Returns true if the file was read successfully, else
  // returns false. NOTE: This function should be called right after the object
  // instantiation.
  //
  // Example:
  //  FoodWastageTrackerBackend backend{"path/to/some_file_name.JSON"};
  //  backend.LoadRecordsFromJsonFile();
  bool LoadRecordsFromJSONFile();

  // Writes the food wastage records from the memory to a JSON file at path
  // food_wastage_records_filepath_. Returns true if the file was written
  // successfully, else returns false.
  bool WriteRecordsToJSONFile() const;

  // Add the given food wastage record (in the query_string) to the memory.
  crow::json::wvalue AddRecord(const crow::query_string &query_string);

  // Delete the given food wastage record (in the query_string) from the memory.
  crow::json::wvalue DeleteRecord(const crow::query_string &query_string);

  // Returns all the food wastage records that are stored in the memory.
  crow::json::wvalue GetRecords() const;

  // Generate a report based on all the food wastage records in the memory.
  crow::json::wvalue GetFoodWastageReport() const;

private:
  // File path of the file that stores all the food wastage records in JSON
  // format.
  const std::string &food_wastage_records_filepath_;

  // A top level class object to track the food wastage.
  // TODO: Add a FoodWastageTracker object as a member here. Make sure you stick to the Google's style guide while naming your variable.
};
#endif