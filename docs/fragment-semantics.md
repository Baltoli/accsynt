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

## Parsing and Printing

This section sets out how fragments are to be parsed (c.f. printed) to a textual
representation, so that interactivity can be implemented.

An initial grammar for fragment textual specifications is as follows:

```
name ::= 'linear' | 'empty' | 'seq'

int ::= {integer constant}

name ::= '@' {identifier}

fragment ::= name template_arg_list? child_arg_list?

template_arg ::= # | int | name
template_arg_list ::= '<' (template_arg | template_arg ',' template_arg_list) '>'

child_arg ::= fragment
child_arg_list ::= '(' (child_arg | child_arg ',' child_arg_list) ')'
```

### Implementation

Based on my previous experience implementing parsers using PEGTL, I think the
best thing to do here is to build a separate parse POD type that gets updated as
the parser advances through the input. This type will know how to validate and
dispatch to the various constructors of each fragment type (i.e. a big unwrapper
in the parser that just checks the name and applies validation logic). Possibly
some nicer expression will suggest itself once we start to build it.
