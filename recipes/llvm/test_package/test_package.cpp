#include <llvm/Config/llvm-config.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/raw_ostream.h>

#include <cstdlib>

int main()
{
    llvm::LLVMContext context;
    llvm::Module module("test_package", context);
    llvm::IRBuilder<> builder(context);

    llvm::FunctionType *functionType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    llvm::Function *function =
        llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, "answer", module);
    builder.SetInsertPoint(llvm::BasicBlock::Create(context, "entry", function));
    builder.CreateRet(builder.getInt32(42));

    if (llvm::verifyModule(module, &llvm::errs()) || module.getFunction("answer") != function ||
        module.size() != 1)
    {
        return EXIT_FAILURE;
    }

    llvm::outs() << "LLVM " << LLVM_VERSION_STRING << " built module '" << module.getName()
                 << "' with " << module.size() << " function\n";
    return EXIT_SUCCESS;
}
