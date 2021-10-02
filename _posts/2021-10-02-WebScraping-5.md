---
layout: post
title: "[웹 스크래핑] BeautifulSoup4 #1"
subtitle: "네이버 웹툰"
categories: data
tags: web-scraping
---

# 필요한 모듈 설치

`pip install beautifulsoup4`를 통해서 `BeautifulSoup`을 설치

`pip install lxml` : 구문 분석 파서

---

# Webtoon page 불러오기

```py
import requests
from bs4 import BeautifulSoup

url = "https://comic.naver.com/webtoon/weekday"
res = requests.get(url)
res.raise_for_status()

soup = BeautifulSoup(res.text, "lxml")
```

네이버 웹툰 페이지의 내용을 담아와서 soup이라는 변수에 넣는다.

## title 태그 출력

```py
print(soup.title)
print(soup.title.get_text())
```

웹툰 페이지에서 title태그에 있는 내용을 출력해본다. `get_text()`를 사용하면 태그말고 text 정보만 출력할 수 있다.

## a 태그 사용 실습

```py
print(soup.a)
```

하나의 html파일에서 여러개가 나오는 태그를 출력해보면 첫 번째로 발견하는 a 태그에 관련된 정보를 출력해분다.

```py
print(soup.a.attrs)
# 출력 : {'href': '#menu', 'onclick': "document.getElementById('menu').tabIndex=-1;document.getElementById('menu').focus();return false;"}

print(soup.a["href"])
# 출력 : #menu
```

`attrs`를 통해서 속성값을 딕셔너리 형태로도 출력할 수 있다. 또한 딕셔너리형태이기 때문에 key값을 이용해서 value도 따로 출력할 수 있다.

## find 함수

```py
print(soup.find("a", attrs={"class":"Nbtn_upload"})) # class = "Nbtn_upload"인 a element를 찾아라
print(soup.find(attrs={"class":"Nbtn_upload"})) # class = "Nbtn_upload"인 어떤 element를 찾아라
```

`find`함수를 이용해서 `attrs`로 속성을 지정해서 태그를 찾을 수도 있다.

## 인기급상승 만화 정보 찾기

```py
rank1 = soup.find("li", attrs={"class":"rank01"})
print(rank1.a)
print(rank1.a.get_text())
```

`class`가 `rank01`인 `li`태그를 가진 내용을 찾아서 rank1에 넣고 그 내용중에서 `a태그`의 내용을 찾아서 출력해본다.

`get_text()`를 사용해서 태그 전체가 아닌 text 내용만 출력해볼 수도 있다.

```py
rank2 = rank1.next_sibling.next_sibling
rank3 = rank2.next_sibling.next_sibling
```

`next_sibling`을 사용해서 형제태그를 찾아서 다음 순위를 찾을 수 있다.

두 번 사용하는 경우는 개행정보가 있기 때문이다.(한 번 사용했을 때 내용이 출력되지 않는다.)

```py
rank2 = rank3.previous_sibling.previous_sibling
```

`previous_sibling`으로 위로 올라가서 찾을 수도 있다.

```py
print(rank1.parent)
```

`parent`태그를 찾아서 출력해보면 `<li></li>`의 parent태그인 `<ol></ol>`태그가 전부 출력된다.

```py
rank2 = rank1.find_next_sibling("li") # next_sibling을 두 번 찾지 않고 li인 것만 찾음
print(rank2.a.get_text())
```

next_sibling을 두 번 쓰지 않고 find_next_sibling()을 통해서 다음 태그를 찾을 수 있다.

rank1의 형제 태그를 모두 찾는 `find_next_siblings`도 있다.

```py
print(rank1.find_next_siblings("li"))
```

여는 태그와 닫는 태그 사이에 있는 text를 이용해서 찾을 수도 있다.

```py
webtoon = soup.find("a", text = "노답소녀-46화")
print(webtoon)
```

---

# 네이버 웹툰 전체 목록 가져오기

요일별 웹툰에서 전체 목록을 가져와보자.

```py
import requests
from bs4 import BeautifulSoup

url = "https://comic.naver.com/webtoon/weekday"
res = requests.get(url)
res.raise_for_status()

soup = BeautifulSoup(res.text, "lxml")
```

먼저 기본 세팅을 해준다.

요일별 웹툰의 제목은 `title` 이라는 클래스를 가진 a태그이기 때문에 여러개를 리스트로 반환해주는 `find_all` 를 쓴다.

```py
cartoons = soup.find_all("a", attrs={"class":"title"}) # 리스트로 반환
```

`title`을 클래스로 가지고 있는 a태그를 모두 cartoons에 담은 뒤에 반복문을 통해서 내용을 출력해준다.

```py
for cartoon in cartoons:
    print(cartoon.get_text())
```
