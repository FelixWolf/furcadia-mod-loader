#include <windows.h>
#include <shlobj.h>
#include <iostream>
#include <filesystem>
#include "path.h"

std::filesystem::path getFurcadiaUserPath()
{
    char path[MAX_PATH];

    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, path)))
    {
        std::filesystem::path userProfilePath = std::filesystem::path(path) / "Furcadia";
        return userProfilePath;
    }
    return {};
}

std::filesystem::path getFurcadiaConfigPath()
{
    char path[MAX_PATH];

    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path)))
    {
        std::filesystem::path configPath = std::filesystem::path(path) / "Dragon's Eye Productions" / "Furcadia";
        return configPath;
    }
    return {};
}

std::filesystem::path getFurcadiaCacheDir()
{
    char path[MAX_PATH];

    if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, 0, path)))
    {
        std::filesystem::path cachePath = std::filesystem::path(path) / "Dragon's Eye Productions" / "Furcadia";
        return cachePath;
    }
    return {};
}