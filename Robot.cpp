/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include <Encoder.h>
#include <IterativeRobot.h>
#include <SmartDashboard/SmartDashboard.h>


class Robot : public frc::IterativeRobot {
public:
	Robot() {
		/* Defines the number of samples to average when determining the
		 * rate.
		 * On a quadrature encoder, values range from 1-255; larger
		 * values
		 *   result in smoother but potentially less accurate rates than
		 * lower
		 *   values.
		 */
		m_encoder.SetSamplesToAverage(5);

		/* Defines how far the mechanism attached to the encoder moves
		 * per pulse.
		 * In this case, we assume that a 360 count encoder is directly
		 * attached
		 * to a 3 inch diameter (1.5inch radius) wheel, and that we want
		 * to
		 * measure distance in inches.
		 */
		m_encoder.SetDistancePerPulse(1.0 / 360.0 * 2.0 * 3.1415 * 1.5);

		/* Defines the lowest rate at which the encoder will not be
		 * considered
		 *   stopped, for the purposes of the GetStopped() method.
		 * Units are in distance / second, where distance refers to the
		 * units
		 *   of distance that you are using, in this case inches.
		 */
		m_encoder.SetMinRate(1.0);
	}

	void TeleopPeriodic() override {
		// Retrieve the net displacement of the Encoder since the last
		// Reset.
		frc::SmartDashboard::PutNumber(
				"Encoder Distance", m_encoder.GetDistance());

		// Retrieve the current rate of the encoder.
		frc::SmartDashboard::PutNumber(
				"Encoder Rate", m_encoder.GetRate());
	}

private:
	double team;
};

START_ROBOT_CLASS(Robot)
