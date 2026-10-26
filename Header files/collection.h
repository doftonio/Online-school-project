#ifndef COLLECTION_H
#define COLLECTION_H

#include <vector>
#include <optional>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <concepts>
#include <memory>

template <typename T>
class Collection {
private:
    std::vector<T> elements;

    static void printElement(std::ostream& os, const T& item) {
        if constexpr (requires { *item; }) {
            if (item) {
                if constexpr (requires { item->printDetails(); }) {
                    item->printDetails();
                } else if constexpr (requires { os << *item; }) {
                    os << *item;
                } else {
                    os << item;
                }
            } else {
                os << "(null)";
            }
        } else if constexpr (requires { os << item; }) {
            os << item;
        }
    }

public:
    Collection() = default;

    void add(const T& element) requires std::copy_constructible<T> {
        elements.push_back(element);
    }

    void add(T&& element) {
        elements.push_back(std::move(element));
    }

    bool remove(const T& element) requires std::equality_comparable<T> {
        if (const auto it = std::ranges::find(elements, element); it != elements.end()) {
            elements.erase(it);
            return true;
        }
        return false;
    }

    bool removeAt(std::size_t index) {
        if (index >= elements.size()) {
            return false;
        }
        elements.erase(elements.begin() + static_cast<std::ptrdiff_t>(index));
        return true;
    }

    template <typename Predicate>
    std::size_t removeIf(Predicate predicate) {
        const auto originalSize = elements.size();
        std::erase_if(elements, predicate);
        return originalSize - elements.size();
    }

    const T& get(std::size_t index) const {
        return elements.at(index);
    }

    T& get(std::size_t index) {
        return elements.at(index);
    }

    const T& operator[](std::size_t index) const noexcept {
        return elements[index];
    }

    T& operator[](std::size_t index) noexcept {
        return elements[index];
    }

    std::optional<std::size_t> find(const T& element) const requires std::equality_comparable<T> {
        if (const auto it = std::ranges::find(elements, element); it != elements.end()) {
            return static_cast<std::size_t>(std::distance(elements.begin(), it));
        }
        return std::nullopt;
    }

    template <typename Predicate>
    std::optional<std::size_t> findIndex(Predicate predicate) const {
        if (const auto it = std::ranges::find_if(elements, predicate); it != elements.end()) {
            return static_cast<std::size_t>(std::distance(elements.begin(), it));
        }
        return std::nullopt;
    }

    std::size_t size() const noexcept {
        return elements.size();
    }

    bool empty() const noexcept {
        return elements.empty();
    }

    void clear() noexcept {
        elements.clear();
    }

    void print(std::ostream& os = std::cout) const {
        if (elements.empty()) {
            os << "(empty collection)\n";
            return;
        }
        for (std::size_t i = 0; i < elements.size(); ++i) {
            os << "[" << i << "] ";
            printElement(os, elements[i]);
            os << "\n";
        }
    }

    auto begin() noexcept { return elements.begin(); }
    auto end() noexcept { return elements.end(); }
    auto begin() const noexcept { return elements.begin(); }
    auto end() const noexcept { return elements.end(); }
};

template <typename T, typename Predicate>
const T* findByCriterion(const Collection<T>& collection, Predicate criterion) {
    for (std::size_t i = 0; i < collection.size(); ++i) {
        if (criterion(collection[i])) {
            return &collection[i];
        }
    }
    return nullptr;
}

#endif // COLLECTION_H
