#include "match.h"

void compute(Graph graph, Graph second_graph)
{
  graph.add(second_graph);

  std::vector<Match> matches;
  for (int i = 0; i < 50; i++) {
    matches.emplace_back(graph.nodes.size());
  }

  std::vector<Match> matches_new(400, graph.nodes.size());

  for (size_t i = 0; i < 1000; i++) {
    for (size_t j = 0; j < matches_new.size(); j++) {
      matches_new[j] = matches[j % matches.size()];

      switch (rand() % 10) {
      case 0: {
        size_t a = rand() % graph.nodes.size();
        size_t b = rand() % graph.nodes.size();
        while (graph.nodes[a].op != graph.nodes[b].op)
          b = rand() % graph.nodes.size();
        matches_new[j].merge(a, b);
      } break;
      case 1: {
        size_t a = rand() % graph.nodes.size();

        while (graph.nodes[a].edges.size() == 0)
          a = rand() % graph.nodes.size();

        size_t arg = rand() % graph.nodes[a].edges.size();
        for (auto e : matches_new[j].get_closure(a))
          if (graph.nodes[e].edges.size() > arg)
            matches_new[j].merge(graph.nodes[a].edges[arg],
                graph.nodes[e].edges[arg]);
      } break;
      case 2: {
        size_t a = rand() % graph.nodes.size();

        for (auto e : matches_new[j].get_closure(a))
          matches_new[j].separate(e);
      }
      }
    }

    double score_sum = 0.0;
    double score_max = 0.0;
    double score_min = 1.0 / 0.0;
    size_t max_pos = 0;
    size_t min_pos = 0;
    std::vector<double> scores;

    for (auto& match : matches_new) {
      double score = match.evaluate(graph);

      score_sum += score;
      if (score > score_max) {
        score_max = score;
        max_pos = scores.size();
      }
      if (score < score_min) {
        score_min = score;
        min_pos = scores.size();
      }
      scores.push_back(score_sum);
    }

    double sampled_sum = 0.0;
    for (size_t j = 0; j < matches.size(); j++) {
      size_t sample_pos = 0;

      if (j == 0) {
        sample_pos = max_pos;
      } else {
        double sample_value = ((double)rand() / (double)RAND_MAX) * score_sum;
        for (size_t k = 0; k < scores.size(); k++) {
          if (sample_value <= scores[k]) {
            sample_pos = k;
            break;
          }
        }
      }

      sampled_sum += scores[sample_pos] - ((sample_pos == 0) ? 0 : scores[sample_pos - 1]);
      matches[j] = matches_new[sample_pos];
    }

    double avg_score = score_sum / (double)matches_new.size();
    double avg_sampled = sampled_sum / (double)matches.size();

    std::cout << "Iteration " << i
              << ": average score = " << (int)avg_score
              << ", average sampled = " << (int)avg_sampled
              << ", min score = " << (int)score_min
              << ", max score = " << (int)score_max << "\n";
  }

  double max_score = 0.0;
  size_t max_pos = 0;

  for (size_t i = 0; i < matches.size(); i++) {
    double score = matches[i].evaluate(graph);

    std::cout << " " << i << ": " << score << std::endl;
    if (score > max_score) {
      max_score = score;
      max_pos = i;
    }
  }

  double score = matches[max_pos].evaluate(graph, true);

  std::cout << "Result: max score = " << (int)max_score << "\n";

  std::cout << "Graph:\n";
  graph.print(std::cout);

  std::cout << "Groups: \n";
  for (size_t i = 0; i < matches[max_pos].first_member.size(); i++) {
    if (matches[max_pos].first_member[i] == i) {
      std::cout << "  { ";
      for (size_t j = i; j < matches[max_pos].first_member.size(); j++)
        if (matches[max_pos].first_member[j] == i)
          std::cout << j << "[" << graph.nodes[j].name << "] ";
      std::cout << "}\n";
    }
  }

  std::cout << "Constraints:\n";
  matches[max_pos].print_constraints(graph, std::cout);
}
