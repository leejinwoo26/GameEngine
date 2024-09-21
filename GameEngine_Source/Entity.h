#pragma once
#include "CommonInclude.h"

namespace GE
{
	class Entity
	{
	public:
		Entity();
		virtual ~Entity();

		void SetName(const std::wstring& name) { this->mName = name; }
		std::wstring& GetName() { return mName; }
	private:
		std::wstring mName;
	};
}
