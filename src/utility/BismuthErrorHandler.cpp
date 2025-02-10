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
    std::ostringstream e;
    auto trace = this->asTrace(); 

    for(auto t : trace)
    {
        e << t << std::endl; 
    }

    return e.str();
}

// WHat if we could have recursive types to make trees
// easier. Eg, vector<....<vector<std::string>>
// What would that look like? 
std::vector<std::string> BismuthError::asTrace() 
{
    std::vector<std::string> ans; 

    if(errorType != COMBO)
    {
        ans.push_back(
            BismuthError::getStringForSeverity(errorSeverity) + " (" + BismuthError::getStringForErrorType(errorType) + "): "
        );
    }
    
    for (auto [token, message] : trace)
    {

        // What if we could write this like: 
        /*
        match 
            | !token => 
            | ...

        I guess we kinda have that with select in bismuth... but not quite as pattern-matchey 
        */
        if(!token)
        {

            ans.push_back(message); 
            continue; 
        }

        std::ostringstream e;
        if(!message.empty())
        {
            e << token->getInputStream()->getSourceName() << ":" << token->getLine() << ':' << token->getCharPositionInLine() << ": " << message; 
            ans.push_back(e.str());
            continue; 
        }

        
        e << "at " << token->getInputStream()->getSourceName() << ":" << token->getLine() << ':' << token->getCharPositionInLine();
        ans.push_back(e.str());
    }

    return ans;
}




/******************************************
 * 
 *  Error Chain
 * 
 *******************************************/
ErrorChain * ErrorChain::addErrorAt(antlr4::Token *t)
{
    if(branches.size() > 1)
    {
        ErrorChain * pre = new ErrorChain(*this);
        // this->chain.clear();
        this->error.reset(); 
        this->branches.clear(); 
        this->branches.push_back(pre); 
    }

    if(!this->error)
    {
        this->error = new BismuthError(COMBO, ERROR, t, "");
        return this; 
    }

    (*error)->addTrace(t, "");
    // BismuthError *e = new BismuthError(t, "");
    // chain.push_back(e);
    


    return this; 
}


ErrorChain * ErrorChain::addError(antlr4::Token *t, std::string msg)
{
    if(branches.size() > 1)
    {
        ErrorChain * pre = new ErrorChain(*this);
        // this->chain.clear();
        this->error.reset(); 
        this->branches.clear(); 
        this->branches.push_back(pre); 
    }

    if(!this->error)
    {
        this->error = new BismuthError(COMBO, ERROR, t, msg);
        return this; 
    }

    (*error)->addTrace(t, msg);


    // BismuthError *e = new BismuthError(t, msg);

    // chain.push_back(e);
    return this; 
}

// ErrorChain * ErrorChain::addCritWarning(antlr4::Token *t, std::string msg)
// {
//     // TODO: this doesnt actually track the status of crit warn?
//     BismuthError *e = new BismuthError(t, msg);
//     chain.push_back(e);
//     return this;
// }

ErrorChain * ErrorChain::addBranch(ErrorChain * other)
{
    if(error)//chain.size())
    {
        ErrorChain * pre = new ErrorChain(*this);
        this->error.reset(); 
        this->branches.clear(); 
        this->branches.push_back(pre);  
    }

    branches.push_back(other);
    severity |= other->severity; 
    return this; 
}

std::vector<std::string> ErrorChain::asTrace() 
{
    std::vector<std::string> ans; 
    std::string spacer = "";
    for(unsigned int i = 0; i < this->branches.size(); i++)
    {
        for(std::string s : branches.at(i)->asTrace())
        {
            std::string gen = "";
            for(unsigned int j = 0; j < i; j++)
            {
                gen += "| ";
            }
            gen  += s; 
            ans.push_back(gen);
        }

        if(i > 0)
            spacer += " ┘";
    }

    if(ans.size())
        ans.push_back("|" + spacer);
    else 
        ans.push_back(spacer);
    // if(ans.size())
        // ans.push_back(spacer);

    if(error)
    {
        for(auto s : (*error)->asTrace())
        {
            // if(this->branches.size())
            //     ans.push_back("| " + s);
            // else 
                ans.push_back(s);
        }
    }

    return ans;

}

std::string ErrorChain::toString()
{
    std::ostringstream e;

    for(auto s : this->asTrace())
    {
        e << s << std::endl; 
    }

    return e.str();

    // if(!)

    // e << BismuthError::getStringForSeverity(errSev) << " (" << BismuthError::getStringForErrorType(errType) << "): " << std::endl;

    // if (chain.size() == 0)
    // {
    //     e << "UNKNOWN ERROR" << std::endl; // Shouldn't be possible anymore
    // }

    // for (BismuthError *error : chain)
    // {
    //     e << error->toString() << std::endl;
    // }

    // return e.str();
}

uint32_t ErrorChain::getSeverity() { return severity; }








/******************************************
 * 
 *  BismuthErrorHandler
 * 
 *******************************************/
ErrorChain * BismuthErrorHandler::addCompilerError(antlr4::Token *t, std::string msg)
{
    // TODO: where to report error to?
    ErrorChain *e = new ErrorChain(
        t,
        msg + ". This is likely an error with the compiler. Please report it.",
        errType,
        COMPILER
    );
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




std::string BismuthError::getStringForErrorType(ErrType e)
{
    switch (e)
    {
    case SYNTAX:
        return "SYNTAX";
    case SEMANTIC:
        return "SEMANTIC";
    case CODEGEN:
        return "CODEGEN";
    case COMBO: 
        return "COMBO";
    }
}

std::string BismuthError::getStringForSeverity(ErrSev e)
{
    switch (e)
    {
    case ERROR:
        return "Error";
    case CRITICAL_WARNING:
        return "Critical Warning";
    case WARNING:
        return "Warning";
    case INFO:
        return "Informational";
    case COMPILER:
        return "Compiler Error";
    }
}