//
// Created by cemke on 04/08/2024.
//

#ifndef STANDARD_LED_H
#define STANDARD_LED_H



class Standard_Led {

public:

    explicit Standard_Led(int pin, bool is_on = false);
    void toggle();
    void turn_on();
    void turn_off();

private:
    int pin_;
    bool status_;

};

#endif //STANDARD_LED_H
