cmake_minimum_required(VERSION 3.24)
project(Portfolio)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(Portfolio main.cpp Data/IDataSource.h Data/CareerProject.h Data/ExternalLink.h Data/CareerExperience.h Data/Json/JsonDataSource.cpp Data/Json/JsonDataSource.h)

target_link_libraries(Portfolio PRIVATE nlohmann_json::nlohmann_json)