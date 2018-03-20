#pragma once

#include "../../../Maths/Vector3.hpp"
#include "../../../Maths/Quaternion.hpp"
#include "JointTransformData.hpp"

namespace Flounder
{
	class F_EXPORT JointTransform
	{
	private:
		Vector3 *m_position;
		Quaternion *m_rotation;

	public:
		JointTransform(const Vector3 &position, const Quaternion &rotation);

		JointTransform(const JointTransformData &data);

		JointTransform(const Matrix4 &localTransform);

		~JointTransform();

		Matrix4 *GetLocalTransform();

		static JointTransform *Interpolate(const JointTransform &frameA, const JointTransform &frameB, const float &progression);

		static Vector3 Interpolate(const Vector3 &start, const Vector3 &end, const float &progression);

		Vector3 *GetPosition() const { return m_position; }

		void SetPosition(const Vector3 &position) { *m_position = position; }

		Quaternion *GetRotation() const { return m_rotation; }

		void SetRotation(const Quaternion &rotation) { *m_rotation = rotation; }
	};
}
