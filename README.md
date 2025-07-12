# C++ 모도코드 스터디 🚀

**목표**  
- Modoocode PDF 교재를 따라가며 C++ 기본기 강화  
- 실습/메모를 깔끔하게 버전 관리  
- CI로 자동 빌드·테스트 파이프라인 경험

## 레포 구조
```text
.
├── docs/            # 참고자료 요약
├── notes/           # 챕터별 개념 정리
├── src/             # 실습 코드
├── test/            # 단위 테스트
├── .github/workflows# GitHub Actions
└── CMakeLists.txt   # 최상위 빌드 스크립트
```

## 빠른 시작
```bash
git clone <repo-url>
cd cpp-modoocode-study
mkdir build && cd build
cmake ..
cmake --build .
ctest         # 단위 테스트
```
