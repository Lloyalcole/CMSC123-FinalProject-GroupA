#pragma once

#include <vector>
#include <cstddef>
#include <functional>

namespace ods {

class Graph {
public:
    virtual ~Graph() = default;

    virtual std::size_t numVertices() const = 0;
    virtual std::size_t numEdges() const = 0;

    virtual bool hasEdge(std::size_t u, std::size_t v) const = 0;
    virtual double edgeWeight(std::size_t u, std::size_t v) const = 0;

    virtual void addEdge(std::size_t u, std::size_t v, double weight = 1.0) = 0;
    virtual void removeEdge(std::size_t u, std::size_t v) = 0;

    virtual std::size_t addVertex() = 0;
    virtual void removeVertex(std::size_t v) = 0;

    // Use consistent naming (some libraries use "neighbors")
    virtual std::vector<std::size_t> neighbours(std::size_t u) const = 0;

    virtual std::size_t inDegree(std::size_t v) const = 0;
    virtual std::size_t outDegree(std::size_t v) const = 0;

    virtual void forEachEdge(std::function<void(std::size_t, std::size_t, double)> f) const = 0;
};

} 