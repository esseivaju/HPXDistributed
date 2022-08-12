//
// Created by esseivaj on 8/11/22.
//

#ifndef HPXDISTRIBUTED_EVENTCONTEXT_H
#define HPXDISTRIBUTED_EVENTCONTEXT_H

#include <iostream>
#include <hpx/modules/serialization.hpp>

class EventContext {

public:
    using IDType = std::size_t;
    EventContext(IDType id, double eta, double phi) : _eta{eta}, _phi{phi}, _id{id} {}

    template<class Archive>
    friend void save_construct_data(
            Archive&, EventContext const*, unsigned int);
    friend std::ostream& operator<<(std::ostream& os, const EventContext& ec) {
        os << "{id: " << ec._id << " eta: " << ec._eta << " phi: " << ec._phi << "}";
        return os;
    }

    [[nodiscard]] double eta() const {return _eta;};
    [[nodiscard]] double phi() const {return _phi;};
    [[nodiscard]] IDType id() const {return _id;};
private:
    friend class hpx::serialization::access;
    double _eta;
    double _phi;
    IDType _id;
    template <class Archive>
    void serialize(Archive&, const unsigned int) {}
};

template <class Archive>
inline void save_construct_data(Archive& ar,
                                EventContext const* ec, const unsigned int)
{
    ar << ec->_phi << ec->_eta << ec->_id;
}

template <class Archive>
inline void load_construct_data(
        Archive& ar, EventContext* ec, const unsigned int)
{
    double eta, phi;
    EventContext::IDType id;
    ar >> phi >> eta >> id;

    // ::new(ptr) construct new object at given address
    ::new (ec) EventContext(id, eta, phi);
}


#endif //HPXDISTRIBUTED_EVENTCONTEXT_H
