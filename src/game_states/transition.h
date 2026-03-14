#ifndef TRANSITION_H
#define TRANSITION_H
#include <cstdint>
#include <optional>

// Identify states without including their headers
enum class StateID : std::uint8_t { Start, Play, Lose, Win };

struct Transition {
    enum class Type : std::uint8_t {
        Switch, // replace current state with target
        Quit    // exit the game loop
    };

    Type type;
    StateID target; // only meaningful for Switch

    // Convenience constructors
    static Transition switch_to(const StateID identifier) { return {Type::Switch, identifier}; }
    static Transition quit() { return {Type::Quit, StateID::Start}; }
};

// A state returns:
// - std::nullopt  -> no transition
// - Transition    -> request a transition
using TransitionRequest = std::optional<Transition>;

#endif // TRANSITION_H
