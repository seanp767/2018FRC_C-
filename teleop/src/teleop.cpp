/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <iostream>
#include <string>
#include <math.h>
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include <DoubleSolenoid.h>
#include <ctre/Phoenix.h>
#include <ADXRS450_Gyro.h>
#include <Encoder.h>
#include <WPILib.h>

/*#include <CustomDrive.h>
 #include <PlatformLevitate.h>
 #include <Grab.h>*/

#define jsgra joystick1.GetRawAxis
#define turnMultiplier 0.3

#define RAT 84.12
#define TEAM 1 // 1 for blue and -1 for red
#define LEFT 1 // direction symbol
#define RIGHT -1 // direction symbol

using namespace std;
using namespace frc;

class Robot: public frc::IterativeRobot {
public:
	std::shared_ptr<NetworkTable> table;
	Robot() {
		encoder_right.SetSamplesToAverage(5);
		encoder_left.SetSamplesToAverage(5);

		encoder_left.SetDistancePerPulse(1.0 / 1480.0 * 3.1415 * 20.32);
		encoder_right.SetDistancePerPulse(1.0 / 1480.0 * 3.1415 * 20.32);

		encoder_left.SetMinRate(1.0);
		encoder_right.SetMinRate(1.0);
	}
	void RobotInit() {
		table = NetworkTable::GetTable("myTable");
	}
	void AutonomousInit() {
		ultra = m_ultrasonic.GetValue() * kValueToCm;
		while (table->GetNumber("switch_color", 0) == 0 && ultra > 50) {
			m_robotDrive.ArcadeDrive(0.0, 0.4);
		}
		s_mode = table->GetNumber("switch_mode", 0);
		s_color = table->GetNumber("switch_color", 0);
		dis = encoder_left.GetDistance();
		target_dir = s_color * TEAM; //-1 for target on the right and 1 for target on the left
		SmartDashboard::PutNumber("target_dir", target_dir);
		SmartDashboard::PutNumber("s_mode", s_mode);
		SmartDashboard::PutNumber("s_color", s_color);

		timer.Reset();
		timer.Start();
	}
	void AutonomousPeriodic() override {
		ultra = m_ultrasonic.GetValue() * kValueToCm;
		dis = encoder_left.GetDistance();
		SmartDashboard::PutNumber("distance", dis);
		switch (s_mode) {
		case 1 || 3: //robot on the left or right
			if (s_mode + target_dir == 2) { // on the same side, go straight
				dis_dest = dis + 312;
				while (dis_dest > dis) {
					m_robotDrive.ArcadeDrive(-0.4, 0.0);
					dis = encoder_left.GetDistance();
				}
				//turn right
				gyro.Reset();
				while ((gyro.GetAngle() - 90 * target_dir) * kP > 0.05) {
					m_robotDrive.ArcadeDrive(0.0,
							(gyro.GetAngle() - 90 * target_dir) * kP);
				}
				//go straight
				while (ultra > 40) {
					m_robotDrive.ArcadeDrive(-0.5, 0.0);
				}
				m_robotDrive.ArcadeDrive(0.0, 0.0);
				//PLACE CUBE
			} else { //on the different side
					 //1.go straight
				dis_dest = dis + 67;
				while (dis_dest > dis) {
					m_robotDrive.ArcadeDrive(-0.4, 0.0);
					dis = encoder_left.GetDistance();
				}
				m_robotDrive.ArcadeDrive(0.0, 0.0);
				//2.turn right 90 degrees
				gyro.Reset();
				while ((gyro.GetAngle() - 90 * target_dir) * kP > 0.05) {
					m_robotDrive.ArcadeDrive(0.0,
							(gyro.GetAngle() - 90 * target_dir) * kP);
				}
				m_robotDrive.ArcadeDrive(0.0, 0.0);
				//3.go straight
				dis_dest = dis + 546;
				while (dis_dest > dis) {
					m_robotDrive.ArcadeDrive(-0.5, 0.0);
					dis = encoder_left.GetDistance();
				}
				m_robotDrive.ArcadeDrive(0.0, 0.0);
				//4.turn  90 degrees
				gyro.Reset();
				while ((gyro.GetAngle() - 90 * target_dir) * kP > 0.05) {
					m_robotDrive.ArcadeDrive(0.0,
							(gyro.GetAngle() - 90 * target_dir) * kP);
				}
				m_robotDrive.ArcadeDrive(0.0, 0.0);
				//5.go straight
				dis_dest = dis + 439;
				while (dis_dest > dis) {
					m_robotDrive.ArcadeDrive(-0.5, 0.0);
					dis = encoder_left.GetDistance();
				}
				m_robotDrive.ArcadeDrive(0.0, 0.0);
				//6.turn  90 degrees
				gyro.Reset();
				while ((gyro.GetAngle() - 90 * target_dir) * kP > 0.05) {
					m_robotDrive.ArcadeDrive(0.0,
							(gyro.GetAngle() - 90 * target_dir) * kP);
				}
				m_robotDrive.ArcadeDrive(0.0, 0.0);
				//7.go straight with ultrasonic
				while (ultra > 40) {
					m_robotDrive.ArcadeDrive(-0.5, 0.0);
				}
				m_robotDrive.ArcadeDrive(0.0, 0.0);
				m_robotDrive.SetExpiration(0.1);
				//PLACE CUBE
			}
			break;
		case 2:				//robot on the central
							// 1.go straight
			dis_dest = dis + 67;
			while (dis_dest > dis) {
				dis = encoder_left.GetDistance();
				m_robotDrive.ArcadeDrive(-0.5, 0.0);
			}
			m_robotDrive.ArcadeDrive(0.0, 0.0);
			//2.turn  90 degrees
			gyro.Reset();
			while ((gyro.GetAngle() - 90 * target_dir) * kP < -0.05) {
				SmartDashboard::PutNumber("angle",
						(gyro.GetAngle() - 90 * target_dir) * kP);
				m_robotDrive.ArcadeDrive(0.0,
						(gyro.GetAngle() - 90 * target_dir) * kP);
			}
			m_robotDrive.ArcadeDrive(0.0, 0.0);
			//3.go straight
			dis_dest = dis + 282 + 152 * target_dir;
			while (dis_dest > dis) {
				dis = encoder_left.GetDistance();
				m_robotDrive.ArcadeDrive(-0.5, 0.0);
			}
			m_robotDrive.ArcadeDrive(0.0, 0.0);
			//4.turn  90 degrees
			gyro.Reset();
			while (gyro.GetAngle() * kP < -0.05) {
				SmartDashboard::PutNumber("angle",
						(gyro.GetAngle() - 90 * target_dir) * kP);
				m_robotDrive.ArcadeDrive(0.0,
						(gyro.GetAngle() - 90 * target_dir) * kP);
			}
			m_robotDrive.ArcadeDrive(0.0, 0.0);
			//5.go straight
			dis_dest = dis + 439;
			while (dis_dest > dis) {
				m_robotDrive.ArcadeDrive(-0.5, 0.0);
				dis = encoder_left.GetDistance();
			}
			m_robotDrive.ArcadeDrive(0.0, 0.0);
			//6.turn  90 degrees
			gyro.Reset();
			while ((gyro.GetAngle() - 90 * target_dir) * kP > 0.05) {
				m_robotDrive.ArcadeDrive(0.0,
						(gyro.GetAngle() - 90 * target_dir) * kP);
			}
			m_robotDrive.ArcadeDrive(0.0, 0.0);
			//7.go straight with ultrasonic
			while (ultra > 40) {
				m_robotDrive.ArcadeDrive(-0.5, 0.0);
			}
			m_robotDrive.ArcadeDrive(0.0, 0.0);
			m_robotDrive.SetExpiration(0.1);
			//PLACE CUBE
			break;
		}
		gyro.Reset();
		while ((gyro.GetAngle() - 90 * target_dir) * kP > 0.05) {
			m_robotDrive.ArcadeDrive(0.0,
					(gyro.GetAngle() - 90 * target_dir) * kP);
		}
		m_robotDrive.ArcadeDrive(0.0, 0.0);
		dis_dest = dis + 980;
		while (dis_dest > dis) {
			m_robotDrive.ArcadeDrive(-0.5, 0.0);
			dis = encoder_left.GetDistance();
		}
		m_robotDrive.ArcadeDrive(0.0, 0.0);



	}
	void TeleopInit() {
		gyro.Reset();
	}
	void TeleopPeriodic() {

		ultra = m_ultrasonic.GetValue() * kValueToCm;
		SmartDashboard::PutNumber("ultra", ultra);
		SmartDashboard::PutNumber("angle", gyro.GetAngle() * kP);
		dis = encoder_left.GetDistance();
		SmartDashboard::PutNumber("distance", dis);
		customDrive();
		upanddown(1, 0, '1');
		upanddown(3, 2, '2');
		grabFun();
		while(op.GetRawButton(1)) {
		  lift_claw.Set(frc::DoubleSolenoid::kForward);
		}
		lift_claw.Set(frc::DoubleSolenoid::kOff);
		while(op.GetRawButton(4)) {
			lift_claw.Set(frc::DoubleSolenoid::kReverse);
		}
		lift_claw.Set(frc::DoubleSolenoid::kOff);

	}

