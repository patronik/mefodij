
#include "../include/CoreFunctionResolver.h"
#include "../include/Keyword.h"

namespace Mefodij {

    CoreFunctionResolver::CoreFunctionResolver(): storage{}
    {
        setFunction(Keyword::Function::inArray,
            &CoreFunctionResolver::inArray,
            {
                {0, {Keyword::Function::Parameters::elem, nullptr, false}},
                {1, {Keyword::Function::Parameters::array, nullptr, false}}
            }
        );

        setFunction(Keyword::Function::sortArray,
            &CoreFunctionResolver::sortArray,
            {
                {0, {Keyword::Function::Parameters::array, nullptr, true}},
                {1, {Keyword::Function::Parameters::direction, nullptr, false}}
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

    void CoreFunctionResolver::sortArray(shared_ptr<Context> & stack, shared_ptr<Atom> & result)
    {
        shared_ptr<Atom> arrayParam = stack->getVar(Keyword::Function::Parameters::array);
        shared_ptr<Atom> direction = stack->getVar(Keyword::Function::Parameters::direction);

        if (arrayParam->getType() != Keyword::typeArray) {
            throw runtime_error(
                "First argument should be an array, '" + Tools::wideStrToStr(arrayParam->getType()) + "' given."
            );
        }

        if (direction->getType() != Keyword::typeInt) {
            throw runtime_error(
                "Second argument should be an integer, '" + Tools::wideStrToStr(direction->getType()) + "' given."
            );
        }

        if (direction->getInt() != 1 && direction->getInt() != -1) {
            throw runtime_error("Second argument should one of: 1, -1.");
        }
        
        map<wstring, shared_ptr<Atom>, Tools::arrayCmp> tmpArray{};
        vector<pair<wstring, shared_ptr<Atom>>> sortingVector; 

        for (auto elem: arrayParam->getArray()) {
            sortingVector.push_back(elem);
        }

        if (direction->getInt() == 1) {
            sort(sortingVector.begin(), sortingVector.end(), ArrayGTCmp());
            for(int i = 0; i < sortingVector.size(); i++) {
                tmpArray[Tools::to_wstring(i)] = sortingVector[i].second;
            }
        } else {
            sort(sortingVector.begin(), sortingVector.end(), ArrayLTCmp());
            for(int i = 0; i < sortingVector.size(); i++) {
                tmpArray[Tools::to_wstring(i)] = sortingVector[i].second;
            }
        }

        if (tmpArray.size() > 0) {
            arrayParam->setArray(tmpArray);
        }

        result->setNull();
    }

    void CoreFunctionResolver::inArray(shared_ptr<Context> & stack, shared_ptr<Atom> & result)
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