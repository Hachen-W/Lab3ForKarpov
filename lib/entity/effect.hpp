#ifndef EFFECT_HPP_INCLUDED
#define EFFECT_HPP_INCLUDED


#include <string>

using std::string;


enum EffectType {
    SLOWDOWN = 0,
    POISONING,
    WEAKENING,
};


class Effect {
private:
    EffectType _type;
    unsigned int _time;
    double _percent;
public:
    Effect(EffectType type, unsigned int time, double percent) : _type(type), _time(time), _percent(percent) {}
    EffectType getType() {
        return _type;
    }
    void setType(EffectType type) {
        _type = type;
    }
    unsigned int getTime() {
        return _time;
    }
    void setTime(unsigned int time) {
        _time = time;
    }
    double getPercent() {
        return _percent;
    }
    void setPercent(double percent) {
        _percent = percent;
    }
    friend std::ostream& operator<<(std::ostream& output, Effect obj) {
        output << "Type: " << obj.getType() << endl;
        output << "Time: " << obj.getTime() << endl;
        output << "Percent: " << obj.getPercent() << endl;
        return output;
    }
};


#endif