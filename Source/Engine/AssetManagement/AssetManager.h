#pragma once

#include "Asset.h"

namespace SurrealStudio::AssetManagement
{
	class AssetManager
	{
	public:

		bool ShouldLoadAsset(const AssetInfo& info) noexcept
		{
			// TODO: Finish it
			return true;
		}

		bool ShouldUnLoadAsset(const AssetInfo& info) noexcept
		{
			using namespace std::chrono;

			if (info.referenceCount > 0)
				return false;

			if (steady_clock::now() - info.lastUsedTime < seconds(30))
				return false;
			else
				return true;
		}
	};
}