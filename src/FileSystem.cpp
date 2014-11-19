#include "FileSystem.h"
#include <cstdio>

FileSystem* FileSystem::m_fileSystem = nullptr;

FileSystem::FileSystem()
{

}

FileSystem::~FileSystem()
{

}

std::string FileSystem::GetCurrentWorkingDir()
{
    char* tmp = getcwd(m_buffer, sizeof(m_buffer));
    std::string currentWorkDir = "";
    printf("PATH=%s\n", tmp);
    if (tmp)
    {
        currentWorkDir = tmp;
    }
    return currentWorkDir;
}

FileSystem* FileSystem::Instance()
{
    if(m_fileSystem == nullptr)
    {
        m_fileSystem = new FileSystem();
    }
    return m_fileSystem;
}

