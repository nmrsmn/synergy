// Created by Niels Marsman on 17-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#ifndef SANDBOX_HELPERS_H
#define SANDBOX_HELPERS_H

#include <tuple>

namespace stdext
{
    struct pair_hash
    {
        template <class T1, class T2>
        std::size_t operator() (const std::pair<T1, T2>& pair) const
        {
            return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
        };
    };
}

#endif
