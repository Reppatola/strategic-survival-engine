#include <iostream>
#include "data/body/Anatomy.h"
#include "data/body/BodyState.h"
#include "data/body/BodyProjection.h"
#include "data/observer/ObserverData.h"
#include "data/scale/Scale.h"

using namespace SSE;

int main() {
    std::cout << "=== Scale ===" << std::endl;
    std::cout << "PIXELS_PER_CM = " << Scale::PIXELS_PER_CM << std::endl;
    std::cout << "175 cm -> " << Scale::cm(175.0f) << " px" << std::endl;

    std::cout << "\n=== Anatomy (STANDARD_MALE) ===" << std::endl;
    const auto& A = Body::STANDARD_MALE;
    std::cout << "Height:   " << A.total_height  << " cm" << std::endl;
    std::cout << "Shoulder: " << A.shoulder_width << " cm" << std::endl;
    std::cout << "Head:     " << A.head.height   << " cm" << std::endl;
    std::cout << "Arm:      " << A.arm.shoulder_to_elbow + A.arm.elbow_to_wrist << " cm" << std::endl;
    std::cout << "Leg:      " << A.leg.hip_to_knee + A.leg.knee_to_ankle << " cm" << std::endl;

    std::cout << "\n=== Observer ===" << std::endl;
    const auto& O = Observer::STANDARD_OBSERVER;
    std::cout << "Height: " << O.height_cm << " cm" << std::endl;
    std::cout << "R_CORE: " << O.view_core_cm << " cm" << std::endl;
    std::cout << "R_FADE: " << O.view_fade_cm << " cm" << std::endl;
    std::cout << "Scale:  " << O.scale() << std::endl;

    std::cout << "\n=== Body Projection ===" << std::endl;
    Body::BodyState state;
    state.pose = Body::Pose::STANDING;
    state.facing = Body::Facing::S;
    auto visible = Body::project(state);
    std::cout << "Pose: STANDING, Facing: S" << std::endl;
    std::cout << "  Head:      " << (visible.head ? "yes" : "no") << std::endl;
    std::cout << "  Shoulders: " << (visible.shoulders ? "yes" : "no") << std::endl;
    std::cout << "  Chest:     " << (visible.chest ? "yes" : "no") << std::endl;
    std::cout << "  Feet:      " << (visible.feet ? "yes" : "no") << std::endl;

    return 0;
}
