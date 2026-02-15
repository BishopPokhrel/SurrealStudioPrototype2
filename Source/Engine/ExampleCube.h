#pragma once

#include <Engine/SurrealRenderer/Mesh.h>
#include <memory>

namespace SurrealStudio {

	class ExampleCube
	{
	public:

		 static std::shared_ptr<SurrealRenderer::Mesh> CreateExampleCube() noexcept;
	};
}