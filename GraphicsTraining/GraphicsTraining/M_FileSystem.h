#ifndef __M_FILESYSTEM_H__
#define __M_FILESYSTEM_H__

#include "Module.h"
#include <vector>

class M_FileSystem : public Module
{
public:
	M_FileSystem(const char* name, bool startEnabled = true);
	virtual ~M_FileSystem();

	bool Init() override;
	bool CleanUp() override;

	bool AddPath(const char* pathOrZip, const char* mountPoint = nullptr);
	bool Exist(const char* file)const;
	bool MakeDir(const char* path, const char* mount = nullptr)const;
	bool IsDirectory(const char* path)const;

	const char* GetBaseDir()const;
	void DisplaySearchPaths()const;
	int GetSearchPaths(std::vector<std::string>& paths);

	uint Load(const char* file, char** buffer)const;
	uint Save(const char* file, const void* buffer, uint size)const;

	uint GetFilesOnDir(const char* dir, std::vector<std::string>& files)const;
	uint GetFilesAndDirs(const char* dir, std::vector<std::string>& files, std::vector<std::string>& dirs)const;

	double GetLastModification(const char* file)const;
	bool Destroy(std::string filename)const;
	bool DuplicateFile(const char* src, const char* dst)const;

};

#endif