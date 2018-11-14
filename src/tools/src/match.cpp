#include <unordered_set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>

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
    ret
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


std::string Graph::opcode_string(Instruction op) const
{
    switch(op) {
    case Instruction::cnst:  return "cnst";
    case Instruction::param: return "param";
    case Instruction::icmp:  return "icmp";
    case Instruction::br:    return "br";
    case Instruction::phi:   return "phi";
    case Instruction::add:   return "add";
    case Instruction::zext:  return "zext";
    case Instruction::gep:   return "gep";
    case Instruction::load:  return "load";
    case Instruction::fmul:  return "fmul";
    case Instruction::fadd:  return "fadd";
    case Instruction::ret:   return "ret";
    default:                 return "";
    }
}

void Graph::print(std::ostream& ostr) const
{
    ostr<<"function( ";
    for(auto n : nodes)
        if(n.op == Instruction::param)
            ostr<<n.name<<" ";
    ostr<<") {\n";

    for(auto n : nodes)
    {
        if(n.op != Instruction::param &&
           n.op != Instruction::cnst)
        {
            if(n.name == "")
                ostr<<opcode_string(n.op);
            else
                ostr<<n.name<<" = "<<opcode_string(n.op);

            for(auto idx : n.edges)
                ostr<<" "<<nodes[idx].name;
            ostr<<"\n";
        }
    }

    ostr<<"}";
}

std::vector<Instruction> Graph::get_opcodes(std::vector<size_t> idx) const
{
    std::vector<Instruction> result;
    for(size_t i = 0; i < idx.size(); i++)
        result.push_back(nodes[idx[i]].op);
    return result;
}

std::vector<std::vector<size_t>> Graph::get_arguments(std::vector<size_t> idx) const
{
    std::vector<std::vector<size_t>> result;
    for(auto i : idx)
        for(size_t k = 0; k < nodes[i].edges.size(); k++)
        {
            if(k >= result.size()) result.resize(k+1);
            result[k].push_back(nodes[i].edges[k]);
        }
    return result;
}

void Graph::add(Graph& g)
{
    size_t old_size = nodes.size();

    for(auto n : g.nodes)
    {
        for(auto& e : n.edges)
            e += old_size;
        nodes.push_back(n);
    }
}

/*
define float @dot(i32 %n, float* %a, float* %b) {
entry:
  br label %header

exit:                                             ; preds = %loop_exit
  %0 = fsub float %9, %12
  %1 = fmul float %0, %0
  ret float %10

header:                                           ; preds = %entry
  br label %loop-check

body:                                             ; preds = %loop-check
  %2 = getelementptr float, float* %a, i32 %iter
  %3 = load float, float* %2
  %4 = getelementptr float, float* %b, i32 %iter
  %5 = load float, float* %4
  %6 = fmul float %3, %5
  %7 = fadd float %10, %6
  br label %loop-check

loop_exit:                                        ; preds = %loop-check
  %8 = fsub float %12, %10
  %9 = fmul float %12, %13
  br label %exit

loop-check:                                       ; preds = %header, %body
  %10 = phi float [ 0.000000e+00, %header ], [ %7, %body ]
  %iter = phi i32 [ 0, %header ], [ %next_iter, %body ]
  %next_iter = add i32 %iter, 1
  %11 = icmp slt i32 %iter, %n
  %12 = fsub float %10, %10
  %13 = fadd float %12, %12
  br i1 %11, label %body, label %loop_exit
}
*/
Graph first_graph(
{{Instruction::param, "%n"},                   // 0
 {Instruction::param, "%a"},                   // 1
 {Instruction::param, "%b"},                   // 2
 {Instruction::fsub,  "%0",         {13, 18}}, // 3
 {Instruction::fmul,  "%1",         { 3,  3}}, // 4
 {Instruction::ret,   "",           {14}},     // 5
 {Instruction::gep,   "%2",         { 1, 15}}, // 6
 {Instruction::load,  "%3",         { 6}},     // 7
 {Instruction::gep,   "%4",         { 2, 15}}, // 8
 {Instruction::load,  "%5",         { 8}},     // 9
 {Instruction::fmul,  "%6",         { 7,  9}}, //10
 {Instruction::fadd,  "%7",         {14, 10}}, //11
 {Instruction::fsub,  "%8",         {18, 14}}, //12
 {Instruction::fmul,  "%9",         {18, 19}}, //13
 {Instruction::phi,   "%10",        {21, 11}}, //14
 {Instruction::phi,   "%iter",      {16, 22}}, //15   this is swapped around
 {Instruction::add,   "%next_iter", {15, 23}}, //16
 {Instruction::icmp,  "%11",        { 0}},     //17
 {Instruction::fsub,  "%12",        {14, 14}}, //18
 {Instruction::fadd,  "%13",        {18, 18}}, //19
 {Instruction::br,    "",           {17}},     //20
 {Instruction::cnst,  "0.0"},                  //21
 {Instruction::cnst,  "0"},                    //22
 {Instruction::cnst,  "1"}});                  //23

