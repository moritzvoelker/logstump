#include <fstream>
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
    initLogstump(logfiles, false, true, DEBUG);

    error("This should be red.");
    warn("This should be yellow.");
    info("This should be standard.");
    debug("This should be green.");

    closeLogstump();
}

void testLogMode()
{
    vector<string*> logfiles = { };
    initLogstump(logfiles, false, true, ERROR);

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