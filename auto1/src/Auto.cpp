#include <cmath>
#include <ctre/Phoenix.h>
#include <WPILib.h>
#include <AHRS.h>
#include <iostream>
#include <string>
#define RAT 84.12
#define turnMultiplier 0.3


class Robot : public frc::IterativeRobot {
public:
	std::shared_ptr<NetworkTable> table;

	Robot():TEAM(DriverStation::GetInstance().GetAlliance()),
			current_dis(encoder_right.GetDistance()),
			destination_dis(encoder_right.GetDistance()+10){


		table = NetworkTable::GetTable("myTable");

				encoder_right.SetSamplesToAverage(5);
		        encoder_left.SetSamplesToAverage(5);

		        encoder_left.SetDistancePerPulse(1.0 / 1440.0 * 3.1415 * 20.32);
		        encoder_right.SetDistancePerPulse(1.0 / 1440.0 * 3.1415 * 20.32);

		        encoder_left.SetMinRate(1.0);
		        encoder_right.SetMinRate(1.0);

					fr_left.SetInverted(true);
					re_left.SetInverted(true);
					fr_right.SetInverted(true);
					re_right.SetInverted(true);
					turn_direction = table->GetNumber("switch_color", 0);
						if(TEAM==1){
							switch(turn_direction)
							{
							case 1:
							turn_direction=2;

							break;

							case 2:
							turn_direction=1;
							break;

							}
						}


	}


void AutonomousInit() override {

	ahrs->Reset();

			frc::SmartDashboard::PutNumber("current_dis", current_dis);
			frc::SmartDashboard::PutNumber("destination_dis", destination_dis);

			gamedata = frc::DriverStation::GetInstance().GetGameSpecificMessage();

								  if(gamedata[0] == 'L')
								  {
									turn_direction=2;
								  } else {
									  turn_direction=1;
								  }





			dis = fr_right.GetSelectedSensorPosition(0);


			m_timer.Reset();
			m_timer.Start();


}
void AutonomousPeriodic() override{

	frc::SmartDashboard::PutNumber("Angle", int(ahrs->GetAngle())%360);
	frc::SmartDashboard::PutNumber("Ultrasonic_left", ultrasonic_left.GetValue());
	frc::SmartDashboard::PutNumber("Ultrasonic_right", ultrasonic_right.GetValue());
	frc::SmartDashboard::PutNumber("Ultrasonic_claw", ultrasonic_claw.GetValue());
	frc::SmartDashboard::PutNumber("turn_direction", turn_direction);
	frc::SmartDashboard::PutNumber("right_encoder_dis", encoder_right.GetDistance());

	switch(mode)
	{
	case(1):

	dis_dest = dis + 15;
			while (dis_dest > dis) {
						m_robotDrive.ArcadeDrive(-0.4, 0.0);
						dis = encoder_right.GetDistance();
					}
			m_robotDrive.ArcadeDrive(0.0, 0.0);
		mode=2;
break;

	case(2):
		ahrs->Reset();
			std::cout<<"Mode 2";
			if(turn_direction==1){
				while(int(ahrs->GetAngle())%360<88){
				m_robotDrive.ArcadeDrive(0.0 , -(int(ahrs->GetAngle())%360-90)*kP_Gyro);
				}
			}
			else if(turn_direction==2){
				while(int(ahrs->GetAngle())%360>-88){
				m_robotDrive.ArcadeDrive(0.0 , -(int(ahrs->GetAngle())%360+90)*kP_Gyro);
				}
			}
			Wait(0.3);
			mode = 3;

			break;
	case(3):
			std::cout<<"Mode 3";
	      	  while(ultrasonic_left.GetValue()*kValueToInches>100){
	      		  m_robotDrive.ArcadeDrive(-0.5 , 0.0);
	      	  }
	      	m_robotDrive.ArcadeDrive(0.0, 0.0);
			Wait(0.3);
			mode = 4;

			break;
	case(4):
			std::cout<<"Mode 4";
			ahrs->Reset();


			if(turn_direction==1){
					while(int(ahrs->GetAngle())%360>-88){
							m_robotDrive.ArcadeDrive(0.0 , -(int(ahrs->GetAngle())%360+90)*kP_Gyro);
							}


						}
						else if(turn_direction==2){
							while(int(ahrs->GetAngle())%360<88){
							m_robotDrive.ArcadeDrive(0.0 , -(int(ahrs->GetAngle())%360-90)*kP_Gyro);
							}

						}
			Wait(0.3);
				mode = 5;
break;

	case(5):
			std::cout<<"mode 5";
			dis = encoder_right.GetDistance();
			dis_dest = dis + 320;
		while (dis_dest>dis) {
			m_robotDrive.ArcadeDrive(-0.5, 0.0);
			dis = encoder_right.GetDistance();
				}
		m_robotDrive.ArcadeDrive(0.0, 0.0);
		mode = 6;

break;

	case(6):

			std::cout<<"Mode 6";
		    ahrs->Reset();
	     	if(turn_direction==1){
			while(int(ahrs->GetAngle())%360>-88){
				m_robotDrive.ArcadeDrive(0.0 , -(int(ahrs->GetAngle())%360+90)*kP_Gyro);
				}
			}
	     	else if(turn_direction==2){
			while(int(ahrs->GetAngle())%360<88){
				m_robotDrive.ArcadeDrive(0.0, -(int(ahrs->GetAngle())%360-90)*kP_Gyro);
				}
			}

		    Wait(0.3);
		    mode = 7;

		    break;
	case(7):
			std::cout<<"Mode 7";

			while(ultrasonic_left.GetValue()>20){
				m_robotDrive.ArcadeDrive(-0.5, 0.0);

				}
			m_robotDrive.ArcadeDrive(0.0, 0.0);
			//Drop cube

			Wait(0.3);
			mode = 8;

			break;
	case(8):
		if(turn_direction==1){
			while(int(ahrs->GetAngle())%360<88){
				m_robotDrive.ArcadeDrive(0.0 , -(int(ahrs->GetAngle())%360-90)*kP_Gyro);
						}
					}
					else if(turn_direction==2){
						while(int(ahrs->GetAngle())%360>-88){
						m_robotDrive.ArcadeDrive(0.0 , -(int(ahrs->GetAngle())%360+90)*kP_Gyro);
						}
					}



		mode = 9;
		break;
	case(9):
			std::cout<<"mode 9";
					dis = encoder_right.GetDistance();
					dis_dest = dis + 334;
				while (dis_dest>dis) {
					m_robotDrive.ArcadeDrive(-0.5, 0.0);
					dis = encoder_right.GetDistance();
						}
				m_robotDrive.ArcadeDrive(0.0, 0.0);

				break;
	}

}

void TeleopPeriodic(){

	frc::SmartDashboard::PutNumber("Angle", int(ahrs->GetAngle())%360);
	frc::SmartDashboard::PutNumber("Ultrasonic_left", ultrasonic_left.GetValue());
	frc::SmartDashboard::PutNumber("Ultrasonic_right", ultrasonic_right.GetValue());
	frc::SmartDashboard::PutNumber("Ultrasonic_claw", ultrasonic_claw.GetValue());
	frc::SmartDashboard::PutNumber("Team", TEAM);


    customDrive();

    while(op.GetRawButton(1)) {
    	lift_claw.Set(frc::DoubleSolenoid::kForward);
    }
    	lift_claw.Set(frc::DoubleSolenoid::kOff);
    while(op.GetRawButton(4)) {
    	lift_claw.Set(frc::DoubleSolenoid::kReverse);
    }
    	lift_claw.Set(frc::DoubleSolenoid::kOff);



}

private:

