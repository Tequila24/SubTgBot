#pragma once

#include <iostream>
#include <string>
#include "StringUtils.h"

class Log
{
public: // static
    static Log* getInstance() {
            static Log* instance;
            return instance;
        }
    static Log* instance;

public: // methods
    ~Log();
    // cout line
    void logCL(const std::string line);

private:    // methods
    Log();

#define SLog() Log::getInstance()
};
