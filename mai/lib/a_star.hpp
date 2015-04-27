#pragma once

#include <string>
#include <queue>
#include <chrono>
#include "node.hpp"
#include "heuristic_func.hpp"
#include "function_dictionary.hpp"

namespace mai
{
    namespace search
    {
        struct DefaultCostFunc
        {
            auto operator()(mai::search::Node const& node) const -> std::size_t
            {
                return node.path.size();
            }
        };

        //
        //	A* search without Expanded List
        //
        template<typename HeuristicFunc, typename CostFunc = DefaultCostFunc>
        class AStar
        {
            struct Greater
            {
                explicit Greater(std::string const& g): goal(g), h{}, c{} {}
                auto operator()(Node const& lhs, Node const& rhs) const -> bool
                {
                    return h(lhs.state, goal) + c(lhs) > h(rhs.state, goal) + c(rhs);
                }

                const std::string goal;
                const HeuristicFunc h;
                const CostFunc c;
            };

            using Q = std::priority_queue < Node, std::vector<Node>, Greater >;
            using Time = std::chrono::high_resolution_clock;

        public:
            AStar(std::string const& source, std::string const& goal) :
                expansions_{ 0u },
                max_q_length_{ 0u },
                q_{ Greater{ goal } },
                final_path_{},
                running_time_{ 0.0f },
                func_dic_{}
            {
                auto start = Time::now();

                for (q_.push(Node{ source, "" }); !q_.empty(); ++expansions_)
                {
                    auto curr = q_.top(); q_.pop();
                    if (curr.state == goal){ final_path_ = curr.path; goto Done; }
                    for (auto make_child : func_dic_.at(curr.state.find('0'))) q_.push(make_child(curr));
                    if (q_.size() > max_q_length_) max_q_length_ = q_.size();
                }

            Done:
                auto done = Time::now();
                running_time_ = std::chrono::duration<float>(done - start).count();
            }

            auto max_q_length() const -> std::size_t { return max_q_length_; }
            auto running_time() const -> float { return running_time_; }
            auto path() const -> std::string const&{ return final_path_; }
            auto num_of_expansions() const -> std::size_t { return expansions_; }

        private:
            std::size_t expansions_, max_q_length_;
            Q q_;
            std::string final_path_;
            float running_time_;
            const mai::search::FunctionDictionary func_dic_;
        };
    }
}