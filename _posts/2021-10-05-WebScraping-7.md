---
layout: post
title: "[웹 스크래핑] BeautifulSoup4 #3"
subtitle: "쿠팡"
categories: data
tags: web-scraping
---

# 쿠팡 페이지

쿠팡에 접속해서 `노트북`이라고 검색을 한다. 처음에 나오는 첫 번째 페이지의 url은 매우 간단하지만 두 번째 페이지로 넘기는 순간 주소가 엄청 복잡해진다. 이 때 주소에서 `page=2`라는 부분을 찾아서 2를 1로 고쳐보면 우리가 처음에 봤던 페이지가 다시 나타나는 것을 확인할 수 있다.

# HTML의 GET / POST 방식

## GET 방식

누구나 볼 수 있도록 url에 적어서 보내는 방식

예시) https://www.coupang/mp/search?minPrice=1000&maxPrice=100000&page=1

`?`뒤에 변수와 값을 넣어주고 `&`표시로 구분을 한다.

쉽게 페이지 요청가능.

## POST

HTTP BODY 에 보내는 방식

예시) https://www.coupang/mp/search?nadocoding&pw=1234

---

# 쿠팡에서 데이터 불러오기

쿠팡에서 노트북을 검색한 url과 headers를 검색해서 넣어준다.

```py
import requests
import re
from bs4 import BeautifulSoup

url = "https://www.coupang.com/np/search?q=%EB%85%B8%ED%8A%B8%EB%B6%81&channel=user&component=&eventCategory=SRP&trcid=&traid=&sorter=scoreDesc&minPrice=&maxPrice=&priceRange=&filterType=&listSize=36&filter=&isPriceRange=false&brand=&offerCondition=&rating=0&page=1&rocketAll=false&searchIndexingToken=1=6&backgroundColor="
headers = {"User-Agent":""}
res = requests.get(url,headers=headers)
res.raise_for_status()
soup = BeautifulSoup(res.text,"lxml")
```

이 때, 검색한 항목에 대해서 하나의 페이지에 있는 모든 정보를 가져오기 위해서 정규식 표현을 써서 `search-product`로 끝나는 class를 가진 `li`태그를 전부 `items`에 넣는다.

```py
items = soup.find_all("li", attrs={"class":re.compile("^search-product")})
```

여러 개를 찾았기 때문에 for문을 통해서 각각 item에 대해서 처리를 해준다.

```py
for item in items:

    # 무료 배송제품은 제외한다.
    ad_badge = item.find("span",attrs={"class":re.compile("^badge-delivery")})
    if ad_badge:
        print(" <무료 배송 상품 제외합니다.>")
        continue

    # 평점이 4.5 이상, 리뷰가 100개넘는 것들만 출력
    name = item.find("div",attrs={"class":"name"}).get_text()

    # 애플 제품 제외
    if "Apple" in name:
        print(" <Apple 제품 제외합니다.>")
        continue

    price = item.find("strong",attrs={"class":"price-value"}).get_text()
    rate = item.find("em",attrs={"class":"rating"})

    # 평점이 없는 product에 대한 조건문
    if rate:
        rate = rate.get_text()
    else :
        print(" <평점 없는 상품 제외합니다.>")
        continue

    rate_cnt = item.find("span",attrs={"class":"rating-total-count"})

    # 평점 수 없는 product에 대한 조건문
    if rate_cnt :
        rate_cnt = rate_cnt.get_text()
        rate_cnt = rate_cnt[1:-1] # 처음이랑 마지막 index 제외시키기 (45) -> 45로 출력
    else :
        print(" <평점 수 없는 상품 제외합니다.>")
        continue

    if float(rate) >= 4.5 and int(rate_cnt) >= 100:
        print(name, price, rate, rate_cnt)
```

---

# 최근 5개 페이지 검사하기

위에서 했듯이 url에 있는 `page`변수에 다른 값을 넣으면 되기 때문에 url 형식을 바꿔주고 이중 for문을 사용해준다.

상품에 대한 내옹을 더 깔끔하게 출력하고 link도 걸어준다.

**전체코드**

```py
import requests
import re
from bs4 import BeautifulSoup

headers = {"User-Agent":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/93.0.4577.82 Safari/537.36"}

for i in range(1,6):
    print(f"{i}번째 페이지")
    url = "https://www.coupang.com/np/search?q=%EB%85%B8%ED%8A%B8%EB%B6%81&channel=user&component=&eventCategory=SRP&trcid=&traid=&sorter=scoreDesc&minPrice=&maxPrice=&priceRange=&filterType=&listSize=36&filter=&isPriceRange=false&brand=&offerCondition=&rating=0&page={}&rocketAll=false&searchIndexingToken=1=6&backgroundColor=".format(i)

    res = requests.get(url,headers=headers)
    res.raise_for_status()
    soup = BeautifulSoup(res.text,"lxml")
    items = soup.find_all("li", attrs={"class":re.compile("^search-product")})

    for item in items:

        # 무료 배송 상품은 제외한다.
        ad_badge = item.find("span",attrs={"class":re.compile("^badge-delivery")})
        if ad_badge:
            continue

        # 평점이 4.5 이상, 리뷰가 100개넘는 것들만 출력
        name = item.find("div",attrs={"class":"name"}).get_text()

        # 애플 제품 제외
        if "Apple" in name:
            continue

        price = item.find("strong",attrs={"class":"price-value"}).get_text()
        rate = item.find("em",attrs={"class":"rating"})

        # 평점이 없는 product에 대한 조건문
        if rate:
            rate = rate.get_text()
        else :
            continue

        rate_cnt = item.find("span",attrs={"class":"rating-total-count"})
        # 평점 수 없는 product에 대한 조건문
        if rate_cnt :
            rate_cnt = rate_cnt.get_text()
            rate_cnt = rate_cnt[1:-1] # 처음이랑 마지막 index 제외시키기
        else :
            continue

        # 제품 link 가져오기
        link = item.find("a", attrs={"class":"search-product-link"})["href"]

        if float(rate) >= 4.5 and int(rate_cnt) >= 100:
            #print(name, price, rate, rate_cnt)
            print(f"제품명 : {name}")
            print(f"가격 : {price}")
            print(f"평점 : {rate}점 ({rate_cnt}개)")
            print("바로가기 : {}".format("https://www.coupang.com"+link))
            print("-"*100) # 구분하기 위한 줄

```
