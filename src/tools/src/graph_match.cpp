#include "match.h"

#include <iostream>

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

void compute(Graph graph, Graph second_graph)
{
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

int main()
{
  compute(first_graph, second_graph);
}
