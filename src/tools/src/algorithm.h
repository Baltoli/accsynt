#pragma once

#include "match.h"

#include <iostream>
#include <type_traits>
#include <vector>

void compute(std::vector<Graph> rest);

void compute_impl(Graph graph);

template <typename G, typename... Gs>
auto compute(G graph, Gs... rest)
    -> std::enable_if_t<std::is_same_v<std::common_type_t<G, Gs...>, Graph>,
        void>
{
  (graph.add(rest), ...);
  compute_impl(graph);
}
