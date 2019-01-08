#pragma once

namespace synth {

/**
 * The interface through which fragments know how to access memory based on
 * iterators and pointers. An accessor is responsible for mapping a set of
 * iteration variables to a set of memory accesses (GEPs), based on some rules.
 * Typically they will be configured by the rule engine, but the actual
 * mechanism is abstract from that interface.
 *
 * This class presents a virtual interface that can be customised by other
 * implementations to provide different behaviour, but also gives "no-op"
 * default behaviour that maps a set of indices to themselves.
 */
class accessor {
public:
  accessor() = default;

private:
};

}
