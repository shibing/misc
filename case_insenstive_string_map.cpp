#include <map>
#include <string>
#include <iostream>
#include <locale>
#include <utility>


class ignore_case_less
{
    public:
        bool operator()(const std::string& lhs, const std::string& rhs) {
            if (lhs.size() < rhs.size()) {
                return true;
            }
            if (lhs.size() == rhs.size()) {
                for (int i = 0; i < lhs.size(); ++i) {
                    if (std::toupper(lhs[i]) == std::toupper(rhs[i])) {
                        continue;
                    }
                    return lhs[i] < rhs[i];
                }
                return false;
            }
            return true;
        }
};

int main()
{
    std::map<std::string, int, ignore_case_less> m;
    m.insert(std::make_pair<std::string, int>("jack", 21));
    m.insert(std::make_pair<std::string, int>("Jack", 22));
    m.insert(std::make_pair<std::string, int>("bob", 22));
    m.insert(std::make_pair<std::string, int>("BOB", 25));
    for (auto iter = m.begin(); iter != m.end(); ++iter) {
        std::cout << iter->first  << ": " << iter->second << std::endl;
    }
}
