#include <iomanip>

#define ARTIFICIALITY

const double convergence_criteria = 0.011;
const int missing_pattern = 1;
const int num_initial_values = 1;
const int steps=2000;

#if defined ARTIFICIALITY
const std::string data_name = "artificiality";
const int num_users = 80;
const int num_items = 100;
const double max_value = 4.0;
const int start_missing_valu = 5000;
const int end_missing_valu = 5000;
const int step_missing_valu = 500;
#endif

// 入力するデータの場所
const std::string input_data_name = "data/sparse_" + data_name + "_" + std::to_string(num_users) + "_" + std::to_string(num_items) + ".txt";