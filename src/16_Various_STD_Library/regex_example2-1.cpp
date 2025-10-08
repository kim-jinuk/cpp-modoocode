// 휴대폰 번호가 유효한지 확인하기
// 조건 1. (숫자)-(숫자)-(숫자) 꼴로 있어야 한다.
// 조건 2. 맨 앞자리는 반드시 3자리이며 0과 1로만 이루어져 있어야 한다.
// 조건 3. 가운데 자리는 3자리 혹은 4자리여야 한다.
// 조건 4. 마지막 자리는 4자리여야 한다.
#include <iostream>
#include <regex>
#include <vector>

int main() {
    std::vector<std::string> phone_numbers = {
        "010-1234-5678", "010-123-4567", "011-1234-5567", "010-12345-6789", "123-4567-8901", "010-1234-567"
    };
    std::regex re("[01]{3}-\\d{3,4}-\\d{4}");

    for (const auto& phone_number : phone_numbers) {
        std::cout << phone_number << ": " << std::boolalpha << std::regex_match(phone_number, re) << '\n';
    }

    return 0;
}