QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DCT2.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    DCT2.h \
    include/Eigen/Cholesky \
    include/Eigen/CholmodSupport \
    include/Eigen/Core \
    include/Eigen/Dense \
    include/Eigen/Eigen \
    include/Eigen/Eigenvalues \
    include/Eigen/Geometry \
    include/Eigen/Householder \
    include/Eigen/IterativeLinearSolvers \
    include/Eigen/Jacobi \
    include/Eigen/LU \
    include/Eigen/MetisSupport \
    include/Eigen/OrderingMethods \
    include/Eigen/PaStiXSupport \
    include/Eigen/PardisoSupport \
    include/Eigen/QR \
    include/Eigen/QtAlignedMalloc \
    include/Eigen/SPQRSupport \
    include/Eigen/SVD \
    include/Eigen/Sparse \
    include/Eigen/SparseCholesky \
    include/Eigen/SparseCore \
    include/Eigen/SparseLU \
    include/Eigen/SparseQR \
    include/Eigen/StdDeque \
    include/Eigen/StdList \
    include/Eigen/StdVector \
    include/Eigen/SuperLUSupport \
    include/Eigen/UmfPackSupport \
    include/Eigen/src/Cholesky/LDLT.h \
    include/Eigen/src/Cholesky/LLT.h \
    include/Eigen/src/Cholesky/LLT_LAPACKE.h \
    include/Eigen/src/CholmodSupport/CholmodSupport.h \
    include/Eigen/src/Core/Array.h \
    include/Eigen/src/Core/ArrayBase.h \
    include/Eigen/src/Core/ArrayWrapper.h \
    include/Eigen/src/Core/Assign.h \
    include/Eigen/src/Core/AssignEvaluator.h \
    include/Eigen/src/Core/Assign_MKL.h \
    include/Eigen/src/Core/BandMatrix.h \
    include/Eigen/src/Core/Block.h \
    include/Eigen/src/Core/BooleanRedux.h \
    include/Eigen/src/Core/CommaInitializer.h \
    include/Eigen/src/Core/ConditionEstimator.h \
    include/Eigen/src/Core/CoreEvaluators.h \
    include/Eigen/src/Core/CoreIterators.h \
    include/Eigen/src/Core/CwiseBinaryOp.h \
    include/Eigen/src/Core/CwiseNullaryOp.h \
    include/Eigen/src/Core/CwiseTernaryOp.h \
    include/Eigen/src/Core/CwiseUnaryOp.h \
    include/Eigen/src/Core/CwiseUnaryView.h \
    include/Eigen/src/Core/DenseBase.h \
    include/Eigen/src/Core/DenseCoeffsBase.h \
    include/Eigen/src/Core/DenseStorage.h \
    include/Eigen/src/Core/Diagonal.h \
    include/Eigen/src/Core/DiagonalMatrix.h \
    include/Eigen/src/Core/DiagonalProduct.h \
    include/Eigen/src/Core/Dot.h \
    include/Eigen/src/Core/EigenBase.h \
    include/Eigen/src/Core/ForceAlignedAccess.h \
    include/Eigen/src/Core/Fuzzy.h \
    include/Eigen/src/Core/GeneralProduct.h \
    include/Eigen/src/Core/GenericPacketMath.h \
    include/Eigen/src/Core/GlobalFunctions.h \
    include/Eigen/src/Core/IO.h \
    include/Eigen/src/Core/Inverse.h \
    include/Eigen/src/Core/Map.h \
    include/Eigen/src/Core/MapBase.h \
    include/Eigen/src/Core/MathFunctions.h \
    include/Eigen/src/Core/MathFunctionsImpl.h \
    include/Eigen/src/Core/Matrix.h \
    include/Eigen/src/Core/MatrixBase.h \
    include/Eigen/src/Core/NestByValue.h \
    include/Eigen/src/Core/NoAlias.h \
    include/Eigen/src/Core/NumTraits.h \
    include/Eigen/src/Core/PermutationMatrix.h \
    include/Eigen/src/Core/PlainObjectBase.h \
    include/Eigen/src/Core/Product.h \
    include/Eigen/src/Core/ProductEvaluators.h \
    include/Eigen/src/Core/Random.h \
    include/Eigen/src/Core/Redux.h \
    include/Eigen/src/Core/Ref.h \
    include/Eigen/src/Core/Replicate.h \
    include/Eigen/src/Core/ReturnByValue.h \
    include/Eigen/src/Core/Reverse.h \
    include/Eigen/src/Core/Select.h \
    include/Eigen/src/Core/SelfAdjointView.h \
    include/Eigen/src/Core/SelfCwiseBinaryOp.h \
    include/Eigen/src/Core/Solve.h \
    include/Eigen/src/Core/SolveTriangular.h \
    include/Eigen/src/Core/SolverBase.h \
    include/Eigen/src/Core/StableNorm.h \
    include/Eigen/src/Core/Stride.h \
    include/Eigen/src/Core/Swap.h \
    include/Eigen/src/Core/Transpose.h \
    include/Eigen/src/Core/Transpositions.h \
    include/Eigen/src/Core/TriangularMatrix.h \
    include/Eigen/src/Core/VectorBlock.h \
    include/Eigen/src/Core/VectorwiseOp.h \
    include/Eigen/src/Core/Visitor.h \
    include/Eigen/src/Core/arch/AVX/Complex.h \
    include/Eigen/src/Core/arch/AVX/MathFunctions.h \
    include/Eigen/src/Core/arch/AVX/PacketMath.h \
    include/Eigen/src/Core/arch/AVX/TypeCasting.h \
    include/Eigen/src/Core/arch/AVX512/MathFunctions.h \
    include/Eigen/src/Core/arch/AVX512/PacketMath.h \
    include/Eigen/src/Core/arch/AltiVec/Complex.h \
    include/Eigen/src/Core/arch/AltiVec/MathFunctions.h \
    include/Eigen/src/Core/arch/AltiVec/PacketMath.h \
    include/Eigen/src/Core/arch/CUDA/Complex.h \
    include/Eigen/src/Core/arch/CUDA/Half.h \
    include/Eigen/src/Core/arch/CUDA/MathFunctions.h \
    include/Eigen/src/Core/arch/CUDA/PacketMath.h \
    include/Eigen/src/Core/arch/CUDA/PacketMathHalf.h \
    include/Eigen/src/Core/arch/CUDA/TypeCasting.h \
    include/Eigen/src/Core/arch/Default/ConjHelper.h \
    include/Eigen/src/Core/arch/Default/Settings.h \
    include/Eigen/src/Core/arch/NEON/Complex.h \
    include/Eigen/src/Core/arch/NEON/MathFunctions.h \
    include/Eigen/src/Core/arch/NEON/PacketMath.h \
    include/Eigen/src/Core/arch/SSE/Complex.h \
    include/Eigen/src/Core/arch/SSE/MathFunctions.h \
    include/Eigen/src/Core/arch/SSE/PacketMath.h \
    include/Eigen/src/Core/arch/SSE/TypeCasting.h \
    include/Eigen/src/Core/arch/ZVector/Complex.h \
    include/Eigen/src/Core/arch/ZVector/MathFunctions.h \
    include/Eigen/src/Core/arch/ZVector/PacketMath.h \
    include/Eigen/src/Core/functors/AssignmentFunctors.h \
    include/Eigen/src/Core/functors/BinaryFunctors.h \
    include/Eigen/src/Core/functors/NullaryFunctors.h \
    include/Eigen/src/Core/functors/StlFunctors.h \
    include/Eigen/src/Core/functors/TernaryFunctors.h \
    include/Eigen/src/Core/functors/UnaryFunctors.h \
    include/Eigen/src/Core/products/GeneralBlockPanelKernel.h \
    include/Eigen/src/Core/products/GeneralMatrixMatrix.h \
    include/Eigen/src/Core/products/GeneralMatrixMatrixTriangular.h \
    include/Eigen/src/Core/products/GeneralMatrixMatrixTriangular_BLAS.h \
    include/Eigen/src/Core/products/GeneralMatrixMatrix_BLAS.h \
    include/Eigen/src/Core/products/GeneralMatrixVector.h \
    include/Eigen/src/Core/products/GeneralMatrixVector_BLAS.h \
    include/Eigen/src/Core/products/Parallelizer.h \
    include/Eigen/src/Core/products/SelfadjointMatrixMatrix.h \
    include/Eigen/src/Core/products/SelfadjointMatrixMatrix_BLAS.h \
    include/Eigen/src/Core/products/SelfadjointMatrixVector.h \
    include/Eigen/src/Core/products/SelfadjointMatrixVector_BLAS.h \
    include/Eigen/src/Core/products/SelfadjointProduct.h \
    include/Eigen/src/Core/products/SelfadjointRank2Update.h \
    include/Eigen/src/Core/products/TriangularMatrixMatrix.h \
    include/Eigen/src/Core/products/TriangularMatrixMatrix_BLAS.h \
    include/Eigen/src/Core/products/TriangularMatrixVector.h \
    include/Eigen/src/Core/products/TriangularMatrixVector_BLAS.h \
    include/Eigen/src/Core/products/TriangularSolverMatrix.h \
    include/Eigen/src/Core/products/TriangularSolverMatrix_BLAS.h \
    include/Eigen/src/Core/products/TriangularSolverVector.h \
    include/Eigen/src/Core/util/BlasUtil.h \
    include/Eigen/src/Core/util/Constants.h \
    include/Eigen/src/Core/util/DisableStupidWarnings.h \
    include/Eigen/src/Core/util/ForwardDeclarations.h \
    include/Eigen/src/Core/util/MKL_support.h \
    include/Eigen/src/Core/util/Macros.h \
    include/Eigen/src/Core/util/Memory.h \
    include/Eigen/src/Core/util/Meta.h \
    include/Eigen/src/Core/util/NonMPL2.h \
    include/Eigen/src/Core/util/ReenableStupidWarnings.h \
    include/Eigen/src/Core/util/StaticAssert.h \
    include/Eigen/src/Core/util/XprHelper.h \
    include/Eigen/src/Eigenvalues/ComplexEigenSolver.h \
    include/Eigen/src/Eigenvalues/ComplexSchur.h \
    include/Eigen/src/Eigenvalues/ComplexSchur_LAPACKE.h \
    include/Eigen/src/Eigenvalues/EigenSolver.h \
    include/Eigen/src/Eigenvalues/GeneralizedEigenSolver.h \
    include/Eigen/src/Eigenvalues/GeneralizedSelfAdjointEigenSolver.h \
    include/Eigen/src/Eigenvalues/HessenbergDecomposition.h \
    include/Eigen/src/Eigenvalues/MatrixBaseEigenvalues.h \
    include/Eigen/src/Eigenvalues/RealQZ.h \
    include/Eigen/src/Eigenvalues/RealSchur.h \
    include/Eigen/src/Eigenvalues/RealSchur_LAPACKE.h \
    include/Eigen/src/Eigenvalues/SelfAdjointEigenSolver.h \
    include/Eigen/src/Eigenvalues/SelfAdjointEigenSolver_LAPACKE.h \
    include/Eigen/src/Eigenvalues/Tridiagonalization.h \
    include/Eigen/src/Geometry/AlignedBox.h \
    include/Eigen/src/Geometry/AngleAxis.h \
    include/Eigen/src/Geometry/EulerAngles.h \
    include/Eigen/src/Geometry/Homogeneous.h \
    include/Eigen/src/Geometry/Hyperplane.h \
    include/Eigen/src/Geometry/OrthoMethods.h \
    include/Eigen/src/Geometry/ParametrizedLine.h \
    include/Eigen/src/Geometry/Quaternion.h \
    include/Eigen/src/Geometry/Rotation2D.h \
    include/Eigen/src/Geometry/RotationBase.h \
    include/Eigen/src/Geometry/Scaling.h \
    include/Eigen/src/Geometry/Transform.h \
    include/Eigen/src/Geometry/Translation.h \
    include/Eigen/src/Geometry/Umeyama.h \
    include/Eigen/src/Geometry/arch/Geometry_SSE.h \
    include/Eigen/src/Householder/BlockHouseholder.h \
    include/Eigen/src/Householder/Householder.h \
    include/Eigen/src/Householder/HouseholderSequence.h \
    include/Eigen/src/IterativeLinearSolvers/BasicPreconditioners.h \
    include/Eigen/src/IterativeLinearSolvers/BiCGSTAB.h \
    include/Eigen/src/IterativeLinearSolvers/ConjugateGradient.h \
    include/Eigen/src/IterativeLinearSolvers/IncompleteCholesky.h \
    include/Eigen/src/IterativeLinearSolvers/IncompleteLUT.h \
    include/Eigen/src/IterativeLinearSolvers/IterativeSolverBase.h \
    include/Eigen/src/IterativeLinearSolvers/LeastSquareConjugateGradient.h \
    include/Eigen/src/IterativeLinearSolvers/SolveWithGuess.h \
    include/Eigen/src/Jacobi/Jacobi.h \
    include/Eigen/src/LU/Determinant.h \
    include/Eigen/src/LU/FullPivLU.h \
    include/Eigen/src/LU/InverseImpl.h \
    include/Eigen/src/LU/PartialPivLU.h \
    include/Eigen/src/LU/PartialPivLU_LAPACKE.h \
    include/Eigen/src/LU/arch/Inverse_SSE.h \
    include/Eigen/src/MetisSupport/MetisSupport.h \
    include/Eigen/src/OrderingMethods/Amd.h \
    include/Eigen/src/OrderingMethods/Eigen_Colamd.h \
    include/Eigen/src/OrderingMethods/Ordering.h \
    include/Eigen/src/PaStiXSupport/PaStiXSupport.h \
    include/Eigen/src/PardisoSupport/PardisoSupport.h \
    include/Eigen/src/QR/ColPivHouseholderQR.h \
    include/Eigen/src/QR/ColPivHouseholderQR_LAPACKE.h \
    include/Eigen/src/QR/CompleteOrthogonalDecomposition.h \
    include/Eigen/src/QR/FullPivHouseholderQR.h \
    include/Eigen/src/QR/HouseholderQR.h \
    include/Eigen/src/QR/HouseholderQR_LAPACKE.h \
    include/Eigen/src/SPQRSupport/SuiteSparseQRSupport.h \
    include/Eigen/src/SVD/BDCSVD.h \
    include/Eigen/src/SVD/JacobiSVD.h \
    include/Eigen/src/SVD/JacobiSVD_LAPACKE.h \
    include/Eigen/src/SVD/SVDBase.h \
    include/Eigen/src/SVD/UpperBidiagonalization.h \
    include/Eigen/src/SparseCholesky/SimplicialCholesky.h \
    include/Eigen/src/SparseCholesky/SimplicialCholesky_impl.h \
    include/Eigen/src/SparseCore/AmbiVector.h \
    include/Eigen/src/SparseCore/CompressedStorage.h \
    include/Eigen/src/SparseCore/ConservativeSparseSparseProduct.h \
    include/Eigen/src/SparseCore/MappedSparseMatrix.h \
    include/Eigen/src/SparseCore/SparseAssign.h \
    include/Eigen/src/SparseCore/SparseBlock.h \
    include/Eigen/src/SparseCore/SparseColEtree.h \
    include/Eigen/src/SparseCore/SparseCompressedBase.h \
    include/Eigen/src/SparseCore/SparseCwiseBinaryOp.h \
    include/Eigen/src/SparseCore/SparseCwiseUnaryOp.h \
    include/Eigen/src/SparseCore/SparseDenseProduct.h \
    include/Eigen/src/SparseCore/SparseDiagonalProduct.h \
    include/Eigen/src/SparseCore/SparseDot.h \
    include/Eigen/src/SparseCore/SparseFuzzy.h \
    include/Eigen/src/SparseCore/SparseMap.h \
    include/Eigen/src/SparseCore/SparseMatrix.h \
    include/Eigen/src/SparseCore/SparseMatrixBase.h \
    include/Eigen/src/SparseCore/SparsePermutation.h \
    include/Eigen/src/SparseCore/SparseProduct.h \
    include/Eigen/src/SparseCore/SparseRedux.h \
    include/Eigen/src/SparseCore/SparseRef.h \
    include/Eigen/src/SparseCore/SparseSelfAdjointView.h \
    include/Eigen/src/SparseCore/SparseSolverBase.h \
    include/Eigen/src/SparseCore/SparseSparseProductWithPruning.h \
    include/Eigen/src/SparseCore/SparseTranspose.h \
    include/Eigen/src/SparseCore/SparseTriangularView.h \
    include/Eigen/src/SparseCore/SparseUtil.h \
    include/Eigen/src/SparseCore/SparseVector.h \
    include/Eigen/src/SparseCore/SparseView.h \
    include/Eigen/src/SparseCore/TriangularSolver.h \
    include/Eigen/src/SparseLU/SparseLU.h \
    include/Eigen/src/SparseLU/SparseLUImpl.h \
    include/Eigen/src/SparseLU/SparseLU_Memory.h \
    include/Eigen/src/SparseLU/SparseLU_Structs.h \
    include/Eigen/src/SparseLU/SparseLU_SupernodalMatrix.h \
    include/Eigen/src/SparseLU/SparseLU_Utils.h \
    include/Eigen/src/SparseLU/SparseLU_column_bmod.h \
    include/Eigen/src/SparseLU/SparseLU_column_dfs.h \
    include/Eigen/src/SparseLU/SparseLU_copy_to_ucol.h \
    include/Eigen/src/SparseLU/SparseLU_gemm_kernel.h \
    include/Eigen/src/SparseLU/SparseLU_heap_relax_snode.h \
    include/Eigen/src/SparseLU/SparseLU_kernel_bmod.h \
    include/Eigen/src/SparseLU/SparseLU_panel_bmod.h \
    include/Eigen/src/SparseLU/SparseLU_panel_dfs.h \
    include/Eigen/src/SparseLU/SparseLU_pivotL.h \
    include/Eigen/src/SparseLU/SparseLU_pruneL.h \
    include/Eigen/src/SparseLU/SparseLU_relax_snode.h \
    include/Eigen/src/SparseQR/SparseQR.h \
    include/Eigen/src/StlSupport/StdDeque.h \
    include/Eigen/src/StlSupport/StdList.h \
    include/Eigen/src/StlSupport/StdVector.h \
    include/Eigen/src/StlSupport/details.h \
    include/Eigen/src/SuperLUSupport/SuperLUSupport.h \
    include/Eigen/src/UmfPackSupport/UmfPackSupport.h \
    include/Eigen/src/misc/Image.h \
    include/Eigen/src/misc/Kernel.h \
    include/Eigen/src/misc/RealSvd2x2.h \
    include/Eigen/src/misc/blas.h \
    include/Eigen/src/misc/lapack.h \
    include/Eigen/src/misc/lapacke.h \
    include/Eigen/src/misc/lapacke_mangling.h \
    include/Eigen/src/plugins/ArrayCwiseBinaryOps.h \
    include/Eigen/src/plugins/ArrayCwiseUnaryOps.h \
    include/Eigen/src/plugins/BlockMethods.h \
    include/Eigen/src/plugins/CommonCwiseBinaryOps.h \
    include/Eigen/src/plugins/CommonCwiseUnaryOps.h \
    include/Eigen/src/plugins/MatrixCwiseBinaryOps.h \
    include/Eigen/src/plugins/MatrixCwiseUnaryOps.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    include/Eigen/CMakeLists.txt

QMAKE_CXXFLAGS += -fopenmp
LIBS += -fopenmp

RESOURCES +=