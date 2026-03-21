#pragma once

#include "graph.h"
#include <vector>
#include <limits>
#include <stdexcept>
#include <cmath>

namespace ods {
class AdjacencyMatrix : public Graph {
public:
    static constexpr double ABSENT = std::numeric_limits<double>::quiet_NaN();

    explicit AdjacencyMatrix(std::size_t n = 0, bool directed = true)
        : n_(n)
        , edge_count_(0)
        , directed_(directed)
        , mat_(n, std::vector<double>(n, ABSENT)) 
    {}

    std::size_t numVertices() const override { return n_; }
    std::size_t numEdges()    const override { return edge_count_; }

    bool hasEdge(std::size_t u, std::size_t v) const override {
        validate(u); validate(v);
        return !isAbsent(mat_[u][v]);
    }

    double edgeWeight(std::size_t u, std::size_t v) const override {
        validate(u); validate(v);
        if (isAbsent(mat_[u][v])) {
            throw std::out_of_range("AdjacencyMatrix::edgeWeight: No edge exists.");
        }
        return mat_[u][v];
    }

    void addEdge(std::size_t u, std::size_t v, double weight = 1.0) override {
        validate(u); validate(v);
        
        if (isAbsent(mat_[u][v])) {
            edge_count_++;
        }
        
        mat_[u][v] = weight;

        if (!directed_ && u != v) {
            mat_[v][u] = weight;
        }
    }

    void removeEdge(std::size_t u, std::size_t v) override {
        validate(u); validate(v);
        if (!isAbsent(mat_[u][v])) {
            mat_[u][v] = ABSENT;
            edge_count_--;
            if (!directed_ && u != v) {
                mat_[v][u] = ABSENT;
            }
        }
    }

    std::size_t addVertex() override {
        for (auto& row : mat_) {
            row.push_back(ABSENT);
        }
        n_++;
        mat_.push_back(std::vector<double>(n_, ABSENT));
        return n_ - 1;
    }

    void removeVertex(std::size_t v) override {
        validate(v);

        for (std::size_t i = 0; i < n_; ++i) {
            if (!isAbsent(mat_[v][i])) {
                edge_count_--;
            }
            
            if (directed_ && i != v && !isAbsent(mat_[i][v])) {
                edge_count_--;
            }
        }

        mat_.erase(mat_.begin() + v);

        for (auto& row : mat_) {
            row.erase(row.begin() + v);
        }

        n_--;
    }

    std::vector<std::size_t> neighbours(std::size_t u) const override {
        validate(u);
        std::vector<std::size_t> result;
        for (std::size_t v = 0; v < n_; ++v) {
            if (!isAbsent(mat_[u][v])) {
                result.push_back(v);
            }
        }
        return result;
    }

    std::size_t inDegree(std::size_t v) const override {
        validate(v);
        if (!directed_) return outDegree(v);
        std::size_t count = 0;
        for (std::size_t i = 0; i < n_; ++i) {
            if (!isAbsent(mat_[i][v])) count++;
        }
        return count;
    }

    std::size_t outDegree(std::size_t v) const override {
        validate(v);
        std::size_t count = 0;
        for (std::size_t j = 0; j < n_; ++j) {
            if (!isAbsent(mat_[v][j])) count++;
        }
        return count;
    }

    void forEachEdge(std::function<void(std::size_t, std::size_t, double)> f) const override {
        for (std::size_t i = 0; i < n_; ++i) {
            for (std::size_t j = 0; j < n_; ++j) {
                if (!isAbsent(mat_[i][j])) {
                    f(i, j, mat_[i][j]);
                }
            }
        }
    }

private:
    std::size_t n_;
    std::size_t edge_count_;
    bool directed_;
    std::vector<std::vector<double>> mat_;

    inline void validate(std::size_t v) const {
        if (v >= n_) throw std::out_of_range("Vertex index out of range");
    }

    static inline bool isAbsent(double w) {
        return std::isnan(w);
    }
};

} 