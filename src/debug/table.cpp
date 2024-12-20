#include "table.hpp"

namespace spade
{
    DataTable::DataTable(const string &title, const vector<string> &args) : title(title), keys(args), data(), width(0) {
        for (const auto &arg: args) { data[arg] = {}; }
    }

    string DataTable::toString() const {
        std::stringstream out;
        vector<size_t> maxes;
        string separator;
        vector<vector<string>> valuesVector;

        // Initialize the maxes and keys
        size_t j = 0;
        for (const auto &values: data | std::views::values) {
            valuesVector.push_back(values);
            size_t max = keys[j].length();
            for (const auto &value: values) {
                if (value.length() > max) max = value.length();
            }
            maxes.push_back(max);
            j++;
        }

        // Build the separator
        separator += '+';
        for (auto max: maxes) separator += string(max + 2, '-') + '+';
        separator += '\n';

        // Build the string
        // Append the title
        out << title << '\n';
        // Append the separator
        out << separator;
        // Append the header
        out << '|';
        for (int i = 0; i < maxes.size(); ++i) { out << std::format(" {: <{}} ", keys[i], maxes[i]) << '|'; }
        out << '\n';
        out << separator;

        // Append the rows
        for (int i = 0; i < width; ++i) {
            out << '|';
            int k = 0;
            for (auto values: valuesVector) {
                auto value = values[i];
                out << std::format(" {:{}} ", isNumber(value) ? padRight(value, maxes[k]) : padLeft(value, maxes[k])) << '|';
                k++;
            }
            out << '\n';
        }
        out << separator;
        return out.str();
    }

    std::ostream &operator<<(std::ostream &os, const DataTable &table) { return os << table.toString() << '\n'; }
} // namespace spade
