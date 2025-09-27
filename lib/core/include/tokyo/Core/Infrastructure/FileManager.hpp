#pragma once

#include <string>
#include <tokyo/Core/Utils/NonCopyable.hpp>

namespace tokyo
{
	class FileManager : NonCopyable
	{
	public:
		void registerDirectory(const std::string& _directory);

		std::string resolvePath(const std::string& _relativePath) const;

	private:
		std::string m_Directory;
	};

}