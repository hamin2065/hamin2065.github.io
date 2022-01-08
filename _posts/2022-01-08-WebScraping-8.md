---
layout: post
title: "[웹 스크래핑] BeautifulSoup4 #4"
subtitle: "다음 이미지"
categories: data
tags: web-scraping
---

# 다음 이미지 가져오기

전 실습인 쿠팡에서 했던 방식과 비슷하게 이중 for문을 돌려서 각각 연도에 있는 5개의 이미지를 다운 받는다.
`with open`을 써서 파일 이름을 지정하고 link의 content내용을 통해서 이미지를 다운받는다.

```py
import requests
from bs4 import BeautifulSoup


for year in range(2016, 2021):
    url = "https://search.daum.net/search?w=tot&q={}%EB%85%84%EC%98%81%ED%99%94%EC%88%9C%EC%9C%84&DA=MOR&rtmaxcoll=MOR".format(year)
    res = requests.get(url)
    res.raise_for_status()
    soup = BeautifulSoup(res.text, "lxml")

    images = soup.find_all("img", attrs={"class":"thumb_img"})

    for idx, image in enumerate(images):
        image_url = image["src"]
        print(image_url)

        image_res = requests.get(image_url)
        image_res.raise_for_status()

        with open("movie{}_{}.jpg".format(year, idx+1), "wb") as f:
            f.write(image_res.content)

        # 상위 5개 이미지까지만 다운로드
        if idx >= 4:break
```
