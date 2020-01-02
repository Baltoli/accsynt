# Fragment Semantics

This document defines the semantics of synthesis fragments and their
compositions. In particular, it sets out some common notation and conventions we
will use consistently within Presyn and associated work.

## Terms 

* **Fragment:** a description of how to construct a partial program somehow.
  They contain concrete program logic (i.e. compilation recipes) and *holes*.
* **Hole:** an abstract location within a fragment that can either be left
  empty or contain another fragment recursively.
* **Composition:** filling a hole in one fragment with another fragment. The
  result of this is always another fragment (i.e. the operation is total).
* **Acceptance:** the other part of the abstract fragment interface beyond
  composition is defined as whether or not it contains any further holes (i.e. a
  fully-concrete fragment with no holes remaining *does not accept*).

## Composition

## Defined Fragments
