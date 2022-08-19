//
// Created by esseivaj on 8/11/22.
//

#ifndef HPXDISTRIBUTED_EVENTCONTEXT_H
#define HPXDISTRIBUTED_EVENTCONTEXT_H

#include <hpx/modules/serialization.hpp>
#include <iostream>
#include <vector>
#include <utility>

template <class ID>
class EventContext {

public:
    using IDType = std::size_t;
    EventContext(IDType id, double eta, double phi, std::vector<ID> requested) : _eta{eta}, _phi{phi}, _id{id}, _requested{std::move(requested)} {}

    template<class Archive>
    friend void save_construct_data(
            Archive &, EventContext const *, unsigned int);
    friend std::ostream &operator<<(std::ostream &os, const EventContext &ec) {
        os << "{id: " << ec._id << " eta: " << ec._eta << " phi: " << ec._phi << "}";
        return os;
    }

    [[nodiscard]] double eta() const { return _eta; };
    [[nodiscard]] double &eta() { return _eta; };
    [[nodiscard]] double phi() const { return _phi; };
    [[nodiscard]] double &phi() { return _phi; };
    [[nodiscard]] IDType id() const { return _id; };
    [[nodiscard]] IDType &id() { return _id; };
    [[nodiscard]] const std::vector<ID>& requested() const { return _requested; };

private:
    friend class hpx::serialization::access;
    double _eta;
    double _phi;
    IDType _id;
    std::vector<ID> _requested;
    template<class Archive>
    void serialize(Archive &, const unsigned int) {}
};

template<class Archive>
inline void save_construct_data(Archive &ar,
                                EventContext<std::string> const *ec, const unsigned int) {
    ar << ec->_phi << ec->_eta << ec->_id << ec->_requested;
}

template<class Archive>
inline void load_construct_data(
        Archive &ar, EventContext<std::string> *ec, const unsigned int) {
    double eta, phi;
    std::vector<std::string> requested;
    typename EventContext<std::string>::IDType eid;
    ar >> phi >> eta >> eid >> requested;

    // ::new(ptr) construct new object at given address
    ::new (ec) EventContext<std::string>(eid, eta, phi, std::move(requested));
}


#endif//HPXDISTRIBUTED_EVENTCONTEXT_H
