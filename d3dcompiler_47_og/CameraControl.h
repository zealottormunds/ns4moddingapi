#ifndef DECOMP_CAMERACONTROL_H 
#define DECOMP_CAMERACONTROL_H
#pragma once

#include <stdio.h>
#include "Vector3.h"

namespace moddingApi
{
	class CameraControl
	{
	public:
		static int __fastcall CameraControllerMain(__int64 a1);
		static __int64 __fastcall CameraControllerLoop(__int64 a1, int a2);
	};
}

#endif