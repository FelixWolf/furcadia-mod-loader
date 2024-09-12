#ifndef PATH_H
#define PATH_H
#include <filesystem>

std::filesystem::path getFurcadiaUserPath();
std::filesystem::path getFurcadiaConfigPath();
std::filesystem::path getFurcadiaCacheDir();

#endif