#ifndef __FILESYSTEM_H_
#define __FILESYSTEM_H_

#ifdef _WIN32
    #include <direct.h>
    #define getcwd _getcwd
#else
    #include <unistd.h>
#endif

#include <climits>
#include <string>

class FileSystem
{
    public:
        ~FileSystem();
        static FileSystem* Instance();
        std::string GetCurrentWorkingDir();

    private:
        static FileSystem* m_fileSystem;
        char m_buffer[PATH_MAX];
        FileSystem();
};

#endif //__FILESYSTEM_H_

