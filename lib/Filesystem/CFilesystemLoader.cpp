#include "StdInc.h"
#include "CFilesystemLoader.h"

#include "CFileInfo.h"
#include "CFileInputStream.h"

CFilesystemLoader::CFilesystemLoader(const std::string & baseDirectory, size_t depth, bool initial):
    baseDirectory(baseDirectory),
    fileList(listFiles(depth, initial))
{
}

std::unique_ptr<CInputStream> CFilesystemLoader::load(const std::string & resourceName) const
{
	std::unique_ptr<CInputStream> stream(new CFileInputStream(getOrigin() + '/' + resourceName));
	return stream;
}

bool CFilesystemLoader::existsEntry(const std::string & resourceName) const
{
	for(auto it = fileList.begin(); it != fileList.end(); ++it)
	{
		if(it->second == resourceName)
		{
			return true;
		}
	}

	return false;
}

std::unordered_map<ResourceID, std::string> CFilesystemLoader::getEntries() const
{
	return fileList;
}

std::string CFilesystemLoader::getOrigin() const
{
	return baseDirectory;
}

bool CFilesystemLoader::createEntry(std::string filename)
{
	ResourceID res(filename);
	if (fileList.find(res) != fileList.end())
		return false;

	std::ofstream file(baseDirectory + '/' + filename);
	if (!file.good())
		return false;

	fileList[res] = filename;
	return true;
}


std::unordered_map<ResourceID, std::string> CFilesystemLoader::listFiles(size_t depth, bool initial) const
{

	assert(boost::filesystem::is_directory(baseDirectory));
	std::unordered_map<ResourceID, std::string> fileList;

	std::vector<std::string> path;//vector holding relative path to our file

	boost::filesystem::recursive_directory_iterator enddir;
	boost::filesystem::recursive_directory_iterator it(baseDirectory, boost::filesystem::symlink_option::recurse);

	for(; it != enddir; ++it)
	{
		EResType::Type type;

		if (boost::filesystem::is_directory(it->status()))
		{
			path.resize(it.level()+1);
			path.back() = it->path().leaf().string();
			it.no_push(depth <= it.level()); // don't iterate into directory if depth limit reached

			type = EResType::DIRECTORY;
		}
		else
			type = EResTypeHelper::getTypeFromExtension(boost::filesystem::extension(*it));

		if (!initial || type == EResType::DIRECTORY || type == EResType::ARCHIVE || type == EResType::TEXT)
		{
			//reconstruct relative filename (not possible via boost AFAIK)
			std::string filename;
			for (size_t i=0; i<it.level() && i<path.size(); i++)
				filename += path[i] + '/';
			filename += it->path().leaf().string();

			fileList[ResourceID(filename, type)] = filename;
		}
	}

	return fileList;
}