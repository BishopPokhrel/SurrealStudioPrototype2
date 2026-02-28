#include "Asset.h"	

#include <filesystem>
#include <fstream>
#include <iostream>

#include <Engine/Logging.h>

namespace Utils {

	namespace fs = std::filesystem;
	static std::string LoadFromFile(const std::string& path) noexcept
	{
		if (path.empty())
			return ""; 

		if (!fs::exists(path))
			return "";

		std::ifstream file(path, std::ios::binary | std::ios::ate);
		if (!file)
			return {};

		const std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::string buffer;
		buffer.resize(size);

		if (!file.read(buffer.data(), size))
			return {};

		return buffer;
	}
}

namespace SurrealStudio::AssetManagement
{
    template<typename T>
    void Asset::Load(T& assetType,
        const std::string& path,
        const std::string& assetName) noexcept
    {
        if (path.empty() || assetName.empty())
        {
            m_LoadState = LoadState::FAILED;
            return;
        }

        m_LoadState = LoadState::LOADING;

        std::string data = Utils::LoadFromFile(path);

        if (data.empty())
        {
            m_LoadState = LoadState::FAILED;
            return;
        }

        m_Path = path;
        m_AssetName = assetName;
        m_LoadState = LoadState::LOADED;
    }
	void Asset::Unload() noexcept
	{

	}
}