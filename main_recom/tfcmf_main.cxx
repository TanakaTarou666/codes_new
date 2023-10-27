#include "../src/recom_methods/tfcmf.h"

int main() {
    double latent_dimensions[] = {5.0};
    double reg_parameters[] = {0.01, 0.02};
    double learning_rates[] = {0.001, 0.005};
    int cluster_size[] = {5};
    double fuzzifier_em[] = {1.001};
    double fuzzifier_Lambda[] = {1000};

    for (int mv = start_missing_valu; mv <= end_missing_valu; mv += step_missing_valu) {
        TFCMF recom(mv);
        recom.input(input_data_name);
        for (double ld : latent_dimensions) {
            for (double rp : reg_parameters) {
                for (double lr : learning_rates) {
                    for (int c : cluster_size) {
                        for (double em : fuzzifier_em) {
                            for (double lambda : fuzzifier_Lambda) {
                                recom.set_parameters(ld, c, em, lambda, rp, lr);
                            }

                            for (int i = 0; i < missing_pattern; i++) {
                                // データを欠損
                                recom.revise_missing_values();
                                recom.train();
                                recom.calculate_mae(i);
                                recom.calculate_roc(i);
                            }
                            // 指標値の計算 シード値のリセット
                            recom.precision_summury();
                        }
                    }
                }
            }
        }
    }

    return 0;
}