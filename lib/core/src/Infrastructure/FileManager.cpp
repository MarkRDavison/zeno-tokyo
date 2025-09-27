#include <tokyo/Core/Infrastructure/FileManager.hpp>
#include <filesystem>

namespace tokyo
{

	void FileManager::registerDirectory(const std::string& _directory)
	{
		m_Directory = _directory;
	}

	std::string FileManager::resolvePath(const std::string& _relativePath) const
	{
		std::filesystem::path path = m_Directory;
		path = path.concat(_relativePath);

#ifdef TOKYO_DEBUG

		if (!std::filesystem::exists(path))
		{
			throw std::runtime_error("Failed to find file at " + path.string());
		}

#endif
		return std::string(path.string());
	}
}