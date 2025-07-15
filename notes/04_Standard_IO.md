# 04. Standard I/O

## 1. 목차
- C++ 표준 입출력 스트림 구조
- cin, cout, cerr, clog 역할
- 포맷팅과 조작자(manipulators)
- 동기화 해제와 입출력 성능 최적화
- 파일 스트림 기본

---

## 2. 핵심 용어 & 분류
| 개념 | 정의 | 비고 |
|------|------|------|
| **cin / cout** | 표준 입력 / 표준 출력 스트림 | <iostream> |
| **cerr / clog** | 에러 출력 스트림 | cerr 버퍼링 X |
| **Manipulators** | 출력 포맷 제어 | setprecision 등 |
| **Stream Buffer** | 데이터 흐름 저장 버퍼 | streambuf |
| **File Stream** | 파일 입출력 스트림 | ifstream, ofstream |
| **Tie** | 스트림 동기화 연결 | cin.tie(&cout) |

---

## 3. 표준 I/O 설계 포인트

### 3-1 cin / cout 기본 사용
```cpp
int x;
std::cin >> x;
std::cout << "Value: " << x << std::endl;
```

### 3-2 포맷 조작자
```cpp
double pi = 3.14159;
std::cout << std::fixed << std::setprecision(2) << pi;
```

### 3-3 버퍼링 & 동기화 해제
```cpp
std::ios::sync_with_stdio(false);
std::cin.tie(nullptr);
```

### 3-4 파일 스트림
```cpp
std::ofstream ofs("out.txt");
ofs << "Hello file!";
std::ifstream ifs("out.txt");
std::string line; ifs >> line;
```

---

## 4. 대표 예시: 패턴 & Idiom
| 패턴 | 아이디어 | 사례 |
|------|----------|------|
| **RAII** | 파일 핸들 자동 닫기 | ofstream |
| **Chaining** | 연속 출력 | cout << a << b << c |
| **Manipulators** | 출력 포맷 유지 | setprecision |

---

## 5. 표준 I/O 비용 / 관리 포인트
```text
endl         newline + flush
cerr         즉시 출력
sync_off     C IO 혼용 금지
file open    파일 닫기 명시/소멸자
```

---

## 6. 흔한 실수 & Best Practice
- endl 대신 \n 사용하고 flush 직접
- sync_with_stdio(false) → printf/scanf 혼용 금지
- 파일 열기 실패 always 체크
- cin.tie(nullptr)로 flush 억제

---

## 7. 더 읽어볼 것
- cppreference: [Iostreams](https://en.cppreference.com/w/cpp/io)
- Effective C++, Item 34
- Fast IO 패턴: cp, 대용량 데이터
