#include <Encoder.h>
#include <IterativeRobot.h>
#include <SmartDashboard/SmartDashboard.h>
#include <WPILib.h>
#include <ctre/Phoenix.h>
#define RAT 84.12
using namespace frc;
using namespace std;

class Robot : public frc::IterativeRobot {
public:
    Robot(){
        talon2.Follow(talon1);
        talon4.Follow(talon3);
        talon1.TalonSRX::ConfigSelectedFeedbackSensor(CTRE_MagEncoder_Absolute,0,10);
        talon3.TalonSRX::ConfigSelectedFeedbackSensor(CTRE_MagEncoder_Absolute,0,10);
                        talon1.SetInverted(true);
                        talon2.SetInverted(true);
                        talon3.SetInverted(true);
                        talon4.SetInverted(true);



    }

    void TeleopPeriodic() override {
        double setgo=0;
        bool check_neg = true;
        m_robotDrive.ArcadeDrive(joystick.GetY()/1.5,joystick.GetZ()/-1.5);

        talon3.SetSensorPhase(true);
        frc::SmartDashboard::PutNumber("Button_state", 0);
        frc::SmartDashboard::PutNumber(
                "Encoder Distance_Left", l_dis);
        frc::SmartDashboard::PutNumber(
                "Encoder Distance_Right",r_dis);
        //frc::SmartDashboard::PutNumber(
        //        "Encoder Rate_Left", talon1.GetSelectedSensorVelocity(0));
        //frc::SmartDashboard::PutNumber(
        //        "Encoder Rate_Right", talon3.GetSelectedSensorVelocity(0));
        frc::SmartDashboard::PutNumber("GOING", setgo);
        l_dis = talon3.GetSelectedSensorPosition(0)/RAT;
        r_dis = talon3.GetSelectedSensorPosition(0)/RAT;
        if(joystick.GetRawButton(1)){
            double ldis=l_dis;
            Wait(0.3);
            while(!joystick.GetRawButton(1)){
                double time=0.2;
                m_robotDrive.ArcadeDrive(joystick.GetY()/1.5,joystick.GetZ()/-1.5);
                while(joystick.GetPOV() == 0) {
                	setgo++;
                	frc::SmartDashboard::PutNumber("GOING", setgo);
                	Wait(time);
                	if(time>0.01)
                		time-=0.01;
                }
                while(joystick.GetPOV() == 180) {
                    setgo--;
                    frc::SmartDashboard::PutNumber("GOING", setgo);
                    Wait(time);
                    if(time >= 0.01)
                    	time-=0.01;
                }
                if(joystick.GetRawButton(8)) {
					setgo*=-1;
				}
				if(joystick.GetRawButton(7)) {
					setgo = 0;
				}
				frc::SmartDashboard::PutNumber("GOING", setgo);
				Wait(0.2);
            }
            frc::SmartDashboard::PutNumber("l_dis", l_dis);
            ldis+=setgo;
            check_neg = (setgo> 0)? (l_dis<=ldis):(l_dis>=ldis);
            while(check_neg){
				if(joystick.GetRawButton(7)) {
					break;
					Wait(0.2);
				}
            	if(setgo > 0) {
            		if(ldis-l_dis < 50)
            		    m_robotDrive.ArcadeDrive(-0.4,0.0);
            		else
            			m_robotDrive.ArcadeDrive(-0.7,0.0);
            	}
            	else {
            		if(l_dis-ldis < 50)
            		    m_robotDrive.ArcadeDrive(0.4,0.0);
            		else
            			m_robotDrive.ArcadeDrive(0.7,0.0);
            	}
                l_dis = talon3.GetSelectedSensorPosition(0)/RAT;
                frc::SmartDashboard::PutNumber("l_dis", l_dis);
                frc::SmartDashboard::PutNumber("ldis", ldis);
                check_neg = (setgo>0)? (l_dis<=ldis):(l_dis>=ldis);
            }
            m_robotDrive.ArcadeDrive(0.0,0.0);
        }
    }


private:
        WPI_TalonSRX talon1{7};
        WPI_TalonSRX talon2{8};
        WPI_TalonSRX talon3{1};
        WPI_TalonSRX talon4{2};


        SpeedControllerGroup left{talon1, talon2};
        SpeedControllerGroup right{talon3,talon4};
        DifferentialDrive m_robotDrive{left, right};

        double l_dis = 0;
        double r_dis = 0;

        Joystick joystick{0};
};

START_ROBOT_CLASS(Robot)
