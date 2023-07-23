#include "Structures.h"

bool Realtor::operator==(const Realtor &other) const {
    return (
        this->fio == other.fio &&
        this->realtor_phone == other.realtor_phone &&
        this->commission == other.commission &&
        this->experience == other.experience 
    );
}

bool Realtor::operator!=(const Realtor &other) const {
    return !(*this == other);
}

bool Deal::operator==(const Deal &other) const {
    return (
        this->date == other.date &&
        this->price == other.price &&
        this->realtor_phone == other.realtor_phone &&
        this->address == other.address 
    );
}

bool Deal::operator!=(const Deal &other) const {
    return !(*this == other);
}



bool DealKey::operator==(const DealKey &other) const {
    return (
        this->date == other.date &&
        this->address == other.address
    );
}

bool DealKey::operator!=(const DealKey &other) const {
    return !(*this == other);
}



bool Date::operator==(const Date &other) const {
    return (
        this->day == other.day &&
        this->month == other.month &&
        this->year == other.year 
    );
}

bool Date::operator!=(const Date &other) const {
    return !(*this == other);
}
