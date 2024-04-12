#include "motor.h"

bool motor::begin(){
    if (motor_dev)
        delete motor_dev;
    motor_dev = new Adafruit_PWMServoDriver();
    motor_dev->begin();
    motor_dev->setPWMFreq(1600);

    return true;
}

void motor::setWheelsSpeed(kinematic_msg_wheels_velocity wheels_vel){
    int rpm_lmotor = map(wheels_vel.l_wheel,-80,80,-4096,4096);
    int rpm_rmotor = map(wheels_vel.r_wheel,-80,80,-4096,4096);
    int rpm_bmotor = map(wheels_vel.b_wheel,-80,80,-4096,4096);
    Serial2.printf("l_motor pwm_speed = %d\n",rpm_lmotor);
    Serial2.printf("r_motor pwm_speed = %d\n",rpm_rmotor);
    Serial2.printf("b_motor pwm_speed = %d\n",rpm_bmotor);
    setMotorRPM(l_motor,rpm_lmotor);
    setMotorRPM(r_motor,rpm_rmotor);
    setMotorRPM(b_motor,rpm_bmotor);
}

void motor::setMotorRPM(motor_pin motor, int rpm){
    int pwm = abs(rpm);
    if(rpm<0){
        motor_dev->setPWM(motor.rpwm_pin,0,4096);
        motor_dev->setPWM(motor.lpwm_pin,pwm,4096-pwm);
    }else{
        motor_dev->setPWM(motor.lpwm_pin,0,4096);
        motor_dev->setPWM(motor.rpwm_pin,pwm,4096-pwm);
    }
}