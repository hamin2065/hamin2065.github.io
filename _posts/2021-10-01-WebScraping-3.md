---
layout: post
title: "[웹 스크래핑] 정규식"
subtitle:
categories: data
tags: web-scraping
---

# 정규식(regular expressions)이란?

정해진 형태를 의미하는 식

ex)

주민등록번호 111111-111111

이메일주소 hamin2065@gmail.com

차량번호 11가 1234

IP 주소 192.168.0.1

위 식들은 알맞은 형태가 있다. 이러한 식들이 알맞은 형식을 갖추고 있는지 확인할 때 우리는 흔히 정규식을 사용한다.

# compile, match

```py
import re

# abcd, book, desk
# ca?e
# care, cafe, case, cave
# caae, cabe, cace, ...

p = re.compile("ca.e")

m = p.match("case")
print(m.group())
```

- `.` (ca.e): 하나의 문자를 의미 > care, cafe, case(o) | caffe (x)
- `^` (^de): 문자열의 시작 -> desk, destination(o) | fade(x)
- `$` (se$) : 문자열의 끝 > case, base(o) | face(x)

위의 내용을 출력해보면 `case`가 출력이 된다.
case가 compile 함수에 넣은 "ca.e"가 매칭이 되어서 그 내용을 출력을 해준것이다.

```py
import re

p = re.compile("ca.e")

m = p.match("caffe")
print(m.group())
```

위의 코드처럼 매칭되지 않는 단어를 매칭시켜보면 에러가 발생한다.

에러가 발생하면 코드가 중단되기 때문에 이를 함수로 만들어준다.

```py
def print_match(m):
    if m:print(m.group())
    else:print("매칭되지 않음")

m = p.match("care")
print_match(m)
```

이 때, match 안에 `careless`를 넣으면 care가 출력이 된다.
이는 match가 주어진 문자열의 처음부터 일치하는지 확인하기 때문인데 `careless`를 앞에부터 실행해서 `care`가 주어진 문자열과 일치하기 때문에 뒤의 `less`는 관여하지 않고 매칭이 된다.

# search

`search`함수는 주어진 문자열 중에 일치하는게 있는지 확인한다.

```py
import re

p = re.compile("ca.e")

def print_match(m):
    if m:print(m.group())
    else:print("매칭되지 않음")

m = p.search("good care")
print_match(m)
```

`good care`의 문자열 안에 `ca.e`와 매칭되는 문자열이 있기 때문에 `care`가 출력이 된다.

`print_match`함수 안에 다양한 함수를 넣어서 출력해본다.

```py
import re

p = re.compile("ca.e")

def print_match(m):
    if m:
        print("m.group() :", m.group()) # 일치하는 문자열 반환
        print("m.string :", m.string) # 입력받은 문자열
        print("m.start() :",m.start()) # 일치하는 문자열의 시작 index
        print("m.end() :",m.end()) # 일치하는 문자열의 끝 index
        print("m.span() :",m.span()) # 일치하는 문자열의 시작 / 끝 index

    else:print("매칭되지 않음")

m = p.search("good care")
print_match(m)
```

> m.group() : care
>
> m.string : good care
>
> m.start() : 5
>
> m.end() : 9
>
> m.span() : (5, 9)

# findall

`findall`은 일치하는 모든 것을 리스트 형태로 반환한다.

```py
lst = p.findall("careless")
print(lst)
```

리스트 형태로 반환하기 때문에 `lst`라는 변수에 담고 출력해보면

> ['care']
> 가 출력이 된다.

```py
lst = p.findall("good care cafe")
print(lst)
```

모든 것을 반환하기 때문에 2개가 일치되는 경우 제대로 출력되는지 다시 확인해본다.

> ['care', 'cafe]

---

# 정리

1. p = re.compile("원하는 형태")
2. m = p.match("비교할 문자열") : 주어진 문자열의 처음부터 일치하는지 확인
3. m = p.search("비교할 문자열") : 주어진 문자열 중에 일치하는게 있는지 확인
4. lst = p.findall("비교할 문자열") : 일치하는 모든 것을 "리스트" 형태로 반환

원하는 형태 : 정규식
`.` : 하나의 문자를 의미
`^` : 문자열의 시작
`$` : 문자열의 끝
