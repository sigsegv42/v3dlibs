#include <iostream>
#include <cmath>

#include "Camera.h"

using namespace v3D;

Camera::Camera() : profile_("Unnamed")
{
}

Camera::~Camera()
{
}

/*
based on gluUnProject
takes a screen space coordinate and the viewport dimensions
and returns the world space coordinate
*/
Vector3 Camera::unproject(const Vector3 & point, int viewport[4])
{
	Vector3 p;
	// normalize point to range [-1, 1]
	p[0] = (point[0] - viewport[0]) * 2.0f / viewport[2] - 1.0f;
	// flip y so 0 is at the bottom of the viewport and viewport size is the top
	p[1] = ((viewport[3] - point[1]) - viewport[1]) * 2.0f / viewport[3] - 1.0f;
	p[2] = 2.0f * point[2] - 1.0f;

	// get inverse transformation matrix
	Matrix4 m, inv;
	m = projection() * view();
	inv = m;
	inv.inverse();
	float w = inv[12] * p[0] + inv[13] * p[1] + inv[14] * p[2] + inv[15];

	return ((inv * p) / w);
}

/*
based on gluProject
takes a world space coordinate and the viewport dimensions
returns the screen space coordinate
*/
Vector3 Camera::project(const Vector3 & point, int viewport[4])
{
	Vector3 p;
	p = view() * point;
	p = projection() * p;

	p[0] = viewport[0] + (1.0f + p[0]) * viewport[2] / 2.0f;
	p[1] = viewport[1] + (1.0f + p[1]) * viewport[3] / 2.0f;
	p[2] = (1.0f + p[2]) / 2.0f;

	return p;
}

/*
build either an orthographic or perspective projection matrix
the resulting matrix is similar to what glOrtho() and glFrustum() would build
*/
void Camera::createProjection() // active scene bound
{
	float aspect = profile_.pixelAspect_;
	if (!orthographic())
	{
		/*
			glFrustum(left, right, bottom, top, near, far)
			glFrustum(-aspect, aspect, -1., 1., _viewport->_camera->near(), _viewport->_camera->far());

			[(2*near)/(right-left)	0						A	0]
			[0						(2*near)/(top-bottom)	B	0]
			[0						0						C	D]
			[0						0						-1	0]

			A = (right + left) / (right - left)
			B = (top + bottom) / (top - bottom)
			C = (far + near) / (far - near)
			D = (2 * near * far) / (far - near)

			instead of doing what glFrustum does we could do gluPerspective
			which does the same as the frustum method
		*/
		// gluPerspective part
		float xmin, xmax, ymin, ymax;
		ymax = profile_.near_ * tan(profile_.fov_ * PI / 360.0f);
		ymin = -ymax;
		xmin = ymin * aspect;
		xmax = ymax * aspect;

		// glFrustum part
		float left = xmin;
		float right = xmax;
		float bottom = ymin;
		float top = ymax;
		float x = (2.0f * profile_.near_) / (right - left);
		float y = (2.0f * profile_.near_) / (top - bottom);
		float A = (right + left) / (right - left);
		float B = (top + bottom) / (top - bottom);
		float C = -(profile_.far_ + profile_.near_) / (profile_.far_ - profile_.near_);
		float D = -(2.0f * profile_.far_ * profile_.near_) / (profile_.far_ - profile_.near_);

		projection_[0] = x;
		projection_[1] = 0.0f;
		projection_[2] = A;
		projection_[3] = 0.0f;
		projection_[4] = 0.0f;
		projection_[5] = y;
		projection_[6] = B;
		projection_[7] = 0.0f;
		projection_[8] = 0.0f;
		projection_[9] = 0.0f;
		projection_[10] = C;
		projection_[11] = D;
		projection_[12] = 0.0f;
		projection_[13] = 0.0f;
		projection_[14] = -1.0f;
		projection_[15] = 0.0f;
	}
	else // orthographic
	{
		/*
			[2 / (right-left)	0					0				tx	]
			[0					2 / (top-bottom)	0				ty	]
			[0					0					-2/(far-near)	tz	]
			[0					0					0				1	]

			tx = (right + left) / (right - left)
			ty = (top + bottom) / (top - bottom)
			tz = (far + near) / (far - near)

			glOrtho(left, right, bottom, top, near, far)
			glOrtho(-1.33, 1.33, -1.0, 1.0, 	0.1, 1.0)

			near/far are distances from camera to the respective clipping planes
			left/right, top/bottom are points on each of the respective horizontal/vertical clipping planes
			the transpose method should be used when setting this matrix in GL (to account for row/column order)
		*/
		aspect *= profile_.orthoZoom_;
		float left = -1.0f * aspect;
		float right = 1.0f * aspect;
		float top = 1.0f * profile_.orthoZoom_;
		float bottom = -1.0f * profile_.orthoZoom_;
		float far_val = profile_.far_;
		float near_val = profile_.near_;

		// mesa's glOrtho negates the top value
		float tx = -(right + left) / (right - left);
		float ty = -(top + bottom) / (top - bottom);
		float tz = -(far_val + near_val) / (far_val - near_val);

		projection_[0] = 2.0f / (right - left);
		projection_[1] = 0.0f;
		projection_[2] = 0.0f;
		projection_[3] = tx;
		projection_[4] = 0.0f;
		projection_[5] = 2.0f / (top - bottom);
		projection_[6] = 0.0f;
		projection_[7] = ty;
		projection_[8] = 0.0f;
		projection_[9] = 0.0f;
		projection_[10] = -2.0f / (far_val - near_val);
		projection_[11] = tz;
		projection_[12] = 0.0f;
		projection_[13] = 0.0f;
		projection_[14] = 0.0f;
		projection_[15] = 1.0f;
	}
}

