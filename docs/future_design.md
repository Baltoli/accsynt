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
* Any number of arguments

### Using Properties

Properties are supplied to the synthesiser

## Synthesis Techniques

A synthesis technique describes how LLVM should be generated in some situations.

## Type System

AccSynt will only consider
