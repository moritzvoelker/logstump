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

#include <string>
#include <vector>

#include "logstump.hpp"

using namespace std;
using namespace stump;

void testOpeningAndWritingToLogfiles()
{
    string path = "testOpeningAndWritingToLogfiles.log";
    vector<string*> logfiles = { &path };
    initLogstump(logfiles, false, false, DEBUG);

    log("Test: ", "Writing to file works like a charm.");

    closeLogstump();
}

void testTogglingConsoleLog()
{
    vector<string*> logfiles = { };
    initLogstump(logfiles, false, false, DEBUG);

    log("Test: ", "This should not be printed.");

    closeLogstump();

    initLogstump(logfiles, true, false, DEBUG);

    log("Test: ", "This should be printed.");

    closeLogstump();
}

void testColorCoding()
{
    vector<string*> logfiles = { };
    initLogstump(logfiles, true, true, DEBUG);

    error("This should be red.");
    warn("This should be yellow.");
    info("This should be standard.");
    debug("This should be green.");

    closeLogstump();
}

void testLogMode()
{
    vector<string*> logfiles = { };
    initLogstump(logfiles, true, true, ERROR);

    error("This should be printed.");
    warn("This should not be printed.");
    info("This should not be printed.");
    debug("This should not be printed.");

    logstump.logMode = WARN;


    error("This should be printed.");
    warn("This should be printed.");
    info("This should not be printed.");
    debug("This should not be printed.");

    logstump.logMode = INFO;

    error("This should be printed.");
    warn("This should be printed.");
    info("This should be printed.");
    debug("This should not be printed.");

    logstump.logMode = DEBUG;

    error("This should be printed.");
    warn("This should be printed.");
    info("This should be printed.");
    debug("This should be printed.");

    closeLogstump();
}

int main()
{
    testOpeningAndWritingToLogfiles();
    testTogglingConsoleLog();
    testColorCoding();
    testLogMode();
}