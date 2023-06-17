#pragma once

#include <string>
#include <vector>
#include <regex>
#include <fmt/core.h>
#include <fmt/format.h>
#include "logging.h"

namespace stringUtils {

    static bool isContains(std::string what, std::string in) {
        if (in.find(what) != -1)
            return true;

        return false;
    }

    static std::vector<std::string> splitArgs(std::string& what, std::string& strPattern) {

        std::regex pattern(strPattern);
        std::smatch matches;
        std::vector<std::string> ret;

        if (std::regex_search(what, matches, pattern)) {
            ret.reserve(matches.size());

            for (int i=1; i < matches.size(); i++) {
                ret.push_back(matches[i]);
            }
        }

        return ret;
    }

    /*static std::vector<std::string> split(std::string what) {
        std::vector<std::string> parts;

        std::size_t start = 0;
        std::size_t curEnd = what.find(" ")

        return parts;
    }*/

}
