cmake_minimum_required(VERSION 3.24)

set(CPM_DOWNLOAD_VERSION 0.36.0)
if(CPM_SOURCE_CACHE)
    set(CPM_DOWNLOAD_LOCATION "${CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
elseif(DEFINED ENV{CPM_SOURCE_CACHE})
    set(CPM_DOWNLOAD_LOCATION "$ENV{CPM_SOURCE_CACHE}/cpm/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
else()
    set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
endif()

if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
    file(DOWNLOAD
            https://github.com/TheLartians/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
            ${CPM_DOWNLOAD_LOCATION}
            )
endif()


project(Portfolio)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
include(${CPM_DOWNLOAD_LOCATION})
CPMAddPackage(
        NAME drogon
        VERSION 1.7.5
        GITHUB_REPOSITORY drogonframework/drogon
        GIT_TAG v1.7.5
)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(Portfolio main.cpp Data/IDataSource.h Data/CareerProject.h Data/ExternalLink.h Data/CareerExperience.h Data/Json/JsonDataSource.cpp Data/Json/JsonDataSource.h Data/IDataSourceExporter.h Data/Json/JsonDataSourceExporter.cpp Data/Json/JsonDataSourceExporter.h Data/Json/JsonValues.h Web/IServer.h Web/Drogon/DrogonServer.h Web/Drogon/DrogonServer.cpp Web/Drogon/PortfolioController.cpp Web/Drogon/PortfolioController.h Web/Drogon/PortfolioPlugin.h Web/Drogon/PortfolioPlugin.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE drogon)
target_link_libraries(Portfolio PRIVATE nlohmann_json::nlohmann_json)