	void TestPeriodic() {
	}
private:
	static constexpr double kValueToCm = 0.125;
	DifferentialDrive m_robotDrive { right, left };
	AnalogInput m_ultrasonic { 0 };

	ADXRS450_Gyro gyro { };

	DoubleSolenoid gear { 0, 7 };
	DoubleSolenoid claw { 1, 6 };
	DoubleSolenoid lift_claw { 3, 4 };


	frc::Timer timer;
	Encoder encoder_left { 4,5, false, Encoder::k4X };
	Encoder encoder_right { 6,7, false, Encoder::k4X };

	double kP = -0.01028;
	int ultra = m_ultrasonic.GetValue() * kValueToCm;
	double dis = 0;
	double dis_dest = 0;
	bool blue_front = true;
	int s_mode = 0;
	int s_color = 0;
	double target_dir = 0;
	bool waitedAlready = false;
	//customDrive-------------------------start------------------------------
	double straight = 0;
	double turn = 0;
	double lSpeed = 0;
	double rSpeed = 0;
	double turnModfier = 0;
	WPI_TalonSRX talon1 { 1 }, talon2 { 2 }, talon3 { 3 }, talon4 { 4 },
			talon5 { 5 }, talon6 { 6 }, talon7/*cr*/{ 7 }, talon8 { 8 },
			talon9 { 9 }, platform { 10 };
	SpeedControllerGroup right { talon1, talon2, talon3 }, left { talon4,
			talon5, talon8 };

