#include <cmath>

#include <AnalogGyro.h>
#include <Drive/DifferentialDrive.h>
#include <IterativeRobot.h>
#include <Joystick.h>
#include <ctre/Phoenix.h>
#include <WPILib.h>
#include <AHRS.h>
#include <iostream>

using namespace frc;
using namespace std;


class Robot : public frc::IterativeRobot {
public:



	void TeleopPeriodic() override {




		frc::SmartDashboard::PutNumber("Angle", int(ahrs->GetAngle())%360);
		frc::SmartDashboard::PutNumber("UpdateRate", ahrs->GetActualUpdateRate());



		if ( m_joystick.GetRawButton(2)) {
			   ahrs->Reset();
			}

		bool turnControl;


		while(m_joystick.GetRawButton(3)){

		m_robotDrive.ArcadeDrive(m_joystick.GetY()*-0.7, (int(ahrs->GetAngle())%360-90)*kP);
							turnControl=1;


		}

		while(m_joystick.GetRawButton(4)){

		m_robotDrive.ArcadeDrive(m_joystick.GetY()*-0.7, (int(ahrs->GetAngle())%360-180)*kP);
							turnControl=1;


				}
		while(m_joystick.GetRawButton(5)){

		m_robotDrive.ArcadeDrive(m_joystick.GetY()*-0.7, (int(ahrs->GetAngle())%360-270)*kP);
							turnControl=1;



				}
		while(m_joystick.GetRawButton(6)){

		m_robotDrive.ArcadeDrive(m_joystick.GetY()*-0.7, int(ahrs->GetAngle())%360*kP);
							turnControl=1;



				}

			turnControl=0;

		if(turnControl == 0)
				{
					m_robotDrive.ArcadeDrive(m_joystick.GetY()*-0.7, m_joystick.GetZ()*0.5);
				}

	}

private:

	int test;

	AHRS *ahrs = new AHRS(SPI::kMXP, 100);

	double kP=-0.01228;

	WPI_TalonSRX talon1{1};
	WPI_TalonSRX talon2{2};
	WPI_TalonSRX talon3{3};
	WPI_TalonSRX talon4{4};

	SpeedControllerGroup left{talon1, talon2};
	SpeedControllerGroup right{talon3,talon4};
	DifferentialDrive m_robotDrive{left, right};


	frc::Joystick m_joystick{0};
};

START_ROBOT_CLASS(Robot)
