
#include "../include/CoreFunctionResolver.h"
#include "../include/Atom/Keyword.h"

namespace Mefodij {

    CoreFunctionResolver::CoreFunctionResolver(): storage{}
    {
        setFunction(Keyword::Function::inArray,
            &CoreFunctionResolver::functionInArray,
            {
                {0, {Keyword::Function::Parameters::elem, nullptr, false}},
                {1, {Keyword::Function::Parameters::array, nullptr, false}}
            }
        );
    }

    bool CoreFunctionResolver::hasFunction(wstring name)
    {
        return storage.count(name) != 0;
    }

    CoreFunctionResolver::methodParams & CoreFunctionResolver::getParams(wstring name)
    {
        return storage.at(name).second;
    }

    CoreFunctionResolver::methodPtr CoreFunctionResolver::getPointer(wstring name)
    {
        return storage.at(name).first;
    }

    void CoreFunctionResolver::setFunction(
        wstring name, 
        CoreFunctionResolver::methodPtr method,
        CoreFunctionResolver::methodParams params
    )
    {
        storage.insert({name, {method, params}});
    }

    void CoreFunctionResolver::resolveCall(
        wstring name, 
        shared_ptr<Context> & stack, 
        shared_ptr<Atom> & result
    )
    {
        if (!storage.count(name)) {
            throw runtime_error(
                "Core function '" 
                + Mefodij::Tools::wideStrToStr(name) 
                + "' does not exist."
            );
        }

        auto ptr = getPointer(name);
        (this->*ptr)(stack, result);
    }

    void CoreFunctionResolver::functionInArray(shared_ptr<Context> & stack, shared_ptr<Atom> & result)
    {
        shared_ptr<Atom> element = stack->getVar(Keyword::Function::Parameters::elem);
        shared_ptr<Atom> array = stack->getVar(Keyword::Function::Parameters::array);
        bool found = false;

        for (const auto & kv : array->getArray()) {
            if (kv.second->getType() != element->getType()) {
                continue;
            }

            if (kv.second->getType() == Keyword::typeInt) {
                if (kv.second->getInt() == element->getInt()) {
                    found = true;
                    break;
                }
            }

            if (kv.second->getType() == Keyword::typeDouble) {
                if (kv.second->getDouble() == element->getDouble()) {
                    found = true;
                    break;
                }
            }

            if (kv.second->getType() == Keyword::typeString) {
                if (kv.second->getString() == element->getString()) {
                    found = true;
                    break;
                }
            }

            if (kv.second->getType() == Keyword::typeBool) {
                if (kv.second->getBool() == element->getBool()) {
                    found = true;
                    break;
                }
            }

            if (kv.second->getType() == Keyword::typeArray) {
                if (kv.second->getArray() == element->getArray()) {
                    found = true;
                    break;
                }
            }

            if (kv.second->getType() == Keyword::typeNull) {
                found = true;
                break;
            }
        }

        result->setBool(found);
    }

}