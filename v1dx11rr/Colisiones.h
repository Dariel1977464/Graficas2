#pragma once
#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10math.h>

class Colisiones
{
public:
	float ox, oy, oz, RangoX, RangoZ;
	
	Colisiones(float _ox, float _oy, float _oz, float _RangoX, float _RangoZ) {
		ox = _ox;
		oy = _oy;
		oz = _oz;
		RangoX = _RangoX;
		RangoZ = _RangoZ;


	}
	


	bool hitbox(float px, float pz)
	{
		if (px > (ox - RangoX) && px < (ox + RangoX))
		{
			if (pz > (oz - RangoZ) && pz < (oz + RangoZ))
			{
				return true;
			}
		}
	}

private:

};

