#include <frc/XboxController.h>
#include <frc/Joystick.h>

class OI {

 public:
   OI();
   std::pair<double, double> getSteeringControls();

 private:
   std::shared_ptr<frc::XboxController> driverController;
   std::shared_ptr<frc::XboxController> manipulatorController;

};