void Camera::createView()
{
	// set viewing matrix
	view_.identity();
	Vector3 e = -profile_.eye_;
	if (orthographic())
	{
		// normally for the camera rotation we'd want the inverse
		// the inverse of a pure rotation matrix should also be the transpose
		view_ = profile_.rotation_.matrix().transpose();
		view_.translate(e[0], e[1], e[2]);
	}
	else
	{
		Matrix4 rot = profile_.rotation_.matrix().transpose();
		view_.translate(e[0], e[1], e[2]);
		view_ *= rot;
	}
}

/*
	pan - move horizontally around a fixed axis (the camera's y axis) - camera rotation & look at position changes 
			but eye position doesn't - look left/right
	pan and tilt are types of rotation with restrictions
*/
void Camera::pan(float angle)
{
	Vector3 axis(0.0, 1.0, 0.0);
	Quaternion local_rotation;
	local_rotation.rotation(axis, angle);
	Quaternion total;
	total = profile_.rotation_;
	total = total * local_rotation;
	profile_.rotation_ = total;
}

/*
	tilt - move vertically around a fixed axis (camera's x axis) - look up/down
*/
void Camera::tilt(float angle)
{
	Vector3 axis(1.0, 0.0, 0.0);
	Quaternion local_rotation;
	local_rotation.rotation(axis, angle);
	Quaternion total;
	total = profile_.rotation_;
	total = total * local_rotation;
	profile_.rotation_ = total;
}

/*
	dolly - move eye forward or backward along direction of view
	dolly, truck, pedestal are types of translations with special restrictions
	dolly - same as pedestal but use direction vector instead of up vector
*/
void Camera::dolly(float d)
{
	Vector3 ed = profile_.direction_ * d;
	profile_.eye_ += ed;
}

/*
	truck - move eye on axis perpendicular to direction of view and up axis - move left/right
	truck - multiply delta value and right vector to get eye delta - right vector must be 
	normalized - add eye delta to current eye position
*/
void Camera::truck(float delta)
{
	Vector3 ed = profile_.right_ * delta;
	profile_.eye_ += ed;
}

/*
	zoom - affects the camera lens to zoom in or out (dolly without moving camera)
*/
void Camera::zoom(float z)
{
	profile_.orthoZoom_ += z;
}

/*
	pedestal - move eye on up axis - move up/down
	pedestal - same as truck but use up vector instead of right vector
*/
void Camera::pedestal(float delta)
{
	Vector3 ed = profile_.up_ * delta;
	profile_.eye_ += ed;
}

Matrix4 Camera::view() const
{
	return view_;
}

Matrix4 Camera::projection() const
{
	return projection_;
}

bool Camera::orthographic() const
{
	if (profile_.options_ & CameraProfile::OPTION_ORTHOGRAPHIC)
		return true;
	return false;
}

void Camera::orthographic(bool ortho)
{
	if (ortho)
		profile_.options_ |= CameraProfile::OPTION_ORTHOGRAPHIC;
	else
		profile_.options_ &= ~CameraProfile::OPTION_ORTHOGRAPHIC;
}

float Camera::orthoFactor()
{
	float factor = (profile_.orthoZoom_ * 2.0f * profile_.pixelAspect_) / profile_.size_[0];
	return factor;
}

void Camera::rotate(const Quaternion & new_rot)
{
	if (new_rot[0] != 0.0 && new_rot[1] != 0.0 && new_rot[2] != 0.0 && new_rot[3] != 0.0)
	{
		profile_.rotation_ *= new_rot;
	}
}