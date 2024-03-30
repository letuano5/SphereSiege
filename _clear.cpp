// compile before committing to delete all data that we saved

#include <bits/stdc++.h>

using namespace std;

#include <filesystem>
#include <iostream>
#include <string>
#include <sys/stat.h>

namespace fs = std::filesystem;

int main()
{
    // Path to the directory
    std::string path
        = "res/save/";

    // This structure would distinguish a file from a
    // directory
    struct stat sb;

    // Looping until all the items of the directory are
    // exhausted
    for (const auto& entry : fs::directory_iterator(path)) {

        // Converting the path to const char * in the
        // subsequent lines
        std::filesystem::path outfilename = entry.path();
        std::string outfilename_str = outfilename.string();
        const char* path = outfilename_str.c_str();

        // Testing whether the path points to a
        // non-directory or not If it does, displays path
        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR)) {
            ofstream inp(path);
            inp.close();
        }
    }
}
