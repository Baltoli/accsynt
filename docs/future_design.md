# Designing AccSynt v2

The biggest change I would make to AccSynt for a second revision is to make it
configurable, loading heuristics and synthesis techniques from file, rather than
by hard-coding them into the design of the synthesiser. This document sets out
to design the language in which these will be written.

Heuristics and synthesis techniques are the two primary components to be
specified using the DSL. My view of these is a one-way flow of data: synthesis
techniques are triggered by heuristics that they specify. This way, heuristics
can be separated from the techniques they enable. A technique can then require
certain heuristics to be matched before it is enabled.

## Properties

The synthesis problem AccSynt aims to solve is to take an accelerator interface
along with some properties, and to generate a program that behaves equivalently to
the accelerator. 

A property applies to sets of parameters in the interface signature. For
instance, one that specifies the relationship between a pointer and the size of
its pointed-to data might be:

```
void f(int *ptr, int s);

has_size ptr, s
```

This instantiates the `has_size` relationship between `ptr` and `s`. At
synthesis time, a synthesis technique might then query the interface properties
to see whether any pointers have a known size.

### Property Specification

Properties are identified by name (e.g. `has_size`), and they act over:
* The interface at large (this is implicit if no arguments are mentioned).
* Any number of arguments to the interface, identified by their name.
* Constant values (strings, numbers etc).
* For example:
```
has_size ptr, s
output out_ptr
no_return
input in_ptr
access :strided, 1, 2, ptr
has_size arr, 10
```

A collection of these properties specifies everything we know about an interface
that might be able to assist the synthesiser. They are ad-hoc - no specific
meaning is attached to properties, except in the way that they are used by
synthesis techniques.

### Using Properties

Properties are supplied to the synthesiser as an input, alongside the function
interface. This entails giving the synthesiser:
* A shared library that can be used to access the accelerator.
* A specification file that gives:
  * The symbol name in the shared library to look for.
  * The type signature of the symbol.
  * A set of properties to be used in the synthesis process.

## Synthesis Techniques

A synthesis technique describes how LLVM should be generated in some situation.
They specify "when these properties are matched, try this" style rules.
Therefore, a way of matching rules is needed. This looks something like:
```
match has_size sized_arg, size =>
  ... some specification for llvm
```

This is a functional-style pattern match that will bind the names `sized_arg`
and `size` inside a DSL block. The names will provide access to LLVM values that
correspond to the bound values.

### Describing LLVM

A synthesis technique needs a way of specifying how LLVM programs should be
generated. To do this we need to be able to describe:
* Control flow and the structure of basic blocks.
* Data flow and ways of generating instructions.
* Inclusion of other rules (i.e. if condition is matched, do work then use a
  sub-rule as well).
* Randomness and sampling from possibilities - synthesis is not a deterministic
  process and variation needs to be included for it to be useful.

These capabilities are everything that the current version of AccSynt is capable
of doing in a hard-coded way (it can synthesise one limited form of control
flow, and can only do random filling of data flow).

Another thing that it needs to be able to do is maintenance of sets of
instructions with specific semantics - for example, keeping track of all the
values that are tagged as indexes. The simplest way to do this that I can see is
basically to have the generation process allow for values to be added to any
number of sets when they are generated, and to allow for sampling using set
operations.

The synthesiser needs to be able to specify where instructions and control flow
should be generated (i.e. the insertion point). This means tagging basic blocks
with names, and specifying that generated instructions are to be put at the
beginning or end of blocks, or after other labelled instructions.

An example of how this specification might look is below, with the example
showing simple loop control flow:
```
  bound <= param(0)

  entry <= block
  body <= block
  exit <= block

  ind_var <= PHI in body {live, index}
  next <= add ind_var, 1
  value <= sample arithmetic, {live} in body

  phi ind_var(entry: 0, body: next)

  entry to body
  body to exit(next == bound), body
  
  return void in exit
```

Obviously the syntax can and will change as I work out more of what this
language needs to support. The main ideas are here apart from subsumption - how
could another loop be nested inside this one? The real question is the interface
between nested forms of control - if we built the control flow above, then where
are the customisation points?

One idea is that we can specify "regions" which have an entry and an exit
block, and specify attachment points within which other regions can be attached.
Then the rule set above is the specification for a region, with the
specification being given a name that can be referenced by other strategies.

Key design point here is that regions are different to heuristics - a heuristic
/ matcher as given above will invoke a type of region. So for every rule that
gets matched, we try a region - then we can use a similar method to the loop
synthesis from the existing paper to work out all the possible ways to attach
another region!
