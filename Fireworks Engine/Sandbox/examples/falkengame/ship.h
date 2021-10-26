#pragma once

#include "fireworks.h"

using namespace fireworks;
using namespace maths;

inline float Clamp(float value, float min, float max)
{
    return fmin(fmax(value, min), max);
}

inline float DegreesToRadians(float degrees)
{
    return degrees * (M_PI / 180.f);
}

// Convert a normalized axis and angle to a quaternion.
inline falken::Rotation AxisAngle(falken::Position axis, float degrees)
{
    float radians = DegreesToRadians(degrees);
    float s = sin(radians / 2);
    return { s * axis.x, s * axis.y, s * axis.z, cos(radians / 2) };
}

// Convert a HelloFalken 2D angle to a quaternion specifying a 3D rotation.
inline falken::Rotation HFAngleToQuaternion(float angle)
{
    // Falken uses 3D coordinates. We therefore interpret game 2D locations as
    // 3D positions on the XZ plane. We translate a HelloFalken angle into a
    // quaternion that specifies a rotation around the Y-axis. We need to
    // modify the angle in two ways before constructing the quaternion:
    // 1) We need to offset the angle by 90 degrees. This is because Falken
    //    assumes that an object at neutral orientation points towards the
    //    Z-axis, but an object at neutral orientation in HelloFalken points
    //    towards the X-axis.
    // 2) Falken uses a left-handed coordinate system, so rotations around the
    //    Y-axis are clockwise (when looking at the XZ plane from above). Since
    //    angles in HelloFalken are counter-clockwise, we need to negate the
    //    angle.
    float lh_angle_around_y = -angle - 90;
    return AxisAngle({ 0.0, 1.0, 0.0 }, lh_angle_around_y);
}

class Ship
{
public:
    vec2 position = vec2(0.0F, 0.0F);
    float rotation = 0.f;
    static const float kSize;

    // Sets new values for steering and throttle
    void SetControls(float steering, float throttle)
    {
        this->steering = steering;
        this->throttle = throttle;
    }


    // Updates the position and orientation of the ship
    void Update(float delta_time = 0.0f)
    {
        // The max acceleration applied by the throttle
        static const float kMaxThrottle = 750.17f;
        // the max acceleration applied by steering
        static const float kMaxSteering = 200.f;
        // The max velocity of the ship
        static const float kMaxVelocity = 10.25f;
        // The rate at which ship velocity decays
        static const float kVelocityDecay = 5.f;
        // The max angular velocity of the ship
        static const float kMaxAngularVelocity = 950.f;
        // The rate at which ship angular velocity decays
        static const float kAngularDecay = 5.f;

        // Apply steering
        angular_velocity += steering * kMaxSteering * delta_time;
        // Decay gradually slows rotation
        angular_velocity -= angular_velocity * kAngularDecay * delta_time;
        // Ensure we don't exceed our max angular velocity
        angular_velocity =
            Clamp(angular_velocity, -kMaxAngularVelocity, kMaxAngularVelocity);
        // Apply angular veloicty to rotation
        rotation += angular_velocity * delta_time;

        // Apply thrust
        float playerAcceleration = throttle * kMaxThrottle * delta_time;
        vec2 impulse = vec2(cos(toRadians(rotation)), sin(toRadians(rotation)));
        impulse *= playerAcceleration * delta_time;
        velocity += impulse;
        // Decay gradually slows the ship down
        velocity -= velocity * kVelocityDecay * delta_time;
        // Ensure we don't exceed our max velocity
        float velocity_mag_sq = velocity.magSquared();
        if (velocity_mag_sq > (kMaxVelocity * kMaxVelocity)) {
            float scale = kMaxVelocity / sqrtf(velocity_mag_sq);
            velocity *= scale;
        }
        // Apply velocity to position
        position += velocity * delta_time;
    }


    // Moves ship to random position and rotation
    // Zeroes out steering, throttle, and velocity
    void Reset()
    {
        position = vec2(getRandomValue<float>(-60, 60), getRandomValue<float>(-45, 45));;
        rotation = getRandomValue<float>(0.0f, 360.0f);
        steering = 0.f;
        throttle = 0.f;
        velocity.x = 0.f;
        velocity.y = 0.f;
        angular_velocity = 0.f;
    }

    float GetSteering() const { return steering; }
    float GetThrottle() const { return throttle; }

    vec2 GetForward() const { return vec2(cos(toRadians(rotation)), sin(toRadians(rotation))); }
    vec2 GetRight() const
    {
        vec2 forward = GetForward();
        return vec2(forward.y, -forward.x);
    }

private:
    float steering = 0.f;
    float throttle = 0.f;
    vec2 velocity = vec2(0.0F, 0.0F);
    float angular_velocity = 0.f;
};
