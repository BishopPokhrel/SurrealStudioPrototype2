#include "Asset.h"

namespace SurrealStudio::AssetManagement
{
	template<typename T>
	void Asset::Load(T& assetType, const std::string& path, const std::string& assetName, LoadState loadState) noexcept
	{
		loadState = LoadState::Loading;
	}

	void Asset::Unload() noexcept
	{

	}
}