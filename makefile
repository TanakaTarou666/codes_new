CXX = g++
CXXFLAGS = -O3 -mtune=native -march=native -mfpmath=both

# ターゲットと依存関係を指定
math_utils = src/math_utils/vector.cxx src/math_utils/matrix.cxx src/math_utils/sparse_matrix.cxx src/math_utils/tensor.cxx src/math_utils/dsd_tensor.cxx

normal_recom = src/recom_system_base/recom.cxx $(math_utils)
tfc_recom = src/recom_system_base/tfc_recom.cxx src/recom_system_base/recom.cxx $(math_utils)

.out/mf: src/recom_methods/mf.cxx main_recom/mf_main.cxx $(normal_recom) 
	$(CXX) $(CXXFLAGS) $^ -o $@
.out/tfcfm: src/recom_methods/tfcfm.cxx main_recom/tfcfm_main.cxx $(tfc_recom) 
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f .out/tfcfm

.PHONY: clean
