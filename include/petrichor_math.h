#ifndef PET_MATH_H
#define PET_MATH_H

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using Vec2 = glm::vec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Mat4 = glm::mat4;
using Quat = glm::quat;

inline Mat4 perspective(float fov, float aspect, float near, float far) {
    return glm::perspective(glm::radians(fov), aspect, near, far);
}

inline Mat4 ortho(float left, float right, float bottom, float top, float near, float far) {
    Mat4 result = glm::ortho(left, right, bottom, top, near, far);

    result[1][1] *= -1;

    return result;
}

inline Mat4 look_at(Vec3 eye, Vec3 center, Vec3 up) {
    return glm::lookAt(eye, center, up);
}

inline const float* get_raw(const Mat4& m) {
    return glm::value_ptr(m);
}

#endif