#pragma once

#include "Asset.h"

namespace SurrealStudio::AssetManagement
{
	class AssetManager
	{
	public:

		bool ShouldLoadAsset(const AssetInfo& info) noexcept;
		bool ShouldUnLoadAsset(const AssetInfo& info) noexcept;
	};
}