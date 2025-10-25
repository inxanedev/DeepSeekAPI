# DeepSeekAPI

This repository contains a C++ library that provides an simple, barebones interface to the DeepSeek API.  
It is meant to be compiled as a static library and used in other C++ projects.  

It uses `libcurl` for networking, and `nlohmann-json` for JSON support.
# example
```cpp
#include <DeepSeekAPI.h>

using namespace inx::DeepSeek;

API api("your_api_key_here", Model::DeepSeekChat, "You are a helpful assistant.");
api.AddMessage("What's 2 + 2?");

std::string response = api.GetCompletion();
```

# building
Load the project in Visual Studio 2022 and build the project in Release x64.  

# linking to your project
Link against `DeepSeekAPI.lib` and add the include paths.