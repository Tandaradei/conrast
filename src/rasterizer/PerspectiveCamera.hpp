#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utils/Vec.hpp"
#include "utils/Matrix.hpp"

namespace conrast { namespace rast {

class PerspectiveCamera {
public:
	PerspectiveCamera();

	utils::Vec3f projectToScreen(utils::Vec3f worldPos) const;
	utils::Vec3f projectToWorld(utils::Vec3f screenPos) const;

	// This function should be preferred when setting more than one value
	void setValues(
		utils::Vec3f position,
		utils::Vec3f viewDirectionNormalized,
		float zNear,
		float zFar,
		float fovDegrees,
		float aspectRatio
	);

	void setPosition(utils::Vec3f position);
	utils::Vec3f getPosition() const;

	void setViewDirection(utils::Vec3f viewDirectionNormalized);
	utils::Vec3f getViewDirection() const;
	void lookAt(utils::Vec3f position);

	void setZNear(float zNear);
	float getZNear() const;

	void setZFar(float zFar);
	float getZFar() const;

	void setFovDegrees(float fov);
	float getFovDegrees() const;

	void setAspectRatio(float aspectRatio);
	float getAspectRatio() const;

private:
	void calculateProjectionMatrix();

private:
	utils::Vec3f	m_position;
	utils::Vec3f	m_viewDirection;
	float			m_zNear;
	float			m_zFar;
	float			m_fov;
	float			m_aspectRatio;
	utils::Mat4f	m_projectionMatrix;
	utils::Mat4f	m_projectionMatrixInversed;
};

} }

#endif // CAMERA_HPP