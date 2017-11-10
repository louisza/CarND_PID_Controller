---
output:
  html_document: default
  pdf_document: default
---
# CARND Term 2 
# Project 4 - PID controller 


---


## P, I and D
The P factor determines how sharp the vehicle turns. A higher value makes the vehicle turn faster. It is in essence a proportion of  the cross track error .

 
### **I**ntegral controller
The Integral factor dampens the steering angle based on the cumulative cross track error. This includes the sum of positive and negative values, which means that pendulum-esque movements of the vehicle (as views from above) decreases this adjustment. It will help correct drift.



### **D**ifferential controller
The differential controller aims to smooth out the steering angle based on the change in cte. As the vehicle gets closer to the ground truth (the cte value decreases), the steering angle will become less acute.


## Tuning
I had great amikbitions to implement a twiddle method to tune my PID controller. In the end, it was a combination of manual tuning and twiddle. I interchanged into runnig twiddle and doing my own manual adjustments by closely watching the impact of parameter changes


* Tuning the P parameter did not feel ike it was very effective. However I settled on 0.15 as it looked like an acute enough steering angle that we can damper with the D fatcor next. PID = [0.15,0,0]

[![1](https://img.youtube.com/vi/E9Fnbo6N2Kg/0.jpg)](https://youtu.be/E9Fnbo6N2Kg)


* Next step was to find a suitable D value. I started with a small value of 0.05 but that was not effective as it did not dampen enough. I settled on a value of 5. On which the car allready performed really well. PID = [0.15,0,5]


[![2](https://img.youtube.com/vi/KvxXY6M4tjM/0.jpg)](https://youtu.be/KvxXY6M4tjM)


* Then I started tuning using a twiddle implementation to tune all three paramaters ('I' was kept at zero until now). The first thing that I realised is that I had to choose enough steps to allow teh car to go round the lap at least once, otherwise the error was not comparable between steps. I settled on these parameters PID = [0.131925, 0.000000100073, 5.12]


[![3](https://img.youtube.com/vi/UwKOViQMJac/0.jpg)](https://youtu.be/UwKOViQMJac)


These parameters allow the car to go round the track with speeds in excess of 60MPH. Adding a PID controller for throttle can hopefully increase this even more. I am not entirely happy with the smoothness of the drive. It feels jerky especially at high speeds, but it performs well, not hittin the curb and snaps back to the center fairly quickly.

  
  
