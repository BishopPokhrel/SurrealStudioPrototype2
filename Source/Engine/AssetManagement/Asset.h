#pragma once

#include <string>
#include <chrono>
#include <memory>

namespace SurrealStudio::AssetManagement
{
	enum class LoadState
	{
		None = 0,
		LOADED,
		UNLOADED,
		LOADING
	};

	class Asset
	{
	public:
		Asset() noexcept = default;
		~Asset() noexcept = default;

		template<typename T>
		void Load(T& assetType, const std::string& path, const std::string& assetName, LoadState loadState) noexcept;

		void Unload() noexcept;

	private:

	};

	// For optimization
	struct AssetInfo
	{
		std::unique_ptr<Asset> asset;
		std::string assetName;
		std::chrono::steady_clock::time_point lastUsedTime; // For accurate time info
		int referenceCount = 0; 
	};

}