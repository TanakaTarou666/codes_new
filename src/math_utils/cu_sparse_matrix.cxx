#include "cu_sparse_matrix.h"

Matrix sparseM_transposeM_multiply(const SparseMatrix& lhs,const Matrix rhs){
    Matrix result(lhs.rows(), rhs.rows());

    double alpha           = 1.0;
    double beta            = 0.0;

    int   *dA_csrOffsets, *dA_columns;
    double *dA_values, *dB, *dC;
    cudaMalloc((void**)&dA_csrOffsets, (lhs.rows()+ 1) * sizeof(int));
    cudaMalloc((void**)&dA_columns, lhs.nnz() * sizeof(int));
    cudaMalloc((void**)&dA_values, lhs.nnz() * sizeof(double));
    cudaMalloc((void**)&dB, (rhs.rows() * rhs.cols()) * sizeof(double));
    cudaMalloc((void**)&dC, (lhs.rows() * rhs.rows()) * sizeof(double));

    cudaMemcpy(dA_csrOffsets, lhs.getRowPointers() , (lhs.rows() + 1) * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dA_columns,lhs.getColIndices(), lhs.nnz() * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(dA_values, lhs.getValues(), lhs.nnz() * sizeof(double), cudaMemcpyHostToDevice);
    cudaMemcpy(dB, rhs.getValues(), (rhs.rows() * rhs.cols()) * sizeof(double), cudaMemcpyHostToDevice);

    // CUSPARSE APIs
    cusparseHandle_t     handle = NULL;
    cusparseSpMatDescr_t matA;
    cusparseDnMatDescr_t matB, matC;
    void*                dBuffer    = NULL;
    size_t               bufferSize = 0;
    cusparseCreate(&handle);

    // Create sparse matrix A in CSR format
    cusparseCreateCsr(&matA, lhs.rows(), lhs.cols(), lhs.nnz(),
                      dA_csrOffsets, dA_columns, dA_values,
                      CUSPARSE_INDEX_32I, CUSPARSE_INDEX_32I,
                      CUSPARSE_INDEX_BASE_ZERO, CUDA_R_64F);
    
    // Create dense matrix B
    cusparseCreateDnMat(&matB, rhs.rows(), rhs.cols(), rhs.rows(), dB,
                        CUDA_R_64F, CUSPARSE_ORDER_COL);

    // Create dense matrix C
    cusparseCreateDnMat(&matC, result.rows(), result.cols(), result.rows(), dC,
                        CUDA_R_64F, CUSPARSE_ORDER_COL);

    // Allocate an external buffer if needed
    cusparseSpMM_bufferSize(handle,
                            CUSPARSE_OPERATION_NON_TRANSPOSE,
                            CUSPARSE_OPERATION_NON_TRANSPOSE,
                            &alpha, matA, matB, &beta, matC, CUDA_R_64F,
                            CUSPARSE_SPMM_ALG_DEFAULT, &bufferSize);

    cudaMalloc(&dBuffer, bufferSize);        

    // Execute SpMM
    cusparseSpMM(handle,
                 CUSPARSE_OPERATION_NON_TRANSPOSE,
                 CUSPARSE_OPERATION_NON_TRANSPOSE,
                 &alpha, matA, matB, &beta, matC, CUDA_R_64F,
                 CUSPARSE_SPMM_ALG_DEFAULT, dBuffer);    

    // Destroy matrix/vector descriptors
    cusparseDestroySpMat(matA);
    cusparseDestroyDnMat(matB);
    cusparseDestroyDnMat(matC);
    cusparseDestroy(handle);

    // Device result check
    cudaMemcpy(result.getValues(), dC, (result.rows() * result.cols()) * sizeof(double), cudaMemcpyDeviceToHost);

    // Device memory deallocation
    cudaFree(dBuffer);
    cudaFree(dA_csrOffsets);
    cudaFree(dA_columns);
    cudaFree(dA_values);
    cudaFree(dB);
    cudaFree(dC);                     

    return result;
}