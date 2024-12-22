#include "BismuthErrorHandler.h"
#include "CharStream.h"
#include <sstream>

/******************************************
 * 
 *  Bismuth Error
 * 
 *******************************************/
std::string BismuthError::toString()
{
    if (!token)
        return message; // TODO: DO BETTER and use SymbolUtils::tokenToLineChar
    std::ostringstream e;
    // token->getInputStream()->getSourceName()
    if(!message.empty())
        e << token->getInputStream()->getSourceName() << ":" << token->getLine() << ':' << token->getCharPositionInLine() << ": " << message;
    else 
        e << "at " << token->getInputStream()->getSourceName() << ":" << token->getLine() << ':' << token->getCharPositionInLine();
    return e.str();
}




/******************************************
 * 
 *  Error Chain
 * 
 *******************************************/


ErrorChain * ErrorChain::addErrorAt(antlr4::Token *t)
{
    BismuthError *e = new BismuthError(t, "");
    chain.push_back(e);
    return this; 
}


ErrorChain * ErrorChain::addError(antlr4::Token *t, std::string msg)
{
    BismuthError *e = new BismuthError(t, msg);
    chain.push_back(e);
    return this; 
}

ErrorChain * ErrorChain::addCritWarning(antlr4::Token *t, std::string msg)
{
    BismuthError *e = new BismuthError(t, msg);
    chain.push_back(e);
    return this;
}

std::string ErrorChain::toString()
{
    std::ostringstream e;

    e << ErrorChain::getStringForSeverity(errSev) << " (" << ErrorChain::getStringForErrorType(errType) << "): " << std::endl;

    if (chain.size() == 0)
    {
        e << "UNKNOWN ERROR" << std::endl; // Shouldn't be possible anymore
    }

    for (BismuthError *error : chain)
    {
        e << error->toString() << std::endl;
    }

    return e.str();
}

ErrSev ErrorChain::getSeverity() { return errSev; }








/******************************************
 * 
 *  BismuthErrorHandler
 * 
 *******************************************/
ErrorChain * BismuthErrorHandler::addCompilerError(antlr4::Token *t, std::string msg)
{
    // TODO: where to report error to?
    ErrorChain *e = new ErrorChain(t,
                                    msg + ". This is likely an error with the compiler. Please report it.",
                                    errType,
                                    COMPILER);
    errors.push_back(e);

    return e;
}

ErrorChain * BismuthErrorHandler::addError(antlr4::Token *t, std::string msg)
{
    ErrorChain *e = new ErrorChain(t, msg, errType, ERROR);
    errors.push_back(e);

    return e;
}

ErrorChain * BismuthErrorHandler::addCritWarning(antlr4::Token *t, std::string msg)
{
    ErrorChain *e = new ErrorChain(t, msg, errType, CRITICAL_WARNING);
    errors.push_back(e);

    return e;
}

std::vector<ErrorChain *> & BismuthErrorHandler::getErrors() { return errors; }

std::string BismuthErrorHandler::errorList()
{
    std::ostringstream errList;
    for (ErrorChain *e : errors)
    {
        errList << e->toString() << std::endl;
    }
    errList << "Number of Errors: " << errors.size() << std::endl;

    return errList.str();
}


bool BismuthErrorHandler::hasErrors(int errorFlags)
{
    // If no flags provided, then return if we have any
    if (!errorFlags)
        return !errors.empty();

    for (ErrorChain *err : errors)
    {
        std::cerr << err->getSeverity() << " & " << errorFlags << std::endl;
        if (err->getSeverity() & errorFlags)
            return true;
    }

    return false; //! errors.empty();
}
