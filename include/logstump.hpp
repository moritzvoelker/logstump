/* 
MIT License

Copyright (c) 2021 moritzvoelker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __LOGSTUMP_HPP
#define __LOGSTUMP_HPP

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace stump
{
    /**
     * The LogMode is used to indicate the level of logging.
     * The functions error(), warn(), info() and debug() only take any effect, if the logMode is set to same or higher level.
     * LogMode ERROR only shows error messages, LogMode DEBUG shows all possible messages.
     * */
    typedef enum LogMode
    {
        ERROR,
        WARN,
        INFO,
        DEBUG
    } LogMode;

    /**
     * Logstump is used as a global container for the logging configuration.
     * One has to call initLogstump() to properly initalize it before calling any logging functions.
     * This struct doesn't have to be directly touched in order to use logstump.
     * */
    struct Logstump
    {
        std::vector<std::ostream *> files;
        LogMode logMode;
        bool colorCoding;
        char const *colorCodes[5];
        char const *prefixes[4];
    } logstump;

    /**
    * Initializes logging.
    * param logfiles contains a vector of paths to logfiles
    * param logToConsole determins if logging should also go to console
    * param colorCoding determins if the output shall be color coded (applies to all outputs, both files and console)
    * param logMode determins the logging level
    * */
    void initLogstump(std::vector<std::string *> logfiles, bool logToConsole, bool colorCoding, LogMode logMode);
    /**
     * This method can be used to change the color codes for the color coding of the messages.
     * param error contains the color code for the error message
     * param warn contains the color code for the warn message
     * param info contains the color code for the info message
     * param debug contains the color code for the debug message
     * param reset contains the color code to reset the color to normal. This is printed after every message.
     * */
    void setColorCodes(char const *error, char const *warn, char const *info, char const *debug, char const *reset);
    /**
     * Same but with an array.
     * param colorCodes containes the 5 color codes in the same order as in the other overloading of this function
     * */
    void setColorCodes(char const *colorCodes[5]);
    /**
     * This method can be used to change the prefixes of the messages.
     * param error contains the prefix for the error message
     * param warn contains the prefix for the warn message
     * param info contains the prefix for the info message
     * param debug contains the prefix for the debug message
     * */
    void setPrefixes(char const *error, char const *warn, char const *info, char const *debug);
    /**
     * Same but with an array.
     * param prefixes containes the 4 prefixes in the same order as in the other overloading of this function
     * */
    void setPrefixes(char const *prefixes[4]);
    /**
     * The generic logging method to log with printf style formatting.
     * This will take a prefix and a message and print them concatenated with a newline at the end.
     * If color coding is enabled the reset code will be printed before the newline.
     * This function is generally not intended to be used by someone logging, but it doesn't break anything if it is.
     * param prefix will be prefixed to the message
     * param msg is the message to format and log
     * param args is a list of printf style arguments to be formatted into the message (not the prefix)
     * */
    template <class... Args>
    void log(std::string prefix, std::string msg, Args &&...args);
    /**
     * This function will call log() with the error prefix if the logging level is equal or greater than ERROR.
     * If color coding is enabled, the error code will be printed before the prefix.
     * param msg is the message to format and log
     * param args is a list of printf style arguments to be formatted into the message (not the prefix)
     * */
    template <class... Args>
    void error(std::string msg, Args &&...args);
    /**
     * This function will call log() with the warn prefix if the logging level is equal or greater than WARN.
     * If color coding is enabled, the warn code will be printed before the prefix.
     * param msg is the message to format and log
     * param args is a list of printf style arguments to be formatted into the message (not the prefix)
     * */
    template <class... Args>
    void warn(std::string msg, Args &&...args);
    /**
     * This function will call log() with the info prefix if the logging level is equal or greater than INFO.
     * If color coding is enabled, the info code will be printed before the prefix.
     * param msg is the message to format and log
     * param args is a list of printf style arguments to be formatted into the message (not the prefix)
     * */
    template <class... Args>
    void info(std::string msg, Args &&...args);
    /**
     * This function will call log() with the debug prefix if the logging level is equal or greater than DEBUG.
     * If color coding is enabled, the debug code will be printed before the prefix.
     * param msg is the message to format and log
     * param args is a list of printf style arguments to be formatted into the message (not the prefix)
     * */
    template <class... Args>
    void debug(std::string msg, Args &&...args);

    void initLogstump(std::vector<std::string *> logfiles, bool logToConsole, bool colorCoding, LogMode logMode)
    {

        for (std::string *path : logfiles)
        {
            std::ofstream *file = new std::ofstream();
            file->open(*path);
            logstump.files.push_back(file);
        }

        if (logToConsole)
        {
            logstump.files.push_back(&std::cout);
        }

        logstump.colorCoding = colorCoding;

        setColorCodes("\033[31m", "\033[33m", "", "\033[32m", "\033[0m");
        setPrefixes("Error: ", "Warning: ", "Info: ", "Debug: ");

        logstump.logMode = logMode;
    }

    void closeLogstump()
    {
        for (std::ostream *file : logstump.files)
        {
            if (file != &std::cout)
            {
                ((std::ofstream*)file)->close();
                delete file;
            }
        }
        logstump.files.clear();
    }

    void setColorCodes(char const *error, char const *warn, char const *info, char const *debug, char const *reset)
    {
        char const *colorCodes[5] = {error, warn, info, debug, reset};
        setColorCodes(colorCodes);
    }

    void setColorCodes(char const *colorCodes[5])
    {
        logstump.colorCodes[0] = colorCodes[0];
        logstump.colorCodes[1] = colorCodes[1];
        logstump.colorCodes[2] = colorCodes[2];
        logstump.colorCodes[3] = colorCodes[3];
        logstump.colorCodes[4] = colorCodes[4];
    }

    void setPrefixes(char const *error, char const *warn, char const *info, char const *debug)
    {
        char const *prefixes[4] = {error, warn, info, debug};
        setPrefixes(prefixes);
    }

    void setPrefixes(char const *prefixes[4])
    {
        logstump.prefixes[0] = prefixes[0];
        logstump.prefixes[1] = prefixes[1];
        logstump.prefixes[2] = prefixes[2];
        logstump.prefixes[3] = prefixes[3];
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-security"

    template <class... Args>
    void log(std::string prefix, std::string msg, Args &&...args)
    {
        size_t formattedSize = snprintf(NULL, 0, msg.c_str(), args...);
        char *buffer = (char *)malloc(formattedSize);
        snprintf(buffer, formattedSize, msg.c_str(), args...);

        for (std::ostream *file : logstump.files)
        {
            *file << prefix << buffer << (logstump.colorCoding ? logstump.colorCodes[4] : "") << std::endl;
        }
        free(buffer);
    }

#pragma clang diagnostic push

    template <class... Args>
    void error(std::string msg, Args &&...args)
    {
        if (logstump.logMode >= ERROR)
        {
            std::stringstream prefix;
            prefix << (logstump.colorCoding ? logstump.colorCodes[0] : "") << "Error: ";
            log(prefix.str(), msg, args...);
        }
    }

    template <class... Args>
    void warn(std::string msg, Args &&...args)
    {
        if (logstump.logMode >= WARN)
        {
            std::stringstream prefix;
            prefix << (logstump.colorCoding ? logstump.colorCodes[1] : "") << "Warning: ";
            log(prefix.str(), msg, args...);
        }
    }

    template <class... Args>
    void info(std::string msg, Args &&...args)
    {
        if (logstump.logMode >= INFO)
        {
            std::stringstream prefix;
            prefix << (logstump.colorCoding ? logstump.colorCodes[2] : "") << "Info: ";
            log(prefix.str(), msg, args...);
        }
    }

    template <class... Args>
    void debug(std::string msg, Args &&...args)
    {
        if (logstump.logMode >= DEBUG)
        {
            std::stringstream prefix;
            prefix << (logstump.colorCoding ? logstump.colorCodes[3] : "") << "Debug: ";
            log(prefix.str(), msg, args...);
        }
    }
}

#endif