#ifndef DSA_SUFFIX_AUTOMATON_H
#define DSA_SUFFIX_AUTOMATON_H

#include <algorithm>
#include <array>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// Suffix automaton
//
// A minimal DFA that recognises every suffix (and therefore every substring) of
// a string. Each state represents an end-position equivalence class; `link` is
// the suffix link and `length` is the longest string in the state.
//
// Build: O(n)
// contains: O(m)
// Distinct substrings: O(states + transitions)
// ---------------------------------------------------------------------------
class SuffixAutomaton {
public:
    explicit SuffixAutomaton(const std::string& text) {
        states_.push_back(State{});
        states_[0].length = 0;
        states_[0].link = -1;
        last_ = 0;

        for (char character : text) extend(character);
        computeOccurrences();
    }

    bool contains(const std::string& pattern) const {
        int state = 0;

        for (char character : pattern) {
            int next = transition(state, character);
            if (next == -1) return false;
            state = next;
        }

        return true;
    }

    long long distinctSubstrings() const {
        std::vector<long long> memo(states_.size(), -1);
        return countPaths(0, memo);
    }

    std::size_t stateCount() const { return states_.size(); }

    // Number of occurrences of `pattern` in the original text.
    int occurrences(const std::string& pattern) const {
        int state = 0;

        for (char character : pattern) {
            int next = transition(state, character);
            if (next == -1) return 0;
            state = next;
        }

        return states_[state].occurrences;
    }

private:
    struct State {
        std::array<int, 26> next;
        int link = -1;
        int length = 0;
        int occurrences = 0;

        State() { next.fill(-1); }
    };

    std::vector<State> states_;
    int last_ = 0;

    static int index(char character) {
        if (character < 'a' || character > 'z') {
            throw std::invalid_argument("SuffixAutomaton: expected a-z");
        }
        return character - 'a';
    }

    int transition(int state, char character) const {
        return states_[state].next[static_cast<std::size_t>(index(character))];
    }

    void extend(char character) {
        int position = index(character);
        int current = static_cast<int>(states_.size());
        states_.push_back(State{});
        states_[current].length = states_[last_].length + 1;
        states_[current].occurrences = 1;

        int previous = last_;
        while (previous != -1 && states_[previous].next[position] == -1) {
            states_[previous].next[position] = current;
            previous = states_[previous].link;
        }

        if (previous == -1) {
            states_[current].link = 0;
        } else {
            int next = states_[previous].next[position];
            if (states_[previous].length + 1 == states_[next].length) {
                states_[current].link = next;
            } else {
                int clone = static_cast<int>(states_.size());
                states_.push_back(states_[next]);
                states_[clone].length = states_[previous].length + 1;
                states_[clone].occurrences = 0;

                while (previous != -1 &&
                       states_[previous].next[position] == next) {
                    states_[previous].next[position] = clone;
                    previous = states_[previous].link;
                }

                states_[next].link = clone;
                states_[current].link = clone;
            }
        }

        last_ = current;
    }

    void computeOccurrences() {
        std::vector<int> order(states_.size());
        for (std::size_t i = 0; i < order.size(); ++i) {
            order[i] = static_cast<int>(i);
        }

        std::sort(order.begin(), order.end(), [this](int a, int b) {
            return states_[a].length > states_[b].length;
        });

        for (int state : order) {
            if (states_[state].link != -1) {
                states_[states_[state].link].occurrences += states_[state].occurrences;
            }
        }
    }

    long long countPaths(int state, std::vector<long long>& memo) const {
        if (memo[state] != -1) return memo[state];

        long long result = 0;
        for (int next : states_[state].next) {
            if (next != -1) result += 1 + countPaths(next, memo);
        }

        return memo[state] = result;
    }
};

#endif
