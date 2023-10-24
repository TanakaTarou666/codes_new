#include "tfcmf.h"

TFCMF::TFCMF(int missing_count)
    : TFCRecom(missing_count), Recom(missing_count), user_factors_(), item_factors_(), prev_user_factors_(), prev_item_factors_() {
    method_name_ = "TFCMF";
}