/*
; ModuleID = 'dot.ll'
source_filename = "dot.ll"

; Function Attrs: norecurse nounwind readonly
define float @dot(i32 %n, float* nocapture readonly %a, float* nocapture readonly %b) local_unnamed_addr #0 {
entry:
  %0 = icmp sgt i32 %n, 0
  br i1 %0, label %body.preheader, label %loop_exit

body.preheader:                                   ; preds = %entry
  br label %body

body:                                             ; preds = %body.preheader, %body
  %iter1 = phi i32 [ %next_iter, %body ], [ 0, %body.preheader ]
  %1 = phi float [ %8, %body ], [ 0.000000e+00, %body.preheader ]
  %next_iter = add nuw nsw i32 %iter1, 1
  %2 = zext i32 %iter1 to i64
  %3 = getelementptr float, float* %a, i64 %2
  %4 = load float, float* %3, align 4
  %5 = getelementptr float, float* %b, i64 %2
  %6 = load float, float* %5, align 4
  %7 = fmul float %4, %6
  %8 = fadd float %1, %7
  %9 = icmp slt i32 %next_iter, %n  
  br i1 %9, label %body, label %loop_exit

loop_exit:                                        ; preds = %body, %entry
  %.lcssa = phi float [ 0.000000e+00, %entry ], [ %8, %body ]
  ret float %.lcssa
}

attributes #0 = { norecurse nounwind readonly }

*/
Graph second_graph(
{{Instruction::param, "%n"},                   // 0 - 24
 {Instruction::param, "%a"},                   // 1 - 25
 {Instruction::param, "%b"},                   // 2 - 26
 {Instruction::icmp,  "%0",         { 0, 19}}, // 3 - 27
 {Instruction::br,    "",           { 3}},     // 4 - 28
 {Instruction::phi,   "%iter1",     { 7, 19}}, // 5 - 29
 {Instruction::phi,   "%1",         {20, 14}}, // 6 - 30    this is swapped around
 {Instruction::add,   "%next_iter", { 5, 21}}, // 7 - 31
 {Instruction::zext,  "%2",         { 5}},     // 8 - 32
 {Instruction::gep,   "%3",         { 1, 5}},  // 9 - 33    this is manipulated
 {Instruction::load,  "%4",         { 9}},     //10 - 34
 {Instruction::gep,   "%5",         { 2, 5}},  //11 - 35    this is manipulated
 {Instruction::load,  "%6",         {11}},     //12 - 36
 {Instruction::fmul,  "%7",         {10, 12}}, //13 - 37
 {Instruction::fadd,  "%8",         { 6, 13}}, //14 - 38
 {Instruction::icmp,  "%9",         { 7,  0}}, //15 - 39
 {Instruction::br,    "",           {15}},     //16 - 40
 {Instruction::phi,   "%.lcssa",    {20, 14}}, //17 - 41
 {Instruction::ret,   "",           {17}},     //18 - 42
 {Instruction::cnst,  "0"},                    //19 - 43
 {Instruction::cnst,  "0.0"},                  //20 - 44
 {Instruction::cnst,  "1"}});                  //21 - 45

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

    double evaluate(const Graph&, bool) const;

    void print_constraints(const Graph&, std::ostream&) const;
    std::vector<size_t> first_member;
    std::vector<size_t> next_member;

private:
    void print_constraints_line(std::ostream&,std::string,Instruction) const;

};

Match::Match(size_t s) : first_member(s), next_member(s)
{
    for(size_t i = 0; i < s; i++) {
        first_member[i] = i;
        next_member[i] = 0;
    }
}

