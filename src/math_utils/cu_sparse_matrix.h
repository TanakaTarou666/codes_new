#include <cuda_runtime_api.h> // cudaMalloc, cudaMemcpy, etc.
#include <cusparse.h>         // cusparseSpMM
#include "sparse_matrix.h"

Matrix sparseM_transposeM_multiply(const SparseMatrix& lhs,const Matrix rhs);
