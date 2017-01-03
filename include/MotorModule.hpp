/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MotorModule.hpp
 * Author: aleja
 *
 * Created on 2 de enero de 2017, 21:11
 */

#ifndef MOTORMODULE_HPP
#define MOTORMODULE_HPP

class MotorModule {
public:
    
    void giraMDDelante();
    void giraMDAtras();
    void giraMIDelante();
    void giraMIAtras();
    void pararMD();
    void giraMI();

    inline void setPwmValue(int _pwmValue) {
        this->_pwmValue = _pwmValue;
    }

    inline int getPwmValue() const {
        return _pwmValue;
    }

    inline void setPwmPinI(int _pwmPinI) {
        this->_pwmPinI = _pwmPinI;
    }

    inline int getPwmPinI() const {
        return _pwmPinI;
    }

    inline void setPwmPinD(int _pwmPinD) {
        this->_pwmPinD = _pwmPinD;
    }

    inline int getPwmPinD() const {
        return _pwmPinD;
    }
        
private:
    int _pwmPinD;
    int _pwmPinI;
    int _pwmValue;
};

#endif /* MOTORMODULE_HPP */
