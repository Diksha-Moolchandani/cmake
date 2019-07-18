#ifndef PATH_PLANNER_RRT_TREE_TREE_H_
#define PATH_PLANNER_RRT_TREE_TREE_H_

#include <stack>
#include <vector>
#include <array>
#include <iostream>
#include <cmath>
#include <set>
#include <cstdlib>
#include <climits>
#include <cmath>
#include <cerrno>
#include <cfenv>
#include <cstring>
#include "../common/search_space.h"
#include <unordered_map>

namespace kamaz {
namespace hagen {
        class Tree {
            public:
                Tree() = default;
                ~Tree() = default;
                SearchSpace V;
                int v_count = 0;

                template <class T>
                    inline void hash_combine(std::size_t &seed, const T& v){
                        std::hash<T> hasher;
                        seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                }

                template <typename C> struct Hasher{
                    typedef typename C::value_type value_type;
                    inline std::size_t operator() (const C &c) const{
                        std::size_t seed = 0;
                        // size_t h = std::hash<float>()(v[0]);
                        // hash_combine(h, v[1]);
                        // hash_combine(h, v[2]);
                        for(typename C::const_iterator it = c.begin(); it != c.end(); ++it){
                            // hash_combine<value_type>(seed, *it);
                            std::hash<value_type> hasher;
                            seed ^= hasher(*it) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
                        }
                        return seed;
                    }
                };
                
                std::unordered_map<std::array<float, 3>
                                    , Eigen::VectorXf, Hasher<std::array<float, 3>>> E;
                void init(SearchSpace search_space);
        };
    }
}
#endif