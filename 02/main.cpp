#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <cstdlib>
#include <algorithm>

std::vector<std::string> split(const std::string &str, char ch);
void print_ip(const std::vector<std::string> &ip);
std::vector<int> make_int_ip(const std::vector<std::string> &v);
bool ip_comparator_desc(std::vector<std::string> v1, std::vector<std::string> v2);
std::vector<std::vector<std::string>> filter(int first_byte, const std::vector<std::vector<std::string>> &ip_pool);
std::vector<std::vector<std::string>> filter(int first_byte, int second_byte, const std::vector<std::vector<std::string>> &ip_pool);
std::vector<std::vector<std::string>> filter_any(int any_byte, const std::vector<std::vector<std::string>> &ip_pool);

int main() {
    try {
        std::vector<std::vector<std::string>> ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            std::vector<std::string> v = split(line, '\t');
            ip_pool.push_back(split(v[0], '.'));
        }

        // reverse lexicographically sort
        std::sort(ip_pool.begin(), ip_pool.end(), ip_comparator_desc);
//        // print first 3 ips
//        for (int i = 0; i < 3; ++i) {
//            print_ip(ip_pool[i]);
//        }
//        std::cout << "...\n";
//        // print last 3 ips
//        for (auto i = ip_pool.size() - 3; i < ip_pool.size(); ++i) {
//            print_ip(ip_pool[i]);
//        }
        // print all addresses according to assignment
        for (auto ip : ip_pool) {
            print_ip(ip);
        }

        // filter by first byte and output
        auto result = filter(1, ip_pool);
        for (const auto& item : result) {
            print_ip(item);
        }
//        std::cout << "==================\n";

        // filter by first and second bytes and output
        result = filter(46, 70, ip_pool);
        for (const auto& item : result) {
            print_ip(item);
        }
//        std::cout << "==================\n";

        // filter by any byte and output
        result = filter_any(46, ip_pool);
        for (const auto& item : result) {
            print_ip(item);
        }
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}

std::vector<std::string> split(const std::string &str, char ch) {
    std::vector<std::string> result;

    auto stop = str.find_first_of(ch);
    decltype(stop) start = 0;

    while (stop != std::string::npos) {
        result.push_back(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(ch, start);
    }
    result.push_back(str.substr(start, stop - start));

    return result;
}

void print_ip(const std::vector<std::string> &ip) {
    for (auto pos = ip.cbegin(); pos != ip.cend(); ++pos) {
        if (pos != ip.cbegin()) {
            std::cout << ".";
        }
        std::cout << *pos;
    }
    std::cout << std::endl;
}

std::vector<int> make_int_ip(const std::vector<std::string> &v) {
    std::vector<int> r;
    for (auto s : v) {
        r.push_back(std::atoi(s.c_str()));
    }
    return r;
}

bool ip_comparator_desc(std::vector<std::string> v1, std::vector<std::string> v2) {
    return std::make_tuple(make_int_ip(v1)) > std::make_tuple(make_int_ip(v2));
}

std::vector<std::vector<std::string>> filter(int first_byte, const std::vector<std::vector<std::string>> &ip_pool) {
    std::vector<std::vector<std::string>> result;
    for (auto it = ip_pool.cbegin(); it != ip_pool.cend(); ++it) {
        if ((*it).at(0) == std::to_string(first_byte)) {
            result.push_back(*it);
        }
    }
    return result;
}

std::vector<std::vector<std::string>> filter(int first_byte, int second_byte, const std::vector<std::vector<std::string>> &ip_pool) {
    std::vector<std::vector<std::string>> result;
    for (auto it : ip_pool) {
        if (it.at(0) == std::to_string(first_byte) && it.at(1) == std::to_string(second_byte)) {
            result.push_back(it);
        }
    }
    return result;
}

std::vector<std::vector<std::string>> filter_any(int any_byte, const std::vector<std::vector<std::string>> &ip_pool) {
    std::vector<std::vector<std::string>> result;
    for (auto it : ip_pool) {
        if (it.at(0) == std::to_string(any_byte)
            || it.at(1) == std::to_string(any_byte)
            || it.at(2) == std::to_string(any_byte)
            || it.at(3) == std::to_string(any_byte)) {
            result.push_back(it);
        }
    }
    return result;
}
