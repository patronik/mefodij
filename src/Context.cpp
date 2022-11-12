#include "../include/Context.h"

namespace Mefodij {

    void Context::setVar(wstring key, shared_ptr<Atom> var) 
    {
        var->setKey(key);

        // remove reference to source variable
        var->setVarRef(nullptr);

        storage[key] = var;
    }

    void Context::setConst(wstring key, shared_ptr<Atom> var)
    {
        var->setIsConst();

        setVar(key, var);
    }

    bool Context::hasOwnVar(wstring key) 
    {
        return storage.count(key) != 0;
    }

    bool Context::hasVar(wstring key) {
        bool hasOwn = storage.count(key) != 0;
        if (hasOwn) {
            return true;
        }
        if (parentContext) {
            return parentContext->hasVar(key);
        }
        return false;
    }

    shared_ptr<Atom> Context::getVar(wstring key) 
    {
        bool hasOwn = storage.count(key) != 0;
        if (hasOwn) {
            return storage.at(key);
        }
        if (parentContext) {
            return parentContext->getVar(key);
        }
        throw runtime_error("Variable '" + Mefodij::Tools::wideStrToStr(key) + "' does not exist.");
    }

    Context * Context::getVarContext(wstring key) 
    {
        bool hasOwn = storage.count(key) != 0;
        if (hasOwn) {
            return this;
        }
        if (parentContext) {
            return parentContext->getVarContext(key);
        }
        return nullptr;
    }

    void Context::setVarToVarAlias(wstring keyFrom, wstring keyTo)
    {
        auto sourceContext = getVarContext(keyFrom);
        if (sourceContext == nullptr) {
            throw runtime_error("Variable '" + Tools::wideStrToStr(keyFrom) + "' does not exist.");
        }

        auto targetContext = getVarContext(keyTo);
        if (targetContext == nullptr) {
            throw runtime_error("Variable '" + Tools::wideStrToStr(keyTo) + "' does not exist.");
        }

        targetContext->setVar(keyTo, sourceContext->getVar(keyFrom));
    }

    void Context::setFunction(wstring key, int pos, map<int, tuple<wstring, shared_ptr<Atom>, bool>> params) 
    {
        return functions.set(key, pos, params);
    }

    bool Context::hasOwnFunction(wstring key) 
    {
        return functions.has(key);
    }

    bool Context::hasFunction(wstring key) 
    {
        bool hasOwn = functions.has(key);
        if (hasOwn) {
            return true;
        }
        if (parentContext) {
            return parentContext->hasFunction(key);
        }
        return false;
    }

    pair<int, map<int, tuple<wstring, shared_ptr<Atom>, bool>>> & Context::getFunction(wstring key) 
    {    
        bool hasOwn = functions.has(key);
        if (hasOwn) {
            return functions.get(key);
        }
        if (parentContext) {
            return parentContext->getFunction(key);
        }
        throw runtime_error("Function '" + Mefodij::Tools::wideStrToStr(key) + "' does not exist.");
    }

    void Context::setParent(shared_ptr<Context> parent)
    {
        parentContext = parent;
    }

    Context::Context(): storage(), functions(), parentContext(nullptr)
    {
    }

}