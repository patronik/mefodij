
#include "../include/CoreFunctionResolver.h"
#include "../include/Atom/Keyword.h"

namespace Mefody {

    CoreFunctionResolver::CoreFunctionResolver(): storage{}
    {
        setFunction(Keyword::inArrayFunc,
            &CoreFunctionResolver::inArray,
            {
                {0, {Keyword::elemParam, nullptr, false}},
                {1, {Keyword::arrayParam, nullptr, false}}
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
                + Mefody::Tools::wideStrToStr(name) 
                + "' does not exist."
            );
        }

        auto ptr = getPointer(name);
        (this->*ptr)(stack, result);
    }

    void CoreFunctionResolver::inArray(shared_ptr<Context> & stack, shared_ptr<Atom> & result)
    {
        shared_ptr<Atom> element = stack->getVar(Keyword::elemParam);
        shared_ptr<Atom> array = stack->getVar(Keyword::arrayParam);
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