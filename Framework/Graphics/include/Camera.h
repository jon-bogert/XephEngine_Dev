#ifndef __XE_GRAPHICS_CAMERA_H__
#define __XE_GRAPHICS_CAMERA_H__

namespace xe::Graphics
{
	// This camera assumes YAxis as up direction. You
	// cannot look straight up nor straight down.
	class Camera
	{
	public:
		enum class ProjectionMode
		{
			Perspective,
			Orthographic
		};

		void SetMode(ProjectionMode mode);

		void SetPosition(const xe::Math::Vector3& position);
		void SetDirection(const xe::Math::Vector3& direction);
		void SetLookAt(const xe::Math::Vector3& target);

		// Perspective params
		void SetFov(float fov);
		void SetAspectRatio(float ratio);
		float GetAspectRatio();

		// Orthographic params
		void SetSize(float width, float height);

		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);

		// 3 degrees of freedom for translations
		void Walk(float distance);
		void Strafe(float distance);
		void Rise(float distance);

		// 2 degrees of freedom for rotations
		void Yaw(float radian);
		void Pitch(float radian);

		// 1 degree of freedom for field of view
		void Zoom(float amount);

		const xe::Math::Vector3& GetPosition() const;
		const xe::Math::Vector3& GetDirection() const;

		xe::Math::Matrix4 GetViewMatrix() const;
		xe::Math::Matrix4 GetProjectionMatrix() const;

		xe::Math::Matrix4 GetPerspectiveMatrix() const;
		xe::Math::Matrix4 GetOrthographicMatrix() const;

	private:
		ProjectionMode _projectionMode = ProjectionMode::Perspective;

		xe::Math::Vector3 _position = xe::Math::Vector3::Zero;
		xe::Math::Vector3 _direction = xe::Math::Vector3::ZAxis;

		// 0 aspect ratio = use back buffer dimension
		float _fov = 60.0f * xe::Math::Const::DegToRad;
		float _aspectRatio = 0.0f;

		// 0 width or height = use back buffer dimension
		float _width = 0.0f;
		float _height = 0.0f;

		float _nearPlane = 0.01f;
		float _farPlane = 10000.0f;
	};
}

#endif // XE_GRAPHICS_CAMERA_H