void Match::merge(size_t a, size_t b)
{
    if(first_member[a] > first_member[b])
    {
        size_t c = a;
        a = b;
        b = c;
    }

    if(first_member[a] < first_member[b])
    {
        size_t it = first_member[a];
        size_t jt = first_member[b];

        while(next_member[it])
            it = next_member[it];

        next_member[it]  = jt;
        first_member[jt] = first_member[a];

        while(next_member[jt])
        {
            jt = next_member[jt];
            first_member[jt] = first_member[a];
        }
    }
}

void Match::separate(size_t a)
{
    if(first_member[a] == a)
    {
        size_t new_first = next_member[a];
        next_member[a] = 0;

        if(new_first)
        {
            first_member[new_first] = new_first;

            size_t it = new_first;
            while(next_member[it])
            {
                it = next_member[it];
                first_member[it] = new_first;
            }
        }
    }
    else
    {
        for(auto i = 0u; i < next_member.size(); i++)
        {
            if(next_member[i] == a)
            {
                next_member[i] = next_member[a];
                first_member[a] = a;
                next_member[a] = 0;
                return;
            }
        }
    }
}

void Match::sort()
{
    bool repeat = true;

    while(repeat)
    {
        repeat = false;
        for(auto i = 0u; i < next_member.size(); i++)
        {
            size_t j = next_member[i];
            size_t k = next_member[j];
            if(j && k && k < j)
            {
                next_member[j] = next_member[k];
                next_member[k] = j;
                next_member[i] = k;
                if(i > k) repeat = true;
            }
        }
    }
}

std::vector<size_t> Match::get_closure(size_t a) const
{
    std::vector<size_t> result = { first_member[a] };

    while(next_member[result.back()])
        result.push_back(next_member[result.back()]);

    return result;
}

bool Match::is_closed(std::vector<size_t> vec) const
{
    std::vector<size_t> histo(first_member.size(), 0);

    for(auto v : vec)
        histo[v] ++;

    for(size_t i = 0; i < histo.size(); i++)
    {
        if(histo[i] && first_member[i] != i) return false;

        while(histo[i])
        {
            histo[i] -= 1;

            size_t it = i;
            while(next_member[it])
            {
                it = next_member[it];
                if(histo[it] == 0) return false;
                histo[it] -= 1;
            }
        }
    }

    return true;
}

double Match::evaluate(const Graph& g, bool print=false) const
{
    size_t distinct_groups   = 0;
    size_t opcode_mismatches = 0;
    size_t param_mismatches  = 0;
    size_t overlapped_params = 0;

    for(size_t i = 0; i < first_member.size(); i++)
    {
        if(first_member[i] == i)
        {
            std::vector<size_t> members = get_closure(i);

            distinct_groups ++;
            if(members.size() > 2) distinct_groups++;

            std::vector<Instruction> opcodes = g.get_opcodes(members);

            std::sort(opcodes.begin(), opcodes.end());
            size_t dist = std::distance(opcodes.begin(), std::unique(opcodes.begin(), opcodes.end()));
    
            opcode_mismatches += dist-1;
            
            // Score opcode match

            std::vector<std::vector<size_t>> args = g.get_arguments(members);

            std::vector<size_t> used_groups(first_member.size(), 0);
            used_groups[i] = 1;

            for(size_t j = 0; j < args.size(); j++)
            {
                if(args[j].size() != members.size() || ! is_closed(args[j]))
                    param_mismatches += members.size();

                for(size_t k = 0; k < args[j].size(); k++)
                    if(used_groups[first_member[args[j][k]]])
                    {
                        overlapped_params += members.size();
                        break;
                    }

                for(size_t k = 0; k < args[j].size(); k++)
                    used_groups[first_member[args[j][k]]] = 1;
            }
        }
    }

    double p1 = 1.0;
    double p2 = 0.5;
    double p3 = 0.5;
    double p4 = 0.5;

    if(print)
    {
        std::cout<<distinct_groups<<"\t"<<opcode_mismatches<<"\t"
                 <<param_mismatches<<"\t"<<overlapped_params<<"\n";
    }

    return 1000000000.0 / pow(p1 * distinct_groups + p2 * opcode_mismatches
                            + p3 * param_mismatches + p4 * overlapped_params, 3);
}

