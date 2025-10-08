// 원하는 패턴을 검색하기 (std::regex_search 사용)
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
    
    std::regex re(R"(<div class="sk[\w -]*">\w*</div>)");
    std::smatch match;

    while (std::regex_search(html, match, re)) {
        std::cout << match.str() << '\n';
        html = match.suffix();
    }

    return 0;
}