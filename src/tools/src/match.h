#pragma once

#include <llvm/IR/Function.h>

#include <iostream>
#include <string>
#include <vector>

enum class Instruction
{
    cnst,
    param,
    icmp,
    br,
    phi,
    add,
    mul,
    zext,
    gep,
    load,
    fmul,
    fadd,
    fsub,
    ret,
    store
};

class Node
{
public:
    Node(Instruction o, std::string n, std::vector<int> e={}) : op(o), name(n), edges(e) { }

    Instruction      op;
    std::string      name;
    std::vector<int> edges;
};

class Graph
{
public:
    Graph(std::vector<Node> n) : nodes(n) { }

    void add(Graph& g);

    std::string opcode_string(Instruction) const;
    void print(std::ostream&) const;

    std::vector<Instruction> get_opcodes(std::vector<size_t> idx) const;
    std::vector<std::vector<size_t>> get_arguments(std::vector<size_t> idx) const;

    std::vector<Node> nodes;
};

class Match
{
public:
    Match(size_t);

    void merge(size_t a, size_t b);
    void separate(size_t a);

    void sort();

    std::vector<size_t> get_closure(size_t a) const;
    bool is_closed(std::vector<size_t>) const;
    bool overlaps(std::vector<size_t>, std::vector<size_t>) const;

    double evaluate(const Graph&, bool print=false) const;

    void print_constraints(const Graph&, std::ostream&) const;
    std::vector<size_t> first_member;
    std::vector<size_t> next_member;

private:
    void print_constraints_line(std::ostream&,std::string,Instruction) const;

};

void compute(Graph graph, Graph second_graph);

Graph from_function(llvm::Function const& fn);
