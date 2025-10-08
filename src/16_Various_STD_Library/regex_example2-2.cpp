// 휴대폰 번호가 유효할 경우 중간 자리만 따로 추출하기 (std::regex_match 사용)
#include <iostream>
#include <regex>
#include <vector>

int main() {
    std::vector<std::string> phone_numbers = {
        "010-1234-5678", "010-123-4567", "011-1234-5567", "010-12345-6789", "123-4567-8901", "010-1234-567"
    };
    std::regex re("[01]{3}-(\\d{3,4})-\\d{4}");
    std::smatch match;

    for (const auto& number : phone_numbers) {
        if (std::regex_match(number, match, re)) {
            for (int i = 0; i < match.size(); ++i) {
                std::cout << "Match : " << match[i].str() << '\n';
            }
            std::cout << "--------------------------\n";
        }
    }

    return 0;
}