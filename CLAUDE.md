# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Claude 행동 규칙

- 모든 응답은 한국어로 작성한다. 코드, 커밋 메시지, 파일명 등은 예외로 하되, 설명/대화 텍스트는 항상 한국어를 사용한다.
- 도구 실행 시 사용자 승인(approval)이 필요한 모든 경우, 기존 영문 설명 뒤에 괄호로 한국어 설명을 추가한다. Bash, PowerShell 등 모든 도구에 적용.
  - 예: `git push origin master` → `git push origin master (원격 브랜치에 푸시할까요?)`

## Repository Purpose

알고리즘 코딩 테스트 풀이 저장소. 백준 온라인 저지(BOJ), 프로그래머스, 카카오 문제 풀이를 C++ 및 C#으로 작성.

## Build & Run

- **현재 작업 파일**: `Solving/main.cpp` — 새 문제를 여기에 작성
- 각 `.cpp` 파일은 독립적인 콘솔 앱이며, stdin으로 입력받고 stdout으로 출력
- 자동화된 테스트 프레임워크 없음 — 온라인 저지 테스트케이스로 직접 검증.

## Project Structure

```
Cpp_01/      # BOJ, 프로그래머스, 카카오 풀이 (~210개)
Cpp_02/      # 최근 고난이도 BOJ 풀이 (~13개)
Solving/     # 현재 풀고 있는 문제 작업 공간 (main.cpp)
Csharp_01/   # C# 풀이
SolvingCsharp/ # C# 작업 공간
```

## File Naming Convention

`Solving/main.cpp` 풀이 완료 후 `Cpp_02/`에 저장할 때의 규칙.

| 출처 | 형식 | 예시 |
|------|------|------|
| 백준 | `백준[번호]번_[문제명].cpp` | `백준1517번_버블 소트.cpp` |
| 프로그래머스 | `프로그래머스(L[레벨])_[문제명].cpp` | `프로그래머스(L3)_아이템 줍기.cpp` |
| 카카오 | `카카오_[연도]_[문제명].cpp` | `카카오_2023_표현 가능한 이진트리.cpp` |

**문제명 파악 방법**: `Solving/main.cpp` 최상단 주석에서 읽음.
- 형식 예: `// 백준 1517번 : 버블 소트` → `백준1517번_버블 소트.cpp`
- 형식 예: `// 프로그래머스(L3) : 아이템 줍기` → `프로그래머스(L3)_아이템 줍기.cpp`

**규칙:**
- 문제명은 원래 제목 그대로 (공백 유지, 특수문자 제거)
- "번" 반드시 포함 (백준 한정)
- 구분자는 `_` (언더스코어)

## Common Algorithms

주로 다루는 알고리즘:
- 그래프: Dijkstra, BFS/DFS, 위상정렬, Union-Find, MST
- 자료구조: 세그먼트 트리(구간합/최솟값/최솟값 인덱스), Fenwick Tree
- DP: 메모이제이션, 배낭문제, LIS
- 수학: 좌표 압축(`lower_bound`), 소수/소인수분해, 포함-배제, GCD
- 문자열: KMP, 해싱
- 기하: 교차 판정, 볼록 껍질

세그먼트 트리는 `1-based` 인덱스, 노드 번호는 `node*2` / `node*2+1` 패턴 사용.
