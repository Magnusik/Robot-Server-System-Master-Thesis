/*


*/

#include <stdint.h>

#ifndef PID_H_
#define PID_H_


struct pid_params{
    float u[3]; 
    float e[3];

    float a[3];
    float Ku[2];
    float Ke[3];

    float Ts;
    float alpha;
};

typedef struct pid_params PID_params;

void init_PID(PID_params *PID, float Ts, float N, float Kp, float Ki, float Kd);
void controller_PID(PID_params *PID,float ref, float y, float maxU);
#endif /*PID_H*/