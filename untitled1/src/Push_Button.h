//
// Created by cemke on 04/08/2024.
//

#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H


class Push_Button {
    public:
        Push_Button(int pin, bool is_pull_up = false);
        bool is_pressed() const;
    private:
        int pin;
        bool is_pull_up;
};



#endif //PUSH_BUTTON_H
