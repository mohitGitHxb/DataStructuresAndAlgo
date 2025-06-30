#ifndef CONTAINER_PRINTER_HPP
#define CONTAINER_PRINTER_HPP

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <deque>
#include <list>
#include <forward_list>
#include <tuple>
#include <type_traits>

class ContainerPrinter
{
public:
    // Primary template for generic container printing
    template <typename Container>
    static void print(const Container &container,
                      const std::string &name = "Container",
                      std::ostream &os = std::cout)
    {
        os << name << ": [";
        printContainerElements(container, os);
        os << " ]" << std::endl;
    }

    // Specialization for 2D vectors
    template <typename T>
    static void print(const std::vector<std::vector<T>> &matrix,
                      const std::string &name = "2D Vector",
                      std::ostream &os = std::cout)
    {
        os << name << ": [" << std::endl;
        for (size_t i = 0; i < matrix.size(); ++i)
        {
            os << "  Row " << i << ": [ ";
            printContainerElements(matrix[i], os);
            os << " ]" << std::endl;
        }
        os << "]" << std::endl;
    }

    // Specialization for maps and unordered_maps
    template <typename Key, typename Value>
    static void print(const std::map<Key, Value> &map,
                      const std::string &name = "Map",
                      std::ostream &os = std::cout)
    {
        os << name << ": {" << std::endl;
        for (const auto &[key, value] : map)
        {
            os << "  " << key << " : " << value << std::endl;
        }
        os << "}" << std::endl;
    }

    template <typename Key, typename Value>
    static void print(const std::unordered_map<Key, Value> &map,
                      const std::string &name = "Unordered Map",
                      std::ostream &os = std::cout)
    {
        os << name << ": {" << std::endl;
        for (const auto &[key, value] : map)
        {
            os << "  " << key << " : " << value << std::endl;
        }
        os << "}" << std::endl;
    }

    // Specialization for stack
    template <typename T, typename Container = std::deque<T>>
    static void print(const std::stack<T, Container> &stk,
                      const std::string &name = "Stack",
                      std::ostream &os = std::cout)
    {
        os << name << ": [";
        std::stack<T, Container> tempStack = stk;
        bool first = true;

        // Create a temporary stack to preserve original order
        std::vector<T> elements;
        while (!tempStack.empty())
        {
            elements.push_back(tempStack.top());
            tempStack.pop();
        }

        // Print in original order (bottom to top)
        for (auto it = elements.rbegin(); it != elements.rend(); ++it)
        {
            if (!first)
                os << ", ";
            first = false;
            os << *it;
        }

        os << " ]" << std::endl;
    }

    // Specialization for queue
    template <typename T, typename Container = std::deque<T>>
    static void print(const std::queue<T, Container> &q,
                      const std::string &name = "Queue",
                      std::ostream &os = std::cout)
    {
        os << name << ": [";
        std::queue<T, Container> tempQueue = q;
        bool first = true;

        while (!tempQueue.empty())
        {
            if (!first)
                os << ", ";
            first = false;
            os << tempQueue.front();
            tempQueue.pop();
        }

        os << " ]" << std::endl;
    }

    // Specialization for priority_queue
    template <typename T, typename Container = std::vector<T>, typename Compare = std::less<T>>
    static void print(const std::priority_queue<T, Container, Compare> &pq,
                      const std::string &name = "Priority Queue",
                      std::ostream &os = std::cout)
    {
        os << name << ": [";
        std::priority_queue<T, Container, Compare> tempPQ = pq;
        bool first = true;

        while (!tempPQ.empty())
        {
            if (!first)
                os << ", ";
            first = false;
            os << tempPQ.top();
            tempPQ.pop();
        }

        os << " ]" << std::endl;
    }

private:
    // Helper function to print container elements
    template <typename Container>
    static void printContainerElements(const Container &container,
                                       std::ostream &os)
    {
        bool first = true;
        for (const auto &elem : container)
        {
            if (!first)
                os << ", ";
            first = false;

            // Handle nested containers or special types
            if constexpr (is_printable_container_v<decltype(elem)>)
            {
                os << "[";
                printContainerElements(elem, os);
                os << "]";
            }
            else
            {
                os << elem;
            }
        }
    }

    // Expanded type trait to check if a type is a printable container
    template <typename T>
    struct is_printable_container : std::false_type
    {
    };

    // Add support for more containers
    template <typename T, typename Alloc>
    struct is_printable_container<std::vector<T, Alloc>> : std::true_type
    {
    };

    template <typename T, typename Alloc>
    struct is_printable_container<std::list<T, Alloc>> : std::true_type
    {
    };

    template <typename T, typename Alloc>
    struct is_printable_container<std::deque<T, Alloc>> : std::true_type
    {
    };

    template <typename T, typename Alloc>
    struct is_printable_container<std::forward_list<T, Alloc>> : std::true_type
    {
    };

    template <typename T, typename Comp, typename Alloc>
    struct is_printable_container<std::set<T, Comp, Alloc>> : std::true_type
    {
    };

    template <typename T, typename Comp, typename Alloc>
    struct is_printable_container<std::multiset<T, Comp, Alloc>> : std::true_type
    {
    };

    template <typename T, typename Comp, typename Alloc>
    struct is_printable_container<std::unordered_set<T, Comp, Alloc>> : std::true_type
    {
    };

    template <typename Key, typename Value, typename Comp, typename Alloc>
    struct is_printable_container<std::map<Key, Value, Comp, Alloc>> : std::true_type
    {
    };

    template <typename Key, typename Value, typename Hash, typename Pred, typename Alloc>
    struct is_printable_container<std::unordered_map<Key, Value, Hash, Pred, Alloc>> : std::true_type
    {
    };

    template <typename T>
    static constexpr bool is_printable_container_v = is_printable_container<std::decay_t<T>>::value;
};

// Convenience function for easy printing
template <typename Container>
void printContainer(const Container &container,
                    const std::string &name = "Container",
                    std::ostream &os = std::cout)
{
    ContainerPrinter::print(container, name, os);
}

#endif // CONTAINER_PRINTER_HPP