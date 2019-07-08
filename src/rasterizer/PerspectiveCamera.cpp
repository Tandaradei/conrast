#include "PerspectiveCamera.hpp"

#include <cmath>

namespace conrast { namespace rast {

	PerspectiveCamera::PerspectiveCamera()
		: m_position({ 0.0f, 0.0f, 0.0f }),
		m_viewDirection({ 0.0f, 0.0f, 1.0f }),
		m_zNear(0.1f),
		m_zFar(1000.0f),
		m_fov(90.0f),
		m_aspectRatio(1.0f),
		m_projectionMatrix({}),
		m_projectionMatrixInversed({})
	{
		calculateProjectionMatrix();
	}

	utils::Vec3f PerspectiveCamera::projectToScreen(utils::Vec3f worldPos) const {
		auto result = m_projectionMatrix.multVec({ worldPos.x, worldPos.y, worldPos.z, 1.0f });
		return { result.x / result.w, result.y / result.w, result.w };
	}

	utils::Vec3f PerspectiveCamera::projectToWorld(utils::Vec3f screenPos) const {
		auto result = m_projectionMatrixInversed.multVec({ { screenPos.x * screenPos.z, screenPos.y * screenPos.z, screenPos.z }, 1.0f });
		return { result.x, result.y, result.z };
	}

	void PerspectiveCamera::setValues(utils::Vec3f position, utils::Vec3f viewDirectionNormalized, float zNear, float zFar, float fovDegrees, float aspectRatio) {
		m_position = position;
		m_viewDirection = viewDirectionNormalized;
		m_zNear = zNear;
		m_zFar = zFar;
		m_fov = fovDegrees;
		m_aspectRatio = aspectRatio;
		calculateProjectionMatrix();
	}

	void PerspectiveCamera::setPosition(utils::Vec3f position) {
		m_position = position;
		calculateProjectionMatrix();
	}

	utils::Vec3f PerspectiveCamera::getPosition() const {
		return m_position;
	}

	void PerspectiveCamera::setViewDirection(utils::Vec3f viewDirectionNormalized) {
		m_viewDirection = viewDirectionNormalized;
		calculateProjectionMatrix();
	}

	utils::Vec3f PerspectiveCamera::getViewDirection() const {
		return m_viewDirection;
	}

	void PerspectiveCamera::lookAt(utils::Vec3f position) {
		m_viewDirection = (position - m_position).normalize();
	}

	void PerspectiveCamera::setZNear(float zNear) {
		m_zNear = zNear;
		calculateProjectionMatrix();
	}

	float PerspectiveCamera::getZNear() const {
		return m_zNear;
	}

	void PerspectiveCamera::setZFar(float zFar) {
		m_zFar = zFar;
		calculateProjectionMatrix();
	}

	float PerspectiveCamera::getZFar() const {
		return m_zFar;
	}

	void PerspectiveCamera::setFovDegrees(float fov) {
		m_fov = fov;
		calculateProjectionMatrix();
	}

	float PerspectiveCamera::getFovDegrees() const {
		return m_fov;
	}

	void PerspectiveCamera::setAspectRatio(float aspectRatio) {
		m_aspectRatio = aspectRatio;
		calculateProjectionMatrix();
	}

	float PerspectiveCamera::getAspectRatio() const {
		return m_aspectRatio;
	}

	void PerspectiveCamera::calculateProjectionMatrix() {
		float fovRadian = 1.0f / atan(m_fov * 0.5f / 180.0f * 3.14159f);
		float q = m_zFar / (m_zFar - m_zNear);
		m_projectionMatrix = {
			m_aspectRatio * fovRadian,	0.0f,				0.0f,	0.0f,
			0.0f,						-fovRadian,			0.0f,	0.0f,
			0.0f,						0.0f,				q,		-q * m_zNear,
			0.0f,						0.0f,				1.0f,	0.0f
		};
		m_projectionMatrixInversed = {
			1.0f / (m_aspectRatio * fovRadian),	0.0f,				0.0f,		0.0f,
			0.0f,								-1.0f / fovRadian,	0.0f,		0.0f,
			0.0f,								0.0f,				1.0f,		0.0f,
			0.0f,								0.0f,				0.0f,		0.0f
		};
	}

} }
