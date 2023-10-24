
# g++ -o .out/test -O3 -mtune=native -march=native -mfpmath=both src/recom_methods/mf.cxx main_recom/mf_main.cxx src/recom_system_base/recom.cxx src/math_utils/vector.cxx src/math_utils/matrix.cxx src/math_utils/sparse_matrix.cxx 

g++ -o .out/test -O3 -mtune=native -march=native -mfpmath=both src/recom_methods/tfcfm.cxx main_recom/tfcfm_main.cxx src/recom_system_base/tfc_recom.cxx src/recom_system_base/recom.cxx src/math_utils/vector.cxx src/math_utils/matrix.cxx src/math_utils/sparse_matrix.cxx src/math_utils/tensor.cxx src/math_utils/dsd_tensor.cxx 


./.out/test

# g++ -o .out/test -g3 src/recom_methods/mf.cxx main_recom/main_recom.cxx src/recom_system_base/recom.cxx src/math_utils/vector.cxx src/math_utils/matrix.cxx src/math_utils/sparse_matrix.cxx 
# gdb ./.out/test



