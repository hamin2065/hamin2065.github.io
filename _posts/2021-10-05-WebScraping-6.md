---
layout: post
title: "[웹 스크래핑] BeautifulSoup4 #2"
subtitle: "네이버 웹툰 - 가우스 전자"
categories: data
tags: web-scraping
---

# 가우스 전자 페이지에서 제목과 링크 가져오기

네이버 웹툰 홈페이지에 들어가서 `가우스 전자`를 검색한다. 검색해서 나오는 결과를 클릭하면 하나의 페이지에 여러개의 회차가 나열된 것을 볼 수 있다.

```py
import requests
from bs4 import BeautifulSoup

url = "https://comic.naver.com/webtoon/list?titleId=675554"

res = requests.get(url)
res.raise_for_status()

soup = BeautifulSoup(res.text, "lxml")
```

기본세팅을 먼저 해준다.

HTML을 검사해보면 a 태그에 class가 없기 때문에 부모 element인 `td`를 이용해서 그 밑의 a태그를 가져온다.

```py
cartoons = soup.find_all("td",attrs={"class":"title"})
title = cartoons[0].a.get_text()
link = cartoons[0].a["href"]

print(title)
print("https://comic.naver.com"+link)
```

출력해보면 제일 위의 회차의 제목과 링크가 출력이 된다. 링크는 생략된 링크를 미리 써주고 불러와야지 출력된 값으로 접속이 가능하다.

```py
# 만화제목과 링크 가져오기
for cartoon in cartoons:
    title = cartoon.a.get_text()
    link = "https://comic.naver.com"+cartoon.a["href"]
print(title, link)
```

반복문을 통해서 페이지 전체의 회차와 링크를 가져온다.

---

# 가우스 전자 평점 가져오기

```py
# 평점 가져오기
total_rates = 0
cartoons = soup.find_all("div",attrs={"class" : "rating_type"})
for cartoon in cartoons:
    rate = cartoon.find("strong").get_text()
    print(rate)
    total_rates += float(rate)
print("전체 점수 :",total_rates)
print("평균 점수 : ",total_rates/len(cartoons))
```

`rating_type`의 클래스를 가지고 있는 `div`태그를 전부 찾아서 cartoons라는 변수에 넣고 그 안에서 `strong`의 텍스트 부분을 찾아서 rate에 넣어서 반복문을 통해 전부 출력한다.

`total_rates`를 처음에 0으로 초기화시켜놓고 rate를 float 형태로 바꿔서 더해주면 전체 점수를 구할 수 있고, cartoons의 길이로 나눠주면 평균 점수를 구할 수 있다.
