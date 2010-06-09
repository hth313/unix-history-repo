-- This file is generated by SWIG. Do *not* modify by hand.
--

with Interfaces.C;


package LLVM_Analysis is

   -- LLVMVerifierFailureAction
   --
   type LLVMVerifierFailureAction is (
      LLVMAbortProcessAction,
      LLVMPrintMessageAction,
      LLVMReturnStatusAction);

   for LLVMVerifierFailureAction use
     (LLVMAbortProcessAction => 0,
      LLVMPrintMessageAction => 1,
      LLVMReturnStatusAction => 2);

   pragma Convention (C, LLVMVerifierFailureAction);

   type LLVMVerifierFailureAction_array is
     array (Interfaces.C.size_t range <>)
            of aliased LLVM_Analysis.LLVMVerifierFailureAction;

   type LLVMVerifierFailureAction_view is access all
     LLVM_Analysis.LLVMVerifierFailureAction;

end LLVM_Analysis;