	unsigned int turn_direction, mode=1;
	int TEAM;

	Encoder encoder_left { 4,5, false, Encoder::k4X };
	Encoder encoder_right { 6,7, false, Encoder::k4X };

	static constexpr double kP_Encoder = 0.008;
	static constexpr double kP_Gyro = -0.010027;
	static constexpr double kP_Ultra = 0.05;
	static constexpr double kValueToInches = 0.125;

	std::string gamedata;

	double current_dis, destination_dis;

	frc::Timer m_timer;
	AHRS *ahrs = new AHRS(SPI::kMXP, 100);

	frc::AnalogInput ultrasonic_left{0};
	frc::AnalogInput ultrasonic_right{1};
	frc::AnalogInput ultrasonic_claw{2};


	WPI_TalonSRX fr_left{1};
	WPI_TalonSRX mid_left{2};
	WPI_TalonSRX re_left{3};
	WPI_TalonSRX fr_right{4};
	WPI_TalonSRX mid_right{5};
	WPI_TalonSRX re_right{6};
	WPI_TalonSRX platform{10};

	SpeedControllerGroup left{fr_left, mid_left, re_left};
	SpeedControllerGroup right{fr_right, mid_right, re_right};
	DifferentialDrive m_robotDrive{left, right};

		DoubleSolenoid gear { 0 , 7 };
		DoubleSolenoid claw { 1, 6 };
		DoubleSolenoid lift_claw { 3, 4 };

	frc::Joystick driver{0}, op{1};

		double straight = 0;
		double turn = 0;
		double lSpeed = 0;
		double rSpeed = 0;
		double turnModfier = 0;

		double dis = 0;
		double dis_dest = 0;

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
};


START_ROBOT_CLASS(Robot)
