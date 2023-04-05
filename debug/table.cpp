#include "table.hpp"


DataTable::DataTable(const string &title, const vector<string> &args) : title(title), data(), width(0) {
    for (const auto &arg: args) {
        data[arg] = {};
    }
}

string DataTable::toString() const {
    string out;
    vector<size_t> maxes;
    string separator;
    vector<string> keys;
    vector<vector<string>> valuesVector;

    // Initialize the maxes and keys
    for (auto &[key, values]: data) {
        keys.push_back(key);
        valuesVector.push_back(values);
        size_t max = 0;
        for (const auto &value: values) {
            if (value.length() > max)
                max = value.length();
        }
        maxes.push_back(max);
    }

    // Build the separator
    separator += '+';
    for (auto max: maxes)
        separator += string(max + 2, '-') + '+';
    separator += '\n';

    // Build the string
    // Append the title
    out += title + '\n';
    // Append the separator
    out += separator;
    // Append the header
    out += '|';
    for (int i = 0; i < maxes.size(); ++i) {
        out += format(" %s ", rpad(keys[i], maxes[i]).c_str()) + '|';
    }
    out += '\n';
    out += separator;

    // Append the rows
    for (int i = 0; i < width; ++i) {
        out += '|';
        int k = 0;
        for (auto values: valuesVector) {
            out += format(" %s ", rpad(values[i], maxes[k]).c_str()) + '|';
            k++;
        }
    }
    out += separator;
    return out;
}

std::ostream &operator<<(std::ostream &os, const DataTable &table) {
    return os << table.toString() << '\n';
}
