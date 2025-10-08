// 원하는 패턴을 치환하기 (std::regex_replace 사용)
#include <iostream>
#include <regex>

int main() {
    std::string html = R"(
 <div class="social-login">
    <div class="small-comment">다음으로 로그인</div>
    <div>
        <i class="xi-facebook-official fb-login"></i>
        <i class="xi-google-plus goog-login"></i>
    </div>
 </div>
 <div class="manual">
    <div class="small-comment">
        또는직접입력하세요(댓글수정시비밀번호가필요합니다)
        </div>
        <input name="name" id="name" placeholder="이름">
        <input name="password" id="password" type="password"
 placeholder="비밀번호">
    </div>
    <div id="adding-comment" class="sk-fading-circle">
        <div class="sk-circle1 sk-circle">a</div>
        <div class="sk-circle2 sk-circle">b</div>
        <div class="sk-circle3 sk-circle">asd</div>
        <div class="sk-circle4 sk-circle">asdfasf</div>
        <div class="sk-circle5 sk-circle">123</div>
        <div class="sk-circle6 sk-circle">aax</div>
        <div class="sk-circle7 sk-circle">sxz</div>
    </div>
 )";
    
    std::regex re(R"r(sk-circle(\d))r");
    std::smatch match;

    std::string modified_html = std::regex_replace(html, re, "$1-sk-circle");
    std::cout << modified_html;

    // 치환된 문자열 객체 modified_html 생성 없이, 바로 치환된 문자열 출력하기 (std::regex_replace 오버로딩)
    // std::regex_replace(std::ostreambuf_iterator<char>(std::cout), html.begin(), html.end(), re, "$1-sk-circle");

    return 0;
}