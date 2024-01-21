#pragma once

#include "Common.h"

namespace xe
{
	enum class ComponentID
	{
		Null,
		Transform,
		Camera,

		Count
	};
}

#define SET_TYPE_ID(id)\
    static uint32_t StaticGetTypeID() {return static_cast<uint32_t>(id);}\
    uint32_t GetTypeID() const override {return StaticGetTypeID();}