void Match::print_constraints_line(std::ostream& ostr,std::string name,Instruction op) const
{
    ostr<<"{"<<name<<"} is ";
    switch(op) {
    case Instruction::cnst:  ostr<<"constant";           break;
    case Instruction::param: ostr<<"an argument";        break;
    case Instruction::icmp:  ostr<<"icmp instruction";   break;
    case Instruction::br:    ostr<<"branch instruction"; break;
    case Instruction::phi:   ostr<<"phi instruction";    break;
    case Instruction::add:   ostr<<"add instruction";    break;
    case Instruction::mul:   ostr<<"mul instruction";    break;
    case Instruction::zext:  ostr<<"zext instruction";   break;
    case Instruction::gep:   ostr<<"gep instruction";    break;
    case Instruction::load:  ostr<<"load instruction";   break;
    case Instruction::fmul:  ostr<<"fmul instruction";   break;
    case Instruction::fadd:  ostr<<"fadd instruction";   break;
    case Instruction::fsub:  ostr<<"fsub instruction";   break;
    case Instruction::ret:   ostr<<"parameter";          break;
    }
}

void Match::print_constraints(const Graph& g, std::ostream& ostr) const
{
    std::map<size_t,std::string> group_names;

    for(size_t i = 0; i < first_member.size(); i++)
    {
        if(first_member[i] == i)
        {
            std::string name;
            std::stringstream sstr(name);

            sstr<<(char)('A'+(i/10))<<(char)('A'+(i%10));

            for(auto c : g.nodes[i].name)
                if(isalnum(c)) sstr<<c;

            group_names[i] = sstr.str();
        }
    }

    for(size_t i = 0; i < first_member.size(); i++)
    {
        if(first_member[i] == i)
        {
            std::vector<size_t> members = get_closure(i);

            if(members.size() == 1) continue;

            std::vector<Instruction> opcodes = g.get_opcodes(members);
            size_t uniques = std::distance(opcodes.begin(), std::unique(opcodes.begin(), opcodes.end()));

            bool skip = false;
            for(auto op : opcodes)
                if(op == Instruction::param || op == Instruction::br ||
                   op == Instruction::cnst || op == Instruction::ret) skip = true;
            if(skip) continue;

            ostr<<((uniques>1)?"  ( ":"  ");
            for(size_t j = 0; j < uniques; j++)
            {
                print_constraints_line(ostr, group_names[i], opcodes[j]);
                ostr<<((j+1 == uniques)?((j==0)?"":")"):" or\n    ");
            }
            ostr<<" and\n";

            std::vector<std::vector<size_t>> args = g.get_arguments(members);

            if(uniques == 1 && (opcodes[0] == Instruction::fadd ||
                                opcodes[0] == Instruction::fmul ||
                                opcodes[0] == Instruction::add ||
                                opcodes[0] == Instruction::mul ||
                                opcodes[0] == Instruction::phi ||
                                opcodes[0] == Instruction::icmp))
            {
                ostr<<"  ( (";
                bool first = true;
                for(size_t j = 0; j < args.size(); j++)
                {
                    if(args[j].size() == members.size() && is_closed(args[j]))
                    {
                        ostr<<(first?" ":" and\n      ");
                        ostr<<"{"<<group_names[first_member[args[j][0]]]<<"} is ";
                        switch(j) {
                        case 0: ostr<<"first";  break;
                        case 1: ostr<<"second"; break;
                        case 2: ostr<<"third";  break;
                        case 3: ostr<<"fourth"; break;
                        }
                        ostr<<" argument of {"<<group_names[i]<<"}";
                        first = false;
                    }
                }
                ostr<<") or\n    (";
                first = true;
                for(size_t j = 0; j < args.size(); j++)
                {
                    if(args[j].size() == members.size() && is_closed(args[j]))
                    {
                        ostr<<(first?" ":" and\n      ");
                        ostr<<"{"<<group_names[first_member[args[j][0]]]<<"} is ";
                        switch(1-j) {
                        case 0: ostr<<"first";  break;
                        case 1: ostr<<"second"; break;
                        case 2: ostr<<"third";  break;
                        case 3: ostr<<"fourth"; break;
                        }
                        ostr<<" argument of {"<<group_names[i]<<"}";
                        first = false;
                    }
                }
                ostr<<")) and\n";
            }
            else
            {
                for(size_t j = 0; j < args.size(); j++)
                {
                    if(args[j].size() == members.size() && is_closed(args[j]))
                    {
                        ostr<<"  {"<<group_names[first_member[args[j][0]]]<<"} is ";
                        switch(j) {
                        case 0: ostr<<"first";  break;
                        case 1: ostr<<"second"; break;
                        case 2: ostr<<"third";  break;
                        case 3: ostr<<"fourth"; break;
                        }
                        ostr<<" argument of {"<<group_names[i]<<"} and\n";
                    }
                }
            }
        }
    }
}

