# CMake file for LLVM variables
# Platform dependent
set(LLVM_DIR /usr/lib/llvm-12) #/lib/llvm-12/bin)#/usr/local/opt/llvm)
set(LLVM_INCLUDE_DIR "${LLVM_DIR}/include")
set(LLVM_LIBS LLVMCore LLVMSupport LLVMIRReader LLVMMC LLVMMCParser LLVMOption)

# llvm_map_components_to_libnames(llvm_libs ${LLVM_TARGETS_TO_BUILD} support core irreader codegen mc mcparser option)
