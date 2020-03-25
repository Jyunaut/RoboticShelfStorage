#include "Initializations.h"
#include "Interrupts.h"
#include "Handlers.h"

const float ARM_LINK_LEN = 250; //mm, both links are same length
const float servo_UsPerDeg = 8.33333333333; //TODO needs calibration. = 1500 us / 180 deg, but datasheet says 1000/180 = 5.55555
const float motA_angleUsOfZero = 500; //TODO these should be calibrated again
const float motB_angleUsOfZero = 470; //TODO these should be calibrated again

//input positions are in mm from the motors' axis to top joint on the fork
//calling code must provide 2-element array for function to write angles back to
//if returns >0, then calling code must abort and not move motors output angles
char getAngles(float xPos, float zPos, float* outputAngles[]) {
    char validity = 0; //flag, if != 0, stop calculating trig functions to avoid errors, and alert calling code
    
    //calculate helper values:
    float hypot = sqrt((xPos^2) + (zPos^2)); //hypotenuse
    float ang_hypot = atan2(xPos, zPos); //angle of hypotenuse above horizontal
    
    if(hypot > (ARM_LINK_LEN*2)) { validity = 1; } //target is outside of workspace sphere, acos() will fail
    else {
        float ang_d = acos((hypot/2)/ARM_LINK_LEN); //angle between hypot and link1

        //calculate ideal motor angles (error offsets added by motion control):
        outputAngles[0] = math.PI - ang_hypot - ang_d;          //motor A
        outputAngles[1] = (math.PI / 2) - ang_hypot + ang_d;    //motor B

        //Check if angles are valid:
        if((outputAngles[0]>(40*math.PI/180))&&(outputAngles[0]<(140*math.PI/180))) {} else { validity = 2; } //mot_A out of range
        if((outputAngles[1]>(15*math.PI/180))&&(outputAngles[1]<(130*math.PI/180))) {} else { validity = 3; } //mot_B out of range TODO this may be too restrictive
        if((outputAngles[0]+(65*math.PI/180)) > outputAngles[1]) {} else { validity = 4; } //links are pinching
        if((outputAngles[0]-outputAngles[1]) > (65*math.PI/180)) {} else { validity = 5; } //links are overextended
    }
    return validity;
}


int main()
{
    InitPortFInterrupt();
    InitPortBPWM();
}
