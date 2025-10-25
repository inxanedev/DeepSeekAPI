# DeepSeekAPI

This repository contains a C++ library that provides an simple, barebones interface to the DeepSeek API.  
It is meant to be compiled as a static library and used in other C++ projects.  

It uses `libcurl` for networking, and `nlohmann-json` for JSON support.

# docs
You can view the Doxygen documentation here:  
[Documentation](https://inxanedev.github.io/deepseekapi/docs/classinx_1_1_deep_seek_1_1_a_p_i.html)  
Please note however, it might not always be up to date, since I have to do this manually.  
It's always better to use IntelliSense to view the documentation while coding.

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