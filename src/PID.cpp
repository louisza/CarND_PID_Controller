#include "PID.h"
#include <iostream>
#include <cmath>
#include <limits>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	firstIteration = true;

	// Twiddling parameters
	twiddle = true;
	dp = { 0.005*Kp,0.001*Ki,0.005*Kd };
	step = 1;
	param_index = 2;  // back to 0 after first loop
	n_settle_steps = 100;
	n_eval_steps = 7000;
	total_twiddle_error = 0;
	best_error = std::numeric_limits<double>::max();
	attempt_adding = false;
	attempt_subtracting = false;
}

void PID::UpdateError(double cte) {
	if (step == 1) {
		// to get correct initial d_error
		p_error = cte;
	}

	time = std::clock();
	d_error = cte - p_error;
	p_error = cte;
	i_error += cte;

	delta_time = (time - time_old)*1.0f / CLOCKS_PER_SEC;
	delta_time = 1;

	if (delta_time < 0.00001) {
		d_error = 0;
	}
	else {
		d_error = d_error / delta_time;
	}

	time_old = time;


	// update total error only if we're past number of settle steps
	if (step % (n_settle_steps + n_eval_steps) > n_settle_steps) {
		total_twiddle_error += pow(cte, 2);
	}

	if (twiddle && step % (n_settle_steps + n_eval_steps ) == 0 && firstIteration  != true) {
		cout << "step: " << step << endl;
		cout << "total error: " << total_twiddle_error << endl;
		cout << "best error: " << best_error << endl;
		if (total_twiddle_error < best_error) {
			cout << "improvement!" << endl;
			best_error = total_twiddle_error;
			if (step != n_settle_steps + n_eval_steps) {
				dp[param_index] *= 1.1;
			}
			// next parameter
			param_index = (param_index + 1) % 3;
			attempt_adding = attempt_subtracting = false;
		}
		if (!attempt_adding && !attempt_subtracting) {
			// try adding dp[i] to params[i]
			AddToParam(param_index, dp[param_index]);
			attempt_adding = true;
		}
		else if (attempt_adding && !attempt_subtracting) {
			// try subtracting dp[i] from params[i]
			AddToParam(param_index, -2 * dp[param_index]);
			attempt_subtracting = true;
		}
		else {
			// set it back, reduce dp[i], move on to next parameter
			AddToParam(param_index, dp[param_index]);
			dp[param_index] *= 0.9;
			// next parameter
			param_index = (param_index + 1) % 3;
			attempt_adding = attempt_subtracting = false;
		}
		total_twiddle_error = 0;
		i_error = 0;
		cout << "new parameters" << endl;
		cout << "P: " << Kp << ", I: " << Ki << ", D: " << Kd << endl;
	}

	if (twiddle && step % (n_settle_steps + n_eval_steps) == 0 && firstIteration) {
		firstIteration = false;
		total_twiddle_error = 0;
		i_error = 0;
	}


	step++;
}

void PID::AddToParam(int index, double amount) {
	if (index == 0) {
		Kp += amount;
	}
	else if (index == 1) {
		Ki += amount;
	}
	else if (index == 2) {
		Kd += amount;
	}
	else {
		std::cout << "AddToParameterAtIndex: index out of bounds";
	}
}
