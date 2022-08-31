
#include <hpx/config.hpp>
#include <hpx/hpx.hpp>
#include <hpx/serialization.hpp>
#include <hpx/future.hpp>
#include <hpx/runtime_distributed.hpp>
#include <hpx/wrap_main.hpp>
#include <hpx/iostream.hpp>

#include <cstddef>
#include <vector>
#include <utility>
#include <string>
#include <iostream>
#include <sstream>

class EventContext {

public:
#ifdef DEFAULT_CONSTRUCTIBLE
    explicit EventContext() : EventContext(0,{}) {}
#endif
    EventContext(std::size_t id, std::vector<std::string> requested) : _id{id}, _requested{std::move(requested)} {}

    template<class Archive>
    friend void save_construct_data(
            Archive &, EventContext const *, unsigned int);
    friend std::ostream &operator<<(std::ostream &os, const EventContext &ec) {
        std::stringstream ss;
        ss << "{id: " << ec._id << ", requested: ";
        for(const auto &e : ec._requested)
            ss << e << " ";
        ss << "}";
        return os << ss.str();
    }

    [[nodiscard]] std::size_t id() const { return _id; };
    [[nodiscard]] std::size_t &id() { return _id; };
    [[nodiscard]] const std::vector<std::string> &requested() const { return _requested; };

private:
    friend class hpx::serialization::access;
    std::size_t _id;
    std::vector<std::string> _requested;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int) {
#ifdef DEFAULT_CONSTRUCTIBLE
        ar & _id & _requested;
#endif
    }
};

#ifndef DEFAULT_CONSTRUCTIBLE
template<class Archive>
inline void save_construct_data(Archive &ar,
                                EventContext const *ec, const unsigned int) {
    ar << ec->_id << ec->_requested;
}

template<class Archive>
inline void load_construct_data(
        Archive &ar, EventContext *ec, const unsigned int) {
    std::vector<std::string> requested;
    std::size_t eid;
    ar >> eid >> requested;

    ::new (ec) EventContext(eid, std::move(requested));
}
#endif

#ifdef SINGLE_ARG
void print_params(const EventContext& eventContext)
#else
#ifdef VECTOR_2ND_ARG
void print_params(const EventContext& eventContext, const std::vector<std::string> & foo)
#else
void print_params(const EventContext& eventContext, const std::string& foo)
#endif
#endif
{
    hpx::cout << eventContext << std::endl;
#ifndef SINGLE_ARG
#ifdef VECTOR_2ND_ARG
    for(const auto &e : foo)
        hpx::cout << e << " ";
    hpx::cout << std::endl;
#else
    hpx::cout << foo << std::endl;
#endif
#endif
}
HPX_PLAIN_ACTION(print_params, print_params_action);

hpx::future<std::vector<hpx::shared_future<void>>> call_remote() {
    using namespace std::string_literals;
    auto remote{hpx::find_remote_localities()};
    std::vector<hpx::shared_future<void>> futures;
    for (const auto& id : remote){
        EventContext ec{23, {"a"s, "b"s}};
#ifndef SINGLE_ARG
#ifdef VECTOR_2ND_ARG
        auto f = {"foo"s, "bar"s};
        futures.emplace_back(hpx::async<print_params_action>(id, std::move(ec), std::move(f)));
#else
        auto f = "foobar"s;
        futures.emplace_back(hpx::async<print_params_action>(id, std::move(ec), std::move(f)));
#endif
#else
        futures.emplace_back(hpx::async<print_params_action>(id, std::move(ec)));
#endif
    }
    return hpx::when_all(futures);
}

int main(int argc, char** argv){
    auto futures{call_remote()};
    futures.wait();
    return 0;
}