#include "ray.hpp"

namespace flounder
{
	ray::ray(const bool &useMouse, const vector2 &screenStart) :
		m_useMouse(useMouse),
		m_screenStart(new vector2(screenStart)),
		m_viewMatrix(new matrix4x4()),
		m_projectionMatrix(new matrix4x4()),
		m_normalizedCoords(new vector2()),
		m_clipCoords(new vector4()),
		m_eyeCoords(new vector4()),
		m_invertedProjection(new matrix4x4()),
		m_invertedView(new matrix4x4()),
		m_rayWorld(new vector4()),
		m_origin(new vector3()),
		m_currentRay(new vector3())
	{
	}

	ray::~ray()
	{
		delete m_screenStart;

		delete m_origin;
		delete m_currentRay;

		delete m_viewMatrix;
		delete m_projectionMatrix;

		delete m_normalizedCoords;
		delete m_clipCoords;
		delete m_eyeCoords;

		delete m_invertedProjection;
		delete m_invertedView;
		delete m_rayWorld;
	}

	void ray::update(const vector3 &currentPosition, const vector2 &mousePosition, const matrix4x4 &viewMatrix, const matrix4x4 &projectionMatrix)
	{
		m_origin->set(currentPosition);

		if (m_useMouse)
		{
			updateNormalisedDeviceCoordinates(mousePosition.m_x, mousePosition.m_y);
		}
		else
		{
			if (m_screenStart != nullptr)
			{
				m_normalizedCoords->set(*m_screenStart);
			}
			else
			{
				m_normalizedCoords->set(0.0f, 0.0f);
			}
		}

		m_viewMatrix->set(viewMatrix);
		m_projectionMatrix->set(projectionMatrix);
		m_clipCoords->set(m_normalizedCoords->m_x, m_normalizedCoords->m_y, -1.0f, 1.0f);
		updateEyeCoords(m_clipCoords);
		updateWorldCoords(m_eyeCoords);
	}

	vector3 *ray::getPointOnRay(const float &distance, vector3 *destination) const
	{
		if (destination == nullptr)
		{
			destination = new vector3();
		}

		return vector3::add(*m_origin, *destination->set(*m_currentRay)->scale(distance), destination);
	}

	vector3 *ray::convertToScreenSpace(const vector3 &position, vector3 *destination) const
	{
		if (destination == nullptr)
		{
			destination = new vector3();
		}

		vector4 *coords = new vector4(position);
		matrix4x4::transform(*m_viewMatrix, *coords, coords);
		matrix4x4::transform(*m_projectionMatrix, *coords, coords);

		if (coords->m_w < 0.0f)
		{
			return nullptr;
		}

		return destination->set((coords->m_x / coords->m_w + 1.0f) / 2.0f, 1.0f - (coords->m_y / coords->m_w + 1.0f) / 2.0f, coords->m_z);
	}

	void ray::updateNormalisedDeviceCoordinates(const float &mouseX, const float &mouseY)
	{
		float x = (2.0f * mouseX) - 1.0f;
		float y = (2.0f * mouseY) - 1.0f;
		m_normalizedCoords->set(x, -y);
	}

	void ray::updateEyeCoords(vector4 *clipCoords)
	{
		m_invertedProjection = matrix4x4::invert(*m_projectionMatrix, m_invertedProjection);
		matrix4x4::transform(*m_invertedProjection, *m_clipCoords, m_eyeCoords);
		m_eyeCoords->set(m_eyeCoords->m_x, m_eyeCoords->m_y, -1.0f, 0.0f);
	}

	void ray::updateWorldCoords(vector4 *eyeCoords)
	{
		matrix4x4::invert(*m_viewMatrix, m_invertedView);
		matrix4x4::transform(*m_invertedView, *m_eyeCoords, m_rayWorld);
		m_currentRay->set(*m_rayWorld);
	}
}
