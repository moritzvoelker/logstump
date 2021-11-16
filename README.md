# logstump
This is a little logging libray i write to ease the process of debugging and to get a little more comfortable with c++. It is nothing astonishing, but designed to be easy to setup und lightweight. Feel free to use it, if you trust me ;)

## Usage
I think this is quite self explanatory, but here a short overview.

### Initialization
You have to call initLogstump() before you make any calls to a logging functions. You pass a vector of strings containing the paths to the logfiles, a bool, if you want to also log to console, a bool if your output should be colored, and the LogMode.

### Logging
There are 4 logging levels, ERROR, WARN, INFO and DEBUG. Calls to the accordingly named logging functions only have an effect, if the logging level is equal or higher than the level of the function. This means, that you can write a lot of logging statements, but only print them if necessary. This is particularly usefull for debugging. You can sprinkle your code with debugging logs, which can be enabled for debugging, but don't pollute the normal output of your application.
To set the logging level you only have to change it in the initializaion call (or a define you wrote) and recompile the initializing cpp file.
When a logging function is called, and the logging level matches, it will print out the printf style formatted message with the according prefix. If color coding is enabled, the whole print will be colored accordingly.

### Closing
Since the files you write to are constantly held open, you should close logstump to close those handles.

### Changing the defaults (optional)
The prefixes for the different logs and the color codes defining the colors can be changed with the functions setColorCodes() and setPrefixes(). You can either pass the values one by one or as an array (look in the header to see what values and in which order are expected). Tough, some (I hope) sensible defaults are set, so this is totally optional.

## Example
```
#include <string>
#include <vector>

#include "logstump.hpp"

using namespace std;
using namespace stump;

int main()
{
    string path = "example.log";
    vector<string*> logfiles = { &path };
    initLogstump(logfiles, true, true, DEBUG);

    info("Application started successfully");

    int statusCode = somePotentionallyFailingFunction();

    if (statusCode > 0)
    {
        warn("Status code %i indicates that the function didn't completely fail, but something unexpected happened", statusCode);
    }
    else if (statusCode < 0)
    {
        error("Status code %i indicates that the function encountered a fatal error", statusCode);
    }
    else
    {
        info("Function exited successfully");
    }

    debug("I'm running out of sensible things, so here is the square of the statusCode: %i", statusCode * statusCode);

    closeLogstump();
}
```

## Warranty/License
Though it should be relativley clear, that I'm just some random dude who needed an easy way to do some simple logging, I wonna make clear, that I won't take any guaranties to the working and not segfaulting of this code. But feel free to use it, if you deem it fit (except if are programming some bombs or stuff, I would like you to keep my name out of that).