int main()
{
    Graph graph = first_graph;
    graph.add(second_graph);

    std::vector<Match> matches;
    for(int i = 0; i < 50; i++)
    {
        matches.emplace_back(graph.nodes.size());
    }

    std::vector<Match> matches_new(400, graph.nodes.size());

    for(size_t i = 0; i < 1000; i++)
    {
        for(size_t j = 0; j < matches_new.size(); j++)
        {
            matches_new[j] = matches[j%matches.size()];

            switch(rand() % 10){
            case 0:
            {
                size_t a = rand() % graph.nodes.size();
                size_t b = rand() % graph.nodes.size();
                while(graph.nodes[a].op != graph.nodes[b].op)
                    b = rand() % graph.nodes.size();
                matches_new[j].merge(a,b);
            } break;
            case 1:
            {
                size_t a = rand() % graph.nodes.size();

                while(graph.nodes[a].edges.size() == 0)
                    a = rand() % graph.nodes.size();

                size_t arg = rand() % graph.nodes[a].edges.size();
                for(auto e : matches_new[j].get_closure(a))
                    if(graph.nodes[e].edges.size() > arg)
                        matches_new[j].merge(graph.nodes[a].edges[arg],
                                             graph.nodes[e].edges[arg]);
            } break;
            case 2:
            {
                size_t a = rand() % graph.nodes.size();

                for(auto e : matches_new[j].get_closure(a))
                    matches_new[j].separate(e);
            }}
        }

        double score_sum = 0.0;
        double score_max = 0.0;
        double score_min = 1.0/0.0;
        size_t max_pos = 0;
        size_t min_pos = 0;
        std::vector<double> scores;

        for(auto& match : matches_new)
        {
            double score = match.evaluate(graph);

            score_sum += score;
            if(score > score_max) { score_max = score; max_pos = scores.size(); }
            if(score < score_min) { score_min = score; min_pos = scores.size(); }
            scores.push_back(score_sum);
        }

        double sampled_sum = 0.0;
        for(size_t j = 0; j < matches.size(); j++)
        {
            size_t sample_pos = 0;

            if(j == 0)
            {
                sample_pos = max_pos;
            }
            else
            {
                double sample_value = ((double)rand() / (double)RAND_MAX) * score_sum;
                for(size_t k = 0; k < scores.size(); k++)
                {
                    if(sample_value <= scores[k]) {
                        sample_pos = k;
                        break;
                    }
                }
            }

            sampled_sum += scores[sample_pos] - ((sample_pos==0)?0:scores[sample_pos-1]);
            matches[j] = matches_new[sample_pos];
        }

        double avg_score   = score_sum / (double)matches_new.size();
        double avg_sampled = sampled_sum / (double)matches.size();

        std::cout<<"Iteration "<<i
                 <<": average score = "<<(int)avg_score
                 <<", average sampled = "<<(int)avg_sampled
                 <<", min score = "<<(int)score_min
                 <<", max score = "<<(int)score_max<<"\n";
    }

    double max_score = 0.0;
    size_t max_pos = 0;

    for(size_t i = 0; i < matches.size(); i++)
    {
        double score = matches[i].evaluate(graph);

        std::cout<<" "<<i<<": "<<score<<std::endl;
        if(score > max_score)
        {
            max_score = score;
            max_pos = i;
        }
    }

    double score = matches[max_pos].evaluate(graph, true);

    std::cout<<"Result: max score = "<<(int)max_score<<"\n";

    std::cout<<"Graph:\n";
    graph.print(std::cout);

    std::cout<<"Groups: \n";
    for(size_t i = 0; i < matches[max_pos].first_member.size(); i++)
    {
        if(matches[max_pos].first_member[i] == i)
        {
            std::cout<<"  { ";
            for(size_t j = i; j < matches[max_pos].first_member.size(); j++)
                if(matches[max_pos].first_member[j] == i)
                    std::cout<<j<<"["<<graph.nodes[j].name<<"] ";
            std::cout<<"}\n";
        }
    }

    std::cout<<"Constraints:\n";
    matches[max_pos].print_constraints(graph, std::cout);
}
