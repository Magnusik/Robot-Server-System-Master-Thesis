/*
General purpose PID controller

u(s)/e(s) = Kp + Ki/s + NKd/(1+N/s)  with LPF filter on derrivative

*/


#include "PID.h"


void init_PID(PID_params *PID, float Ts, float alpha, float Kp, float Ki, float Kd){
    PID->Ts = Ts;
    PID->alpha = alpha;
    PID->a[0] = (4+2*alpha*Ts);
    PID->a[1] = -8;
    PID->a[2] = (4-2*alpha*Ts);


    float b0 = PID->a[0]*(Kp + 0.5*Ki*(PID->Ts))+4*Kd*(PID->alpha);
    float b1 = PID->a[1]*(Kp + (PID->alpha)*Kd) + 2*Ki*(PID->alpha)*(PID->Ts)*(PID->Ts);
    float b2 = PID->a[2]*(Kp - 0.5*Ki*PID->Ts)+4*Kd*PID->alpha;

    PID->Ke[0] = (b0/PID->a[0]);
    PID->Ke[1] = (b1/PID->a[0]);
    PID->Ke[2] = (b2/PID->a[0]);
    PID->Ku[0] = (-PID->a[1]/PID->a[0]);
    PID->Ku[1] = (-PID->a[2]/PID->a[0]);

    PID->e[0] = PID->e[1] = PID->e[2] = PID->u[0] = PID->u[1] = PID->u[2] = 0;
}


void controller_PID(PID_params *PID, float ref, float y, float maxU){


    PID->e[2] = PID->e[1];
    PID->e[1] = PID->e[0];
    PID->u[2] = PID->u[1];
    PID->u[1] = PID->u[0];


    PID->e[0] = (ref-y);
    PID->u[0] = PID->Ku[0]*PID->u[1] + PID->Ku[1]*PID->u[2] + PID->Ke[0]*PID->e[0] + PID->Ke[1]*PID->e[1] + PID->Ke[2]*PID->e[2];

    if (PID->u[0] > maxU){
        PID->u[0] = maxU;  
    }else if (PID->u[0] < -maxU){
        PID->u[0] = -maxU;
    }


    
}