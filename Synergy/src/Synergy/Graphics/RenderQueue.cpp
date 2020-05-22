// Created by Niels Marsman on 20-05-2020.
// Copyright © 2020 Niels Marsman. All rights reserved.

#include <numeric>
#include <algorithm>

#include <iostream>

#include "Synergy/Graphics/RenderQueue.h"

namespace Synergy
{
    void RenderQueue::Add(Synergy::RenderQueue::Item item)
    {
        auto material = item.shader->Id();
        
        Synergy::RenderQueue::Key key;
        key.opaque.viewport = 1;
        key.opaque.viewportLayer = 1;
        key.opaque.layer = 1;
        key.opaque.transparancy = item.transparent;
        
        if (item.transparent)
        {
            key.transparent.depth = 0 - item.position.z;
            key.transparent.material = material;
        }
        else
        {
            key.opaque.depth = item.position.z;
            key.opaque.material = material;
        }
        
        m_Items.push_back(item);
        m_SortingKeys.push_back(key);
    }

    void RenderQueue::Reset()
    {
        m_Items.clear();
        m_SortedItems.clear();
        m_SortingKeys.clear();
    }

    std::vector<Synergy::RenderQueue::Item> RenderQueue::Sort()
    {
        std::vector<uint64_t> results(m_SortingKeys.size());
        std::iota(results.begin(), results.end(), 0);

        std::stable_sort(results.begin(), results.end(), [this](uint64_t first, uint64_t second)
        {
            return m_SortingKeys[first].value < m_SortingKeys[second].value;
        });
        
        for (auto i : results)
        {
            m_SortedItems.push_back(m_Items[i]);
        }
        
        return m_SortedItems;
    }
}
