#ifndef PID_H
#define PID_H

#include <ctime>
#include <vector>

class PID {
public:
	/*
	* Errors
	*/
	double p_error;
	double i_error;
	double d_error;

	/*
	* Coefficients
	*/
	double Kp;
	double Ki;
	double Kd;

	double cte_old;
	double delta_time;
	double delta_cte;
	double sum_cte;
	bool firstIteration;

	std::clock_t time;
	std::clock_t time_old;

	// Twiddle Dee Twiddle Dum
	std::vector<double> dp;
	int step, param_index;

	int n_settle_steps, n_eval_steps;
	double total_twiddle_error, best_error;
	bool attempt_adding, attempt_subtracting, twiddle;


	/*
	* Constructor
	*/
	PID();

	/*
	* Destructor.
	*/
	virtual ~PID();

	/*
	* Initialize PID.
	*/
	void Init(double Kp, double Ki, double Kd);

	/*
	* Update the PID error variables given cross track error.
	*/
	void UpdateError(double cte);

	/*
	* Calculate the total PID error.
	*/


	void AddToParam(int index, double amount);
};

#endif /* PID_H */