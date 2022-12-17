#pragma once
#include "ExecUtils.h" //TODO: Warning to prevent circular dependencies?

/**
 * @brief Determines the SHA256 hash of a program (NOTE: REQUIRES sha256sum TO BE INSTALLED!)
 * 
 * @param module The llvm::Module where codegen has occurred
 * @return std::string the SHA256 hash of the program
 */
std::string llvmIrToSHA256(llvm::Module *module)
{
    //Create a random file name
    std::string fileName = std::tmpnam(nullptr);

    //Create an LLVM Stream to the file 
    std::error_code ec;
    llvm::raw_fd_ostream irStream(fileName, ec);

    //Write the IR to the stream
    module->print(irStream, nullptr);
    irStream.flush();

    //Exec sha256sum on the file
    std::string ans = exec("sha256sum " + fileName);

    //Cut off the filename so we just have the hash
    std::string hash = ans.substr(0, ans.find(" "));

    return hash; 
}