	Joystick driver { 0 }, op { 1 };


	void customDrive() {
		straight = (driver.GetRawAxis(3) - driver.GetRawAxis(2)) * 0.3;
		turn = driver.GetRawAxis(0);

		if (!(abs(straight) < 0.05))
			turnModfier = straight * turn * turnMultiplier;
		else
			turnModfier = turn * 0.3;

		if (abs(turn) > 0.04) {
			lSpeed = straight + turnModfier;
			rSpeed = straight - turnModfier;
		} else {
			lSpeed = straight;
			rSpeed = straight;
		}

		left.Set(-lSpeed);
		right.Set(rSpeed);

	}
	//customDrive--------------------------end-----------------------------

	//platformLevitating------------------start----------------------------
	void upanddown(int upport, int downport, char mod) {
		DigitalInput uplim { upport }, downlim { downport };
		if (mod == '1') {
			frc::SmartDashboard::PutBoolean("uplim1", uplim.Get());
			SmartDashboard::PutBoolean("downlim1", downlim.Get());
			if (uplim.Get() == true && downlim.Get() == true)
				platform.Set(op.GetRawAxis(5));
			else if(uplim.Get()==true){
				if(op.GetRawAxis(5) * 0.6<=0)
					platform.Set(op.GetRawAxis(5));
			}
			else if(downlim.Get()==true){
							if(op.GetRawAxis(5) * 0.6>=0)
								platform.Set(op.GetRawAxis(5));
						}
		} else if (mod == '2') {
			SmartDashboard::PutBoolean("uplim2", uplim.Get());SmartDashboard::PutBoolean("downlim2", downlim.Get());

				talon7.Set(op.GetRawAxis(1) * 0.6);

		}
	}
};

	//platformLevitating--------------------end---------------------------

	//grab--------------------------------start---------------------
