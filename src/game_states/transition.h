#ifndef TRANSITION_H
#define TRANSITION_H
#include <optional>

// Identify states without including their headers
enum class StateID {
    Start,
    Play,
    Lose
};

struct Transition {
    enum class Type {
        Switch,  // replace current state with target
        Quit     // exit the game loop
    };

    Type type;
    StateID target; // only meaningful for Switch

    // Convenience constructors
    static Transition switch_to(StateID id) { return { Type::Switch, id }; }
    static Transition quit()                { return { Type::Quit,  StateID::Start }; }
};

// A state returns:
// - std::nullopt  -> no transition
// - Transition    -> request a transition
using TransitionRequest = std::optional<Transition>;

#endif //TRANSITION_H
