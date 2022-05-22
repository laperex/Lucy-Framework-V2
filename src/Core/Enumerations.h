#pragma once

namespace lf {
	enum Projection {
		ORTHOGRAPHIC,
		PERSPECTIVE,

		Projection_COUNT
	};

	enum CameraType {
		FPS,
		TPS,
		Default,
		None,

		CameraType_COUNT
	};
	
	enum ForceMode {
		Impulse,
		Acceleration,
		Force,
		VelocityChange,

		ForceMode_COUNT
	};

	enum LightMode {
		Point = 0,
		Spot,
		Area,
		Directional,

		LightMode_COUNT
	};

	enum MaterialAttrib {
		Ambient_Color,
		Diffuse_Color,
		Specular_Color,
		Ambient_Texture,
		Diffuse_Texture,
		Specular_Texture,
		Shininess_Float,

		MaterialAttrib_COUNT